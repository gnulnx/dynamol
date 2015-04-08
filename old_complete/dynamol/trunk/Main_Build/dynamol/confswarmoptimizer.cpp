/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "confswarmoptimizer.h"
#include <iostream>
#include "molecule.h"
#include "confswarm.h"
#include <iomanip>
#include "moladapter.h"
#include "../dynatype/molecule.h"
#include "../dynatype/dtype.h"
#include "charge.h"
#include "math.h"
#include "forcefield.h"

csoThread::csoThread(XmodelView *view, QString name) 
: dynoThread(NULL)
{
   //cout <<"Welcome to the csoThread constuctor"<<endl;
   cso = new confSwarmOptimizer;
}
csoThread::csoThread() 
: dynoThread(NULL)
{
}

csoThread::~csoThread() {

}
   
void csoThread::run() {
   cso->run();
}
QString csoThread::getName() {
	QString tmp = "";
	return tmp;
}
void csoThread::setName(QString name) {
}
void csoThread::stopThread() {
}
int csoThread::rtti() {
return 0;
}

void csoThread::setMolecule(molecule *mol) {
   this->mol = mol;
   cso->setMolecule(mol);
}

void csoThread::init(float id, float c1, float c2, int popSize, int Gen) {
   cso->init(id, c1, c2, popSize, Gen);
}
   
   
confSwarmOptimizer::confSwarmOptimizer()
{
   //cout <<"confSwarmOptimizer"<<endl;
    cs = NULL;
}


confSwarmOptimizer::~confSwarmOptimizer()
{
   //cout <<"Leaving destructor"<<endl;
   if (cs != NULL)
   delete cs;
}

void confSwarmOptimizer::setMolecule(molecule *mol) {
   //cout <<"Setting molecule"<<endl;
   //cout <<"mol->getName(): " << mol->getName() << endl;
   this->mol = mol;
}

void confSwarmOptimizer::init(float id, float c1, float c2, int popSize, int gen) {
  //cout <<"You are in init"<<endl;
  this->id = id;
  this->c1 = c1;
  this->c2 = c2;
  this->popSize = popSize;
  this->gen = gen;
 
  //Set the Atom Types
  //dt::molecule *dtmol = new dt::molecule;
  dt::molPtr dtmol( new dt::molecule );
  molAdapter::mol2molecule(dtmol, mol);
  dt::dType d;
  d.setGaffTypes(dtmol);
  molAdapter::update(mol, dtmol);
  //delete dtmol;
  
  //Calculate the Charges
  charge *chg = new charge();
  //cout <<"Calculating charges"<<endl;
  chg->setUp(mol, "AM1-BCC");
  chg->run();
  
  //Set bond, angle, torsion, and nonBond terms
  //cout <<"FF setup"<<endl;
  forceField *ff = new forceField();
  string ffType = "GAFF";
  ff->buildLists(mol, ffType );
  delete ff;
  
  if (mol->angles.size() == 0) mol->setAngles();
  if (mol->torsions.size() == 0) mol->setTorsions();
  if (mol->nonBonds.size() == 0) mol->setNonBonds(100);
  
  
  
  cs = new confSwarm(popSize, id, c1, c2, mol);
}

void confSwarmOptimizer::run() {
  //cout <<"running my ass off"<<endl;
  //cout <<"molName: " << mol->getName() << endl;

  globalBest = 10000000;
  //cs->printPop();
  //int gen = 120;
  //id = 1.0;
  //c1 = 1.0;
  //c2 = 1.0;
  float idHold = id;
  QString outFile = mol->getName();
  
  outFile += "_pso.run";
  ofstream out(outFile.latin1(), ios::out);
  out <<"score\tvelocity\tw\tc1\tc2\tbonds"<<endl;
  
  //for (float j=0; j<1; j+=.02) {
  //id = j;
  //cout <<"gen"<<setw(15)<<"avg"<<setw(15)<<"best"<<setw(10)<<"id"<<setw(10);
  //cout <<"velocity"<<endl;
  
  float idAdjust = id/gen;
  float cAdjust = c2/gen;
  //cout <<"cAdjust: " << cAdjust << endl;
  int ts = 0;
  cin >> ts;
  
  float avgRunScore = 0;
  float avgVelScore = 0;
  
  float xPercent = 0.02;
  
  bool set1 = true;
  bool set2 = false;
  //cs->scoreSwarm();
  int count = 0;
  for (float i=0; i<gen; i++) {
     cs->scoreSwarm();
     cs->updateSwarmVelocities(id, c1, c2);
     cs->updateSwarmPositions();
          
     float avgScore = cs->getAvgScore();
     float bestScore = cs->getBestScore();
     float avgVel = cs->getAvgVelocity();
     
     if (i >=20) {
       avgRunScore += avgScore;
       avgVelScore += avgVel;
     }
     //cout << i <<setw(15) << bestScore << setw(15)  << avgVel << "\t";
     
     
     cs->printAvgCValues();
     
     if (avgVel > .9)
        id -= idAdjust;
    
     
     if (cs->avgC1 == 1 && cs->avgC2 == 0)
        break;
  }  
  
  avgRunScore /= (gen-20);
  avgVelScore /= (gen-20);
  
  
  
  //cout <<"avgRunScore: " << avgRunScore << endl;
  //cout <<"avgVelScore: " << avgVelScore << endl;  
  
  
  out <<avgRunScore <<"\t" << avgVelScore <<"\t";
  out <<id<<"\t"<<c1<<"\t"<<c2<<"\t"<<cs->rotBondNum()<<endl;
  //}
  cs->saveBest();
  cs->saveAll("pso_all.sdf");
}



