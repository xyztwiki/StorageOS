use rand::Rng;
use rand_distr::{Distribution, Normal};
use plotters::prelude::*;

const HBAR: f64 = 1.0; // Reduced Planck's constant (in appropriate units)

// Simulate a measurement of position with given uncertainty
fn measure_position(true_position: f64, uncertainty: f64) -> f64 {
    let normal = Normal::new(true_position, uncertainty).unwrap();
    normal.sample(&mut rand::thread_rng())
}

// Simulate a measurement of momentum with given uncertainty
fn measure_momentum(true_momentum: f64, uncertainty: f64) -> f64 {
    let normal = Normal::new(true_momentum, uncertainty).unwrap();
    normal.sample(&mut rand::thread_rng())
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("Heisenberg Uncertainty Principle");
    println!("--------------------------------");
    println!("The Heisenberg uncertainty principle states that:");
    println!("    ΔxΔp ≥ ℏ/2");
    println!("Where:");
    println!("    Δx is the uncertainty in position");
    println!("    Δp is the uncertainty in momentum");
    println!("    ℏ is the reduced Planck's constant");
    println!("\nThis means that we cannot simultaneously measure both the position and momentum of a particle with arbitrary precision.");
    println!("The more precisely we know one of these values, the less precisely we can know the other.");

    // Demonstration
    let true_position = 0.0;
    let true_momentum = 1.0;
    let n_measurements = 1000;

    let uncertainty_pairs = vec![
        (0.1, 5.0),  // High position certainty, low momentum certainty
        (1.0, 0.5),  // Balanced
        (5.0, 0.1),  // Low position certainty, high momentum certainty
    ];

    let root = BitMapBackend::new("heisenberg_uncertainty.png", (800, 600)).into_drawing_area();
    root.fill(&WHITE)?;

    let mut chart = ChartBuilder::on(&root)
        .caption("Heisenberg Uncertainty Principle Demonstration", ("sans-serif", 20).into_font())
        .margin(5)
        .x_label_area_size(30)
        .y_label_area_size(30)
        .build_cartesian_2d(-10.0..10.0, -10.0..10.0)?;

    chart.configure_mesh().draw()?;

    for (i, (pos_uncertainty, mom_uncertainty)) in uncertainty_pairs.iter().enumerate() {
        let color = Palette99::pick(i);
        let mut measurements = Vec::new();

        for _ in 0..n_measurements {
            let measured_position = measure_position(true_position, *pos_uncertainty);
            let measured_momentum = measure_momentum(true_momentum, *mom_uncertainty);
            measurements.push((measured_position, measured_momentum));
        }

        chart.draw_series(measurements.iter().map(|&(x, y)| Circle::new((x, y), 2, color.filled())))?
            .label(format!("Δx = {:.1}, Δp = {:.1}", pos_uncertainty, mom_uncertainty))
            .legend(move |(x, y)| Circle::new((x, y), 5, color.filled()));

        let product = pos_uncertainty * mom_uncertainty;
        println!("\nFor Δx = {:.1} and Δp = {:.1}:", pos_uncertainty, mom_uncertainty);
        println!("    ΔxΔp = {:.3}", product);
        println!("    ℏ/2 = {:.3}", HBAR / 2.0);
        println!("    Is ΔxΔp ≥ ℏ/2? {}", if product >= HBAR / 2.0 { "Yes" } else { "No" });
    }

    chart.configure_series_labels()
        .background_style(&WHITE.mix(0.8))
        .border_style(&BLACK)
        .draw()?;

    root.present()?;

    println!("\nMeasurement plot saved as 'heisenberg_uncertainty.png'");

    Ok(())
}