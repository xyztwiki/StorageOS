use std::collections::HashMap;

#[derive(Debug, PartialEq, Eq, Hash, Clone, Copy)]
struct Electron {
    n: u32,  // Principal quantum number
    l: u32,  // Azimuthal quantum number
    ml: i32, // Magnetic quantum number
    ms: i32, // Spin quantum number
}

impl Electron {
    fn new(n: u32, l: u32, ml: i32, ms: i32) -> Self {
        Electron { n, l, ml, ms }
    }
}

struct Atom {
    electrons: Vec<Electron>,
}

impl Atom {
    fn new() -> Self {
        Atom { electrons: Vec::new() }
    }

    fn add_electron(&mut self, electron: Electron) -> Result<(), String> {
        // Check if the electron state is already occupied
        if self.electrons.contains(&electron) {
            return Err("Electron state already occupied. Pauli exclusion principle violated!".to_string());
        }

        // Check if the quantum numbers are valid
        if electron.l >= electron.n || electron.ml.abs() as u32 > electron.l || electron.ms.abs() > 1 {
            return Err("Invalid quantum numbers".to_string());
        }

        self.electrons.push(electron);
        Ok(())
    }

    fn electron_configuration(&self) -> HashMap<(u32, u32), u32> {
        let mut config = HashMap::new();
        for e in &self.electrons {
            *config.entry((e.n, e.l)).or_insert(0) += 1;
        }
        config
    }
}

fn main() {
    println!("Pauli Exclusion Principle Demonstration");
    println!("---------------------------------------");
    println!("The Pauli exclusion principle states that no two electrons in an atom can have the same set of quantum numbers.");
    println!("This principle is fundamental to the electronic structure of atoms and the stability of matter.");
    println!("\nWe'll demonstrate this by filling electron orbitals in an atom:");

    let mut atom = Atom::new();

    // Filling 1s orbital (n=1, l=0)
    println!("\nFilling 1s orbital:");
    assert!(atom.add_electron(Electron::new(1, 0, 0, -1)).is_ok()); // Spin up
    assert!(atom.add_electron(Electron::new(1, 0, 0, 1)).is_ok());  // Spin down
    println!("Successfully added two electrons with opposite spins.");

    // Trying to add a third electron to 1s (should fail)
    println!("\nTrying to add a third electron to 1s orbital:");
    match atom.add_electron(Electron::new(1, 0, 0, -1)) {
        Ok(_) => println!("Added successfully (This shouldn't happen!)"),
        Err(e) => println!("Failed as expected: {}", e),
    }

    // Filling 2s orbital (n=2, l=0)
    println!("\nFilling 2s orbital:");
    assert!(atom.add_electron(Electron::new(2, 0, 0, -1)).is_ok());
    assert!(atom.add_electron(Electron::new(2, 0, 0, 1)).is_ok());
    println!("Successfully added two electrons to 2s orbital.");

    // Filling 2p orbitals (n=2, l=1)
    println!("\nFilling 2p orbitals:");
    for ml in -1..=1 {
        assert!(atom.add_electron(Electron::new(2, 1, ml, -1)).is_ok());
        assert!(atom.add_electron(Electron::new(2, 1, ml, 1)).is_ok());
        println!("Added two electrons to 2p orbital with ml = {}", ml);
    }

    // Print final electron configuration
    println!("\nFinal electron configuration:");
    let config = atom.electron_configuration();
    for ((n, l), count) in config {
        let orbital = match l {
            0 => "s",
            1 => "p",
            2 => "d",
            3 => "f",
            _ => "?",
        };
        println!("{}{}:{}", n, orbital, count);
    }

    println!("\nThis demonstration shows how the Pauli exclusion principle limits the number of electrons in each orbital,");
    println!("leading to the characteristic electron configurations of atoms.");
}