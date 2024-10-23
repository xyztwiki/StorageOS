use nalgebra as na;
use plotters::prelude::*;

type Complex = na::Complex<f64>;
type Matrix2c = na::Matrix2<Complex>;
type Matrix4c = na::Matrix4<Complex>;

const HBAR: f64 = 1.0;  // Reduced Planck's constant
const C: f64 = 299792458;     // Speed of light
const M: f64 = 1.0;     // Mass of the particle

// Pauli matrices
    Matrix2c::new(Complex::new(0.0, 0.0), Complex::new(1.0, 0.0),
                  Complex::new(1.0, 0.0), Complex::new(0.0, 0.0))
}

fn sigma_y() -> Matrix2c {
    Matrix2c::new(Complex::new(0.0, 0.0), Complex::new(0.0, -1.0),
                  Complex::new(0.0, 1.0), Complex::new(0.0, 0.0))
}

fn sigma_z() -> Matrix2c {
    Matrix2c::new(Complex::new(1.0, 0.0), Complex::new(0.0, 0.0),
                  Complex::new(0.0, 0.0), Complex::new(-1.0, 0.0))
}

// Dirac matrices
fn alpha_x() -> Matrix4c {
    Matrix4c::new(
        Complex::new(0.0, 0.0), Complex::new(0.0, 0.0), Complex::new(0.0, 1.0), Complex::new(0.0, 0.0),
        Complex::new(0.0, 0.0), Complex::new(0.0, 0.0), Complex::new(1.0, 0.0), Complex::new(0.0, 0.0),
        Complex::new(0.0, 1.0), Complex::new(1.0, 0.0), Complex::new(0.0, 0.0), Complex::new(0.0, 0.0),
        Complex::new(0.0, 0.0), Complex::new(0.0, 0.0), Complex::new(0.0, 0.0), Complex::new(0.0, 0.0)
    )
}

fn beta() -> Matrix4c {
    Matrix4c::new(
        Complex::new(1.0, 0.0), Complex::new(0.0, 0.0), Complex::new(0.0, 0.0), Complex::new(0.0, 0.0),
        Complex::new(0.0, 0.0), Complex::new(1.0, 0.0), Complex::new(0.0, 0.0), Complex::new(0.0, 0.0),
        Complex::new(0.0, 0.0), Complex::new(0.0, 0.0), Complex::new(-1.0, 0.0), Complex::new(0.0, 0.0),
        Complex::new(0.0, 0.0), Complex::new(0.0, 0.0), Complex::new(0.0, 0.0), Complex::new(-1.0, 0.0)
    )
}

// Dirac Hamiltonian for a free particle
fn dirac_hamiltonian(p: f64) -> Matrix4c {
    C * p * alpha_x() + M * C.powi(2) * beta()
}

// Solve the time-independent Dirac equation
fn solve_dirac(p: f64) -> (f64, f64, na::Vector4<Complex>) {
    let h = dirac_hamiltonian(p);
    let eigen = h.eigenvalues();
    let positive_energy = eigen[0].re;
    let negative_energy = eigen[2].re;
    let eigenvector = h.eigenvectors().unwrap().column(0).into_owned();
    (positive_energy, negative_energy, eigenvector)
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("Dirac Equation Demonstration");
    println!("----------------------------");
    println!("The Dirac equation is a relativistic quantum mechanical wave equation formulated by Paul Dirac:");
    println!("    (iℏγ^μ∂_μ - mc)ψ = 0");
    println!("Where:");
    println!("    γ^μ are the Dirac gamma matrices");
    println!("    ∂_μ is the four-gradient");
    println!("    m is the mass of the particle");
    println!("    c is the speed of light");
    println!("    ψ is the Dirac spinor");

    println!("\nIn this demonstration, we'll solve the time-independent Dirac equation for a free particle:");
    println!("    Hψ = Eψ");
    println!("Where H is the Dirac Hamiltonian: H = c(α⋅p) + βmc^2");

    // Calculate energy eigenvalues for different momenta
    let p_values: Vec<f64> = (-100..=100).map(|p| p as f64 / 10.0).collect();
    let energies: Vec<(f64, f64, f64)> = p_values.iter()
        .map(|&p| {
            let (e_pos, e_neg, _) = solve_dirac(p);
            (p, e_pos, e_neg)
        })
        .collect();

    // Plot energy-momentum relation
    let root = BitMapBackend::new("dirac_energy_momentum.png", (800, 600)).into_drawing_area();
    root.fill(&WHITE)?;

    let mut chart = ChartBuilder::on(&root)
        .caption("Energy-Momentum Relation in Dirac Equation", ("sans-serif", 30).into_font())
        .margin(5)
        .x_label_area_size(30)
        .y_label_area_size(40)
        .build_cartesian_2d(-10.0..10.0, -15.0..15.0)?;

    chart.configure_mesh().draw()?;

    chart.draw_series(LineSeries::new(
        energies.iter().map(|&(p, e, _)| (p, e)),
        &RED,
    ))?
    .label("Positive Energy")
    .legend(|(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], &RED));

    chart.draw_series(LineSeries::new(
        energies.iter().map(|&(p, _, e)| (p, e)),
        &BLUE,
    ))?
    .label("Negative Energy")
    .legend(|(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], &BLUE));

    chart.configure_series_labels()
        .background_style(&WHITE.mix(0.8))
        .border_style(&BLACK)
        .draw()?;

    root.present()?;

    println!("\nEnergy-momentum relation plot saved as 'dirac_energy_momentum.png'");
    println!("\nKey observations:");
    println!("1. The Dirac equation predicts both positive and negative energy solutions.");
    println!("2. The energy-momentum relation is not parabolic (as in non-relativistic quantum mechanics).");
    println!("3. There's a gap between positive and negative energy states, equal to 2mc^2.");
    println!("4. The negative energy solutions were initially interpreted as positrons (antiparticles).");

    Ok(())
}