/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include <iostream>
#include "buildHelpDialog.h"
using namespace std;


void builderDialog::atomChangeSlot()
{
    ////////cout <<"Atom Change Slot"<<endl;
    if (atomGroup->selectedId() == 0)
 otherAtom->setCurrentItem(15);
   else
   if (atomGroup->selectedId() == 1)
               otherAtom->setCurrentItem(59);
  else
  if (atomGroup->selectedId() == 2)
            otherAtom->setCurrentItem(67);
  else
   if (atomGroup->selectedId() == 3) //sulfer
           otherAtom->setCurrentItem(85);
   else
   if (atomGroup->selectedId() == 4) //phos
          otherAtom->setCurrentItem(69);
   else  
   if (atomGroup->selectedId() == 5) //Br
          otherAtom->setCurrentItem(14);
   else 
   if (atomGroup->selectedId() == 6) //Cl
          otherAtom->setCurrentItem(20);
   else 
   if (atomGroup->selectedId() == 7) // I
          otherAtom->setCurrentItem(45);
   else 
   if (atomGroup->selectedId() == 8) // F
          otherAtom->setCurrentItem(32);
   else
    if (atomGroup->selectedId() == 9) // H
          otherAtom->setCurrentItem(39);
   
   //Make sure that one of the bond types is selected
   if (!singleBond->isChecked() &&
       !doubleBond->isChecked() &&
       !tripleBond->isChecked()) 
   {
       singleBond->setChecked(true);
   }
       
   
   //Now we unselect all rings
   sp2_8->setOn(false);
   sp2_7->setOn(false);
   sp2_6->setOn(false);
   sp2_5->setOn(false);
   
   sp3_8->setOn(false);
   sp3_8->setOn(false);
   sp3_7->setOn(false);
   sp3_6->setOn(false);
   sp3_5->setOn(false);
   
   //chiral->setChecked(false);

}


void builderDialog::ringChangeSlot()
{
    carbon->setOn(false);
    nitrogen->setOn(false);
    oxygen->setOn(false);
    sulfer->setOn(false);
    phos->setOn(false);
    bromine->setOn(false);
    chlorine->setOn(false);
    iodine->setOn(false);
    flourine->setOn(false);
    hydrogen->setOn(false);
    //chiral->setChecked(false);
    
    singleBond->setChecked(false);
    doubleBond->setChecked(false);
    tripleBond->setChecked(false);
}


void builderDialog::modeChangedSlot()
{
    if (modeGroup->selectedId() == 2) {
 ringGroup->setEnabled(false);
                atomGroup->setEnabled(false);
 bondGroup->setEnabled(false);

// chiral->setEnabled(false);
               addH->setEnabled(false);

   }
    else
    if ( modeGroup->selectedId() == 1) {
 ringGroup->setEnabled(false);
                atomGroup->setEnabled(true);
                bondGroup->setEnabled(true);
                //hGroup->setEnabled(true);
// chiral->setEnabled(true);
                strucGroup->setEnabled(true);
 addH->setEnabled(true);
    }
    else {
 ringGroup->setEnabled(true);
                atomGroup->setEnabled(true);
 bondGroup->setEnabled(true);
                //hGroup->setEnabled(true);
 //chiral->setEnabled(true);
                strucGroup->setEnabled(true);
 addH->setEnabled(true);
    }
 
}


void builderDialog::chiralFlipSlot()
{
    carbon->setOn(false);
    nitrogen->setOn(false);
    oxygen->setOn(false);
    sulfer->setOn(false);
    phos->setOn(false);
    bromine->setOn(false);
    chlorine->setOn(false);
    iodine->setOn(false);
    flourine->setOn(false);
    hydrogen->setOn(false);
    
    sp2_8->setOn(false);
   sp2_7->setOn(false);
   sp2_6->setOn(false);
   sp2_5->setOn(false);
   
   sp3_8->setOn(false);
   sp3_8->setOn(false);
   sp3_7->setOn(false);
   sp3_6->setOn(false);
   sp3_5->setOn(false);
}


void builderDialog::bondChangeSlot()
{
  sp2_8->setOn(false);
   sp2_7->setOn(false);
   sp2_6->setOn(false);
   sp2_5->setOn(false);
   
   sp3_8->setOn(false);
   sp3_8->setOn(false);
   sp3_7->setOn(false);
   sp3_6->setOn(false);
   sp3_5->setOn(false);
   
   //chiral->setChecked(false);
}


void builderDialog::helpSlot()
{
    buildHelpDialog *dialog = new buildHelpDialog(0, "Help", true);
    
    if (dialog->exec()) {
 
    }
}
























