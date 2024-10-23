use std::f64::consts::PI;
use plotters::prelude::*;

// Constants
const HBAR: f64 = 1.0; // Reduced Planck's constant (in appropriate units)
const M: f64 = 1.0;    // Mass of the particle (in appropriate units)
const L: f64 = 1.0;    // Length of the infinite potential well

// Eigenvalues (energy levels) for the infinite potential well
fn energy_level(n: u32) -> f64 {
    (n as f64 * PI * HBAR).powi(2) / (2.0 * M * L.powi(2))
}

// Wavefunctions for the infinite potential well
fn wavefunction(x: f64, n: u32) -> f64 {
    (2.0 / L).sqrt() * (n as f64 * PI * x / L).sin()
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("Schrödinger Equation for Particle in a 1D Infinite Potential Well");
    println!("-------------------------------------------------------------------");
    println!("The time-independent Schrödinger equation is:");
    println!("    -ℏ²/2m * d²ψ/dx² + V(x)ψ = Eψ");
    println!("For an infinite potential well, V(x) = 0 inside the well and infinity outside.");
    println!("This leads to the following solutions:");
    println!("    ψₙ(x) = √(2/L) * sin(nπx/L)");
    println!("    Eₙ = (n²π²ℏ²) / (2mL²)");
    println!();

    // Calculate and display the first few energy levels
    for n in 1..=5 {
        println!("E{} = {:.4} (in units of ℏ²/2mL²)", n, energy_level(n));
    }

    // Plot the first three wavefunctions
    let root = BitMapBackend::new("wavefunctions.png", (800, 600)).into_drawing_area();
    root.fill(&WHITE)?;

    let mut chart = ChartBuilder::on(&root)
        .caption("Wavefunctions for Infinite Potential Well", ("sans-serif", 30).into_font())
        .margin(5)
        .x_label_area_size(30)
        .y_label_area_size(30)
        .build_cartesian_2d(0.0..L, -2.0..2.0)?;

    chart.configure_mesh().draw()?;

    for n in 1..=3 {
        let color = Palette99::pick(n);
        chart.draw_series(LineSeries::new(
            (0..=100).map(|i| {
                let x = i as f64 * L / 100.0;
                (x, wavefunction(x, n as u32))
            }),
            color,
        ))?
        .label(format!("n = {}", n))
        .legend(move |(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], color));
    }

    chart.configure_series_labels()
        .background_style(&WHITE.mix(0.8))
        .border_style(&BLACK)
        .draw()?;

    root.present()?;

    println!("\nWavefunctions plot saved as 'wavefunctions.png'");

    Ok(())
}