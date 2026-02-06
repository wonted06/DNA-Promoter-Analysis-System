# Gene Expression Analysis System  
*A C++ Object-Oriented Programming Project*

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Status](https://img.shields.io/badge/Status-Complete-success)
![Focus](https://img.shields.io/badge/Focus-Systems%20Programming-purple)

---

## 📌 Overview

This project is a **C++ gene analysis application** that models biological gene promoters and predicts their **response to glucose** based on known DNA motifs.  
The system integrates a custom-designed `Gene` class into a provided prototype application, processes a large promoter dataset, and outputs the **top 20 up-regulated genes** ranked by calculated propensity.

The project emphasises **robust class design, operator overloading, unit testing, debugging, and performance optimisation** within a real-world scientific computing context.

---

## ✨ Key Features

- Object-oriented `Gene` class with full encapsulation
- Operator overloading for comparison and stream I/O
- CSV-based input and output compatibility
- Unit testing via a dedicated test harness
- Refactoring and debugging of an existing codebase
- Performance improvements through reduced object copying
- Standards-compliant **C++17** implementation

---

## 🧠 Core Functionality

The system performs the following steps:

- Loads a database of gene promoter sequences
- Identifies biologically relevant DNA motifs
- Calculates a **glucose-response propensity score** per gene
- Sorts genes by descending propensity
- Outputs the **top 20 genes** to a CSV file

Upper-case characters in DNA sequences are ignored, ensuring robust and consistent analysis.

---

## 🧬 Gene Class Design

### Attributes
- `id` (`std::string`) – unique gene identifier  
- `sequence` (`std::string`) – promoter DNA sequence  
- `propensity` (`double`) – computed glucose-response score  

### Implemented Functionality
- Default and parameterised constructors
- Accessor methods for all attributes
- `setPropensity(double)` mutator
- `toString()` for formatted output
- Full relational operator set (`<`, `>`, `<=`, `>=`, `==`, `!=`)
  - Ordering based on propensity
- Stream insertion and extraction operators (`<<`, `>>`)
  - Compatible with CSV input/output formats

---

## 🧪 Unit Testing

Unit testing is implemented in **`GeneTest.cpp`**:

- Centralised `testGene()` function
- Verifies constructors, accessors, operators, and I/O behaviour
- Designed for regression testing
- Minimal console output on successful test runs

This ensures the `Gene` class behaves correctly both in isolation and when integrated.

---

## 🔧 System Integration & Debugging

The `Gene` class is fully integrated with a provided prototype application:

- Compilation issues were resolved
- Runtime and logic errors were identified and fixed
- Behaviour was validated against expected biological outputs
- A revision history was maintained as required

The final system preserves the original program structure while improving correctness and maintainability.

---

## ⚡ Performance Optimisation

The prototype was refactored to improve efficiency by:

- Replacing `std::vector<Gene>` with `std::vector<Gene*>`
- Minimising unnecessary object copying
- Maintaining safe memory management practices
- Improving scalability for large datasets

---

## 🛠️ Tech Stack

- **C++17**
- **STL** (`vector`, `string`, algorithms, streams)
- **CMake** – build system
- **GCC / G++** (PASS-compatible)

---

## 📂 Project Structure
