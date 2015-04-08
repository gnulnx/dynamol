#ifndef MOLVIEWSCRIPT_H
#define MOLVIEWSCRIPT_H

#include <string>

class molView;
namespace dynacomp
{
    class molecule;
}

#ifdef WINDOWS
extern "C" __declspec(dllexport) 
#endif
void NumberList();

//#ifdef WINDOWS
//extern "C" __declspec(dllexport) 
//#endif
//molView *VIEWER;

#ifdef WINDOWS
extern "C" __declspec(dllexport) 
#endif
int molview_selectAll();

#ifdef WINDOWS
extern "C" __declspec(dllexport)
#endif
int molview_atomCount();

#ifdef WINDOWS
extern "C" __declspec(dllexport)
#endif
int molview_selectAtomType(std::string type);


#ifdef WINDOWS
extern "C" __declspec(dllexport)
#endif
int molview_selectInvert();

#ifdef WINDOWS
extern "C" __declspec(dllexport)
#endif
int molview_selectWithin(float ang);

#ifdef WINDOWS
extern "C" __declspec(dllexport)
#endif
int molview_selectMol(int in);

#ifdef WINDOWS
extern "C" __declspec(dllexport)
#endif
dynacomp::molecule *molview_getMol(int n);

#ifdef WINDOWS
extern "C" __declspec(dllexport)
#endif
void molview_addMol(dynacomp::molecule *mol);

class molViewScript {
public:
   molViewScript();
   ~molViewScript();

   /** \brief Select all atoms in all molecules 
    *   Returns the number of selected atoms
    * */
   static int selectAll();
   
   /** Select all atoms of type "type" 
    *  Returns the number selected atoms
    * */
   static int selectAtomType(std::string type);

   /** Invert the current selection 
    *  Retuns the number of selected atoms
    * */
   static int selectInvert();

   /** Select atoms with "ang" Angstroms of atoms currently selected 
    *   You should probably divide atom space into a BSP tree
    * */
   static int selectWithin(float ang);

   /** Select the "nth" molecule added to the MolView window 
    * */
   static int selectMol(int n);

   /** Return the number of atoms in the molView 
    * */
   static int atomCount();


   /** Return a dynacomp reference to molecul "num"
    *  in the MolView window
    */
   static dynacomp::molecule *getMol(int num);

   static void addMol(dynacomp::molecule *mol);
   
//private:
   static molView *VIEWER;
};

#endif
