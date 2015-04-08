/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   email:  john.furr@dynamol.com
 ***************************************************************************/
#ifndef FLEXALIGN_H
#define FLEXALIGN_H

#include "dynothread.h"

//Standard Library Includes
#include <vector>
#include <map>
using std::map;
using std::vector;

//Dynamol Forward Declarations
class molecule;
class XmodelView;

//Dynamol Computational Library Forward Declarations
namespace dynacomp {
   class flexAlign;
   class molecule;
}

//Thread Class to Handle Flexible Alignment
class flexAlignThread :public dynoThread {
   public:
   flexAlignThread(XmodelView *view, string name);
   ~flexAlignThread();
   /** \brief Used to set the simulation parameters */
   void setUp(map<string, string> Params); 
    
   virtual void run();
   virtual QString getName();
   virtual void setName(string name);
   virtual void stopThread();
   virtual int rtti(); //returns 4;
private:
   /** \brief All molecules are in the viewer */
   bool molViewAlign();
   /** \breif Template in Viewer, others in file */
   bool tempViewAlignFile();
   /** \brief Template molecule in File others in viewer */
   bool tempFileAlignView();
   /** All molecule read from file*/
   bool tempFileAlignFile();

   /** \brief Save the alignments
   * 
   *   The type of save is determined by the Params map
   */
   bool savePoseMap(multimap<float, vector<float> > &poseMap,
                    molecule *templ, molecule *mol);

   /** \brief The flexible alignment class
   * 
   *   This class is defined in flexalign.h in the dynacomp 
   *   directory
   */
   dynacomp::flexAlign *dcFlexAlign;

   /** \brief The view part of the document-view model
   */
   XmodelView *view;

   /** \brief The template molecule
   *
   *   Note the template molecule may be allowed to flex
   */
   dynacomp::molecule *templ;

   /** \brief The molecule to align
   *
   *  Note the template molecule may be allowed to fles
   */
   dynacomp::molecule *toAlign;

   /** \brief The Simulation Parameters
   * 
   *   The Params map includes a list of parameters for the simlulation
   */
   map<string, string> Params;

   /** \brief Stop Check
   *   
   *   When set to true the simulation will stop
   */
   bool stop;
};

#endif

