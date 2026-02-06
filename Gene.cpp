/******************************************************************************

File        : Gene.cpp

Date        : 29th October 2025

Author      : Kurt Canillas

Description : Implementation of the Gene class for gene data representation.

              Provides constructors, accessors, mutators, relational operators,
              stream operators.

******************************************************************************/

#include "Gene.h"
#include <iomanip>
#include <sstream>
#include <string>

// Default constructor
// Initialises ID, sequence to empty string and propensity to 0.0
Gene::Gene() : ID(""), sequence(""), propensity(0.0){}

// Ordinary constructor
// Gene identifier || Gene seuquence as a string
Gene::Gene(const std::string& ID, const std::string& sequence)
: ID(ID), sequence(sequence), propensity(0.0) {}

// Accessors & Mutators
std::string Gene::getID() const {return ID;}                // Returns gene identifier
std::string Gene::getSequence() const {return sequence;}    // Returns sequence identifer
double Gene::getPropensity() const {return propensity;}        // Returns glucose response propensity
void Gene::setPropensity(double p) {this->propensity = p;}     // Sets glucose response propensity for gene

// Relational Operators || Compare genes based on propensity values
bool Gene::operator<(const Gene& other) const { return propensity < other.propensity; }
bool Gene::operator>(const Gene& other) const { return propensity > other.propensity; }
bool Gene::operator<=(const Gene& other) const { return propensity <= other.propensity; }
bool Gene::operator>=(const Gene& other) const { return propensity >= other.propensity; }
bool Gene::operator==(const Gene& other) const { return propensity == other.propensity; }
bool Gene::operator!=(const Gene& other) const { return propensity != other.propensity; }

// Stream operators

// Output stream operator for Gene objects
std::ostream& operator<<(std::ostream& os, const Gene& gene) {
    os << std::quoted(gene.ID)<< ","
       << std::quoted(gene.sequence) << ","
       << gene.propensity;
    return os;
}

// Input stream operator for Gene objects
std::istream& operator>>(std::istream& is, Gene& gene) {
    std::string ID, sequence;
    char comma; // to consume commas

    // Read quoted ID, comma, quoted sequence, comma, propensity
    if (is >> std::quoted(ID) >> comma >> std::quoted(sequence) >> comma >> gene.propensity) {
        gene = Gene(ID, sequence); // reset gene
        gene.setPropensity(gene.propensity);
    }
    return is;
}