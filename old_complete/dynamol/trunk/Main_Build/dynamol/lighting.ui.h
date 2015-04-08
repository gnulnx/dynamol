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
#include <vector>
#include "lighting.h"
#include "helpdialog.h"

using namespace std;

void Lighting::setGenLightProp(vector<float> &pos, vector<float> &amb, vector<float> &spec, vector<float> &dif)
{
    genLightPosX->setValue(pos[0]);
    genLightPosY->setValue(pos[1]);
    genLightPosZ->setValue(pos[2]);
    
     int value = (amb[0]*100)-1;
    genLightAmbR->setValue(value);
    value = (amb[1]*100)-1;
    genLightAmbG->setValue(value);
    value = (amb[2]*100)-1;
    genLightAmbB->setValue(value);
   
    value = (dif[0]*100)-1;
    genLightDifR->setValue(value);
    value = (dif[1]*100)-1;
    genLightDifG->setValue(value);
    value = (dif[2]*100)-1;
    genLightDifB->setValue(value);
    
    value = (spec[0]*100)-1;
    genLightSpecR->setValue(value);
    value = (spec[1]*100)-1;
    genLightSpecG->setValue(value);
    value = (spec[2]*100)-1;
    genLightSpecB->setValue(value);
    
}


void Lighting::helpSlot()
{
    helpDialog *dialog = new helpDialog(this, "FUCK YOU", true);
    dialog->show();
}


void Lighting::setRibLightProp( vector<float> &pos, vector<float> &amb, vector<float> &spec, vector<float> &dif )
{
    genLightPosX_3->setValue(pos[0]);
    genLightPosY_3->setValue(pos[1]);
    genLightPosZ_3->setValue(pos[2]);
    
     int value = (amb[0]*100)-1;
    genLightAmbR_3->setValue(value);
    value = (amb[1]*100)-1;
    genLightAmbG_3->setValue(value);
    value = (amb[2]*100)-1;
    genLightAmbB_3->setValue(value);
   
    value = (dif[0]*100)-1;
    genLightDifR_3->setValue(value);
    value = (dif[1]*100)-1;
    genLightDifG_3->setValue(value);
    value = (dif[2]*100)-1;
    genLightDifB_3->setValue(value);
    
    value = (spec[0]*100)-1;
    genLightSpecR_3->setValue(value);
    value = (spec[1]*100)-1;
    genLightSpecG_3->setValue(value);
    value = (spec[2]*100)-1;
    genLightSpecB_3->setValue(value);
}


void Lighting::applySlot()
{
    emit apply();
}






























