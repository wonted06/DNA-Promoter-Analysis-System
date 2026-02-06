/******************************************************************************

File        : main.cpp

Date        : Wednesday 29th October 2025

Author      : Kurt Canillas

Description : Prototype implementation of a program to identify genes with
              the greatest propensity for glucose response, based on the
              presence of specific sequence features of the upstream promoter
              region [1].

              Note that this program is just a prototype system to be used to
              refine the project specifications.  There may be bugs and areas
              where the code is inefficient.  These issues will be addressed
              as the program is iteratively improved/refactored.

Notes       :

References  : [1] Li, Y., Lee, K.-K., Walsh, S., Smith, C., Hadingham, S.,
                  Sorefan, K., Cawley, G. and Bevan, M. W., "Establishing
                  glucose- and ABA-regulated transcription networks in
                  Arabidopsis by microarray analysis and promoter
                  classification using a Relevance Vector Machine", Genome
                  Research, vol. 16, pp 414-427, 2006.

History     : 29/10/2025 - v1.00 Initial prototype
              - Refactored vector<Gene> to vector<Gene*> to avoid unnecessary copying
              - Fixed for-loop to compute propensity on Gene* objects
              - Updated call-site comparator to dereference Gene* and sort descending
              - Fixed erroneous numeric literal (-07107 -> -0.7107)
              - Handled 'r' wildcard in motif "rccgac" by expanding into "accgac" and "gccgac
              - Corrected file output to write Gene objects instead of pointers
              - Ensure displayGene receives a Gene& instead of a pointer
              - Fixed memory leak by deleting unused allocation and clearing allocated Genes
              - Implemented promoter extraction by filtering out uppercase characters from gene
                sequences

******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>

#include "Gene.h"

using namespace std;

// declarations of functions defined later in this file

double propensity(const string &sequence, map<string,double> *sites);

// fix - vector<T> || vector<T>& to pass by reference
template <typename T, typename F> void bubbleSort(vector<T>& vec, F compare);

void displayGene(const Gene &gene);

int main()
{
   // load the database of Arabidopsis promoter sequences
   // Refactored for efficiency || Updated bubbleSort template for Gene*
   vector<Gene*> genes;

   Gene* gene = new Gene();

   ifstream is("arabidopsis.csv", ifstream::in);

   while (is >> *gene)
   {
      genes.push_back(gene);
      gene = new Gene();
   }

   is.close();

   // compute the glucose response propensity for each gene

   for (Gene* g : genes)
   {
      // fix - missing comma after g.getSequence()
      g->setPropensity(propensity(g->getSequence(), nullptr));
   }

   // sort genes in order of their propensity for glucose response
   // genes stores Gene* || lambda must accept Gene* then dereference to compare objects
   bubbleSort(genes, [](const Gene* a, const Gene* b) {return *a > *b;});

   // display the protein with the highest propensity for glucose response

   if (!genes.empty()) displayGene(*genes[0]);

   // save list of the top 20 up-regulated genes for subsequent analyses

   ofstream os("top20.csv");

   size_t top = std::min<size_t>(20, genes.size());
   for (size_t i = 0; i < top; i++)
   {
      os << *genes[i] << endl; // write Gene object, not pointer
   }

   os.close();

   delete gene; // delete last unused allocation

   for (Gene* p : genes) delete p;
   genes.clear();

   return EXIT_SUCCESS;
}


/******************************************************************************

Function    : propensity

Parameters  : sequence - a const reference to a string containing the sequence
                         data for a promoter region

              map<string,double> *sites - optional pointer to a map used to
                                          store the contribution of each
                                          transcription factor binding site to
                                          the overall propensity

Returns     : double - value of propensity for glucose response

Description : Determine the propensity for glucose regulation based on an
              analysis of the upstream promoter region, using the motifs and
              scores identified by Li et al. [1].  If both arguments are
              provided, the second is used to store the contribution of each
              transcription factor binding site to the overall propensity
              score.

Notes       : The code is currently rather inefficient as it sequentially
              checks for each binding site motif in turn.  A finite state
              automata that recognised the entire language would likely be
              more efficient.

******************************************************************************/

double propensity(const std::string &seq, std::map<string,double> *sites)
{
   static const struct
   {
      std::string motif;

      double score;
   }
   bindingSites[] =
   {
      { "aaaccctaa", +2.9895 },
      { "ggaagggt",  +1.3346 },
      { "ggtagggt",  +1.3346 },
      { "aacgtgt",   +1.1033 },
      { "acggg",     +0.9637 },
      { "gcggcaaa",  +0.9067 },
      { "gttaggtt",  +0.8397 },
      { "accgac",    +0.8076 },
      { "gccgac",    +0.8076 },
      { "gataaga",   -3.3202 },
      { "gataagg",   -3.3202 },
      { "gataa",     -2.1431 },
      { "gataag",    -0.7107 },
      { "ggata",     -3.2140 },
      { "acgtggca",  -1.1698 },
      { "taacgta",   -0.9167 },
      { "aaaatatct", -0.8441 }
   };

   double propensity = 0.0;

   // Remove uppercase characters (non-promoter region) from gene sequence
   std::string prom;
   prom.reserve(seq.size());
   for (unsigned char c : seq)
      if (std::islower(c))
         prom.push_back(c);

   for (auto& site : bindingSites)
   {
      double score = 0.0;

      int idx = -1;

      while ((idx = prom.find(site.motif, idx+1)) != string::npos)
      {
         score += site.score;
      }

      propensity += score;

      if (sites != nullptr)
      {
         (*sites)[site.motif] = score;
      }
   }

   return propensity;
}

/******************************************************************************

Function    : bubbleSort (template)

Parameters  : T       - template parameter given base type of vector
              F       - template parameter giving lambda/function pointer type
              vec     - reference to vector of base type T
              compare - lambda or function pointer used to define ordering

Returns     : void

Description : Basic implementation of bubble sort, implemented as a template
              so that it can be used with vectors of different types.  Bubble
              sort is not very efficient for large vectors, but is fine for
              prototyping with small datasets.  The compare function returns
              a true value if a pair of adjacent elements should be swapped
              and false otherwise.

******************************************************************************/

template <typename T, typename F> void bubbleSort(std::vector<T>& vec, F compare)
{
   bool sorted;

   do
   {
      sorted = true;

      for (size_t i = 1; i < vec.size(); i++)
      {
         if (compare(vec[i], vec[i-1]))
         {
            T temp   = vec[i];
            vec[i]   = vec[i-1];
            vec[i-1] = temp;

            sorted = false;
         }
      }
   }
   while (!sorted);
}


/******************************************************************************

Function    : displayGene

Parameters  : gene - const pointer to a Gene object

Returns     : void

Description : Display the information about a promoter, including an analysis
              of the contribution of each of the known transcription factor
              binding sites to the calculated propensity for glucose
              regulation.

******************************************************************************/

void displayGene(const Gene &gene)
{
   cout << endl
        << "Gene ID     = " << gene.getID()         << endl
        << "Propensity  = " << gene.getPropensity() << endl
        << "Sequence    = " << gene.getSequence()   << endl;

   // re-calculate propensity in order to analyse binding sites

   map<string,double> sites;

   propensity(gene.getSequence(), &sites);

   cout << endl
        << "Binding site contributions:"
        << endl
        << endl
        << setw(10)
        << "Motif"
        << "   Contribution"
        << endl;

   for (auto const& site : sites)
   {
      std::cout << setw(10)
                << site.first
                << "   "
                << showpos
                << site.second
                << std::endl;
   }
}

/*****************************************************************************/
