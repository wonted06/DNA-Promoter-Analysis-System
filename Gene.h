/******************************************************************************

File        : Gene.h

Date        : 29th October 2025

Author      : Kurt Canillas

Description : Declaration of the Gene class for gene data representation.

              The Gene class models a simple biological gene with an identifier,
              nucleotide sequence, and computed glucose response propensity.
              It provides constructors, accessors, mutators, relational and
              stream operators, and a string representation function.

              This class forms part of the 100432626_Gene_CW project.

******************************************************************************/

#ifndef INC_100432626_GENE_CW_GENE_H
#define INC_100432626_GENE_CW_GENE_H

#include <string>
#include <iostream>

/******************************************************************************

Class       : Gene

Description : A class representing a gene entity with:
                - An ID (string)
                - A nucleotide sequence (string)
                - A numeric propensity value (double)

            Provides full encapsulation and operator overloads to allow easy comparison,
            input/output, and formatted display.

 ******************************************************************************/

class Gene {
private:
    // Unique identifier for Gene
    std::string ID;

    // Nucleotide sequence (e.g. "ACGT")
    std::string sequence;

    // Computed glucose response propensity value
    double propensity;

/******************************************************************************

Access Specifier    : public

Description         : Constructors - initialise gene objects.

                      Accessors - retrieve gene ID, sequence, and propensity.

                      Mutator - set propensity value.

                      Relational operators - allow comparison.

                      Stream operators - enable easy input/output of Gene obje

 ******************************************************************************/

public:
    // Constructors
    Gene();  // Default constructor - initialises fields to default values
    Gene(const std::string& ID, const std::string& sequence);   // Ordinary constructor

    // Accessors
    std::string getID() const;          // Retrieves gene identifier
    std::string getSequence() const;    // Retrieves gene sequence
    double getPropensity() const;       // Retrieves glucose response propensity value

    // Mutators
    void setPropensity(double p);       // Sets propensity value for gene

    // Relational operators || Compare Gene objects based on propensity values
    bool operator<(const Gene& other) const;
    bool operator>(const Gene& other) const;
    bool operator<=(const Gene& other) const;
    bool operator>=(const Gene& other) const;
    bool operator==(const Gene& other) const;
    bool operator!=(const Gene& other) const;

    // Stream operators || Enable Gene objects to be printed and read using streams
    friend std::ostream& operator<<(std::ostream& os, const Gene& gene);
    friend std::istream& operator>>(std::istream& is, Gene& gene);
};


#endif //INC_100432626_GENE_CW_GENE_H