/******************************************************************************

File        : GeneTest.cpp

Date        : 29th October 2025

Author      : Kurt Canillas

Description : Unit test harness for the Gene class.

              This file implements automated unit tests for the Gene component,
              verifying the correctness of constructors, accessors, mutators,
              operator overloads, and stream input/output functionality.

              The test harness returns true if all tests pass and false
              otherwise. Only a concise summary message is printed to
              facilitate quick regression testing.

******************************************************************************/

#include "Gene.h"
#include <iostream>
#include <sstream>

/******************************************************************************

Function    : testGene

Parameters  : None

Returns     : true  - if all test cases pass
              false - if any test case fails

Description : Executes a sequence of unit tests to validate the behaviour of
              the Gene class. Each test is self-contained and checks a distinct
              aspect of the class.

******************************************************************************/

bool testGene() {
    // Overall result flag
    bool pass = true;

    std::cout << "Running Gene unit tests...\n";

    // Test 1: Default constructor should create an empty Gene
    // Expected: ID = "", Sequence = "", Propensity = 0.0
    Gene g1;
    if (g1.getID() != "" || g1.getSequence() != "" || g1.getPropensity() != 0.0) {
        std::cout << "Failed: Default constructor\n";
        pass = false;
    }

    // Test 2: Parameterized constructor
    // Expected: correctly stores ID and sequence
    Gene g2("gene1", "ACGT");
    if (g2.getID() != "gene1" || g2.getSequence() != "ACGT") {
        std::cout << "Failed: Parameterised constructor\n";
        pass = false;
    }

    // Test 3: setPropensity and getPropensity
    g2.setPropensity(3.14);
    if (g2.getPropensity() != 3.14) {
        std::cout << "Failed: setPropensity / getPropensity\n";
        pass = false;
    }

    // Test 4: Relational operators
    Gene g3("gene2", "gggg");
    g3.setPropensity(1.0);

    if (!(g2 > g3)) { std::cout << "Failed: operator>\n"; pass = false; }
    if (!(g3 < g2)) { std::cout << "Failed: operator<\n"; pass = false; }
    if (!(g2 >= g3)) { std::cout << "Failed: operator>=\n"; pass = false; }
    if (!(g3 <= g2)) { std::cout << "Failed: operator<=\n"; pass = false; }
    if (g2 == g3) { std::cout << "Failed: operator==\n"; pass = false; }
    if (!(g2 != g3)) { std::cout << "Failed: operator!=\n"; pass = false; }

    // Test 5: Stream operators (<< and >>)
    std::ostringstream oss;
    oss << g2;
    std::istringstream iss(oss.str());
    Gene g4;
    iss >> g4;
    if (g4.getID() != g2.getID() ||
        g4.getSequence() != g2.getSequence() ||
        g4.getPropensity() != g2.getPropensity()) {
        std::cout << "Failed: stream operators (<< / >>)\n";
        pass = false;
    }

    if (pass)
        std::cout << "All test passed!\n";
    else
        std::cout << "Some test failed!\n";

    return pass;
}

/******************************************************************************

Function    : main

Description : Entry point for the Gene unit test harness. Executes testGene()
              and reports a summary for regression testing.

******************************************************************************/
/*
int main() {
    // calls testGene() function
    return testGene() ? 0 : 1;      // if testGene() = true, expression = 0
                                    // if testGene() = false, expression = 1
}
*/