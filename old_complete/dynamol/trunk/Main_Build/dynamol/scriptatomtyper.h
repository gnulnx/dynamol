/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef SCRIPTATOMTYPER_H
#define SCRIPTATOMTYPER_H

#include "scriptobject.h"

//Standard Library Includes
#include <vector>
#include <map>
using std::vector;
using std::map;

//Dynamol Type Library Includes
#include "../dynatype/topological.h"

//BOOST Includes
#include <boost/shared_ptr.hpp>

#include <qvariant.h>
/**
@author jfurr
*/
class scriptmolecule;
class scriptatom;

namespace dt {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;
}

class scriptatomtyper : public scriptObject
{
Q_OBJECT
public:
    scriptatomtyper(QObject *parent = 0, const char *name = 0);

    ~scriptatomtyper();

public slots:

   /** \brief  Preps the molecule with gaff atom types.
   *
   *   This function types the molecule with the Dynamol GAFF forcefield 
   *   implementation.  It then build various count lists which can
   *   be used as molecular properties are a basis for constructing other
   *   molecular properties.
   *
   *   This funcion should be called at the beggining of the processing
   *   stage for each molecule.
   */
   void prepMolecule(scriptmolecule *mol);
   
   /** \brief Returns the count of Rings of size 'size'
   *
   *   This function takes as input a molecule and a ring size
   *   It will return the count of rings of that size
   *   You should call prepMolecule
   *   First in order to save time.
   */
   int ringCount(scriptmolecule *mol, int ringSize);
   
   /** \brief Returns a count of bonds at a specified order
   *
   *   This function takes as arguments a molecule and a bond order
   *   It will return the count of bonds with the given order
   */
   int bondOrderCount(scriptmolecule *mol, int order);
   
   /** \brief Returns a count of atoms with atomic number AN
   *
   *   This function takes as arguments a molecule and an 
   *   atomic number.  It returns the count of atoms with the
   *   specified atomic number
   */
   int atomCounts(scriptmolecule *mol, int AN);
   
   /** \brief Returns the number of aromatic rings.
   *
   *   Return the number of aromatic rings.  Aromaticity is determined
   *   by the GAFF force field type.  Included types are
   *   -ca  --pure aromatic carbon
   *   -cc(cd)  --sp2 carbon in conjugated ring
   *   -cp(cq)  --sp2 bridge carbon in biphenyl systems
   *   -nb aromatic nitrogen
   */
   int aromaticRingCount(scriptmolecule *mol);
   
   /** \brief highlight all atoms with the specified atom environment descriptor
   *
   *    This function allows you to view various atom environments.  Have a look at 
   *    the features file to see what atom environments are being used.
   *    Also note that the atom environments are sorted by Shannon Entropy.  Thus to see
   *    what the highest entropy descriptor is call  selectAE3(mol, 0)
   *    This function will return the entropy of the specifed descriptor
   */
   float selectAE3(scriptmolecule *mol, int descNum); 

   /** \brief highlight all atoms with the specified atom environment descriptor
   *
   *    This function allows you to view various atom environments.  Have a look at
   *    the features file to see what atom environments are being used.
   *    Also note that the atom environments are sorted by Shannon Entropy.  Thus to see
   *    what the highest entropy descriptor is call  selectAE2(mol, 0)
   *    This function will return the entropy of the specifed descriptor
   */
   float selectAE2(scriptmolecule *mol, int descNum);
private:
   scriptmolecule *currMol;
   //dt::molecule *currDT;
   dt::molPtr currDT;
   
   /** This function is used to zero out the following vectors
   */
   void zeroCounts();
   
   /** These variable provide simple counts of atomic properties
   *   It is faster to calculate them upfont
   */
   std::vector<int> AC; //atom counts indexed by atomic number;
   std::vector<int> ringCounts; //indexed by ring size
   std::vector<int> BOC; // bond order counts indexed by order-1
   
   /** This map is used in conjunction with setGaffEStateSum() and getGaffEStateSum()
   */
   map<QString, float> gaffEStateMap;
   map<QString, int> gaffEStateCountMap;
   
   // \brief This is the Topological class from dynatype
   //*/
   dt::Topological Topo;
};

#endif








