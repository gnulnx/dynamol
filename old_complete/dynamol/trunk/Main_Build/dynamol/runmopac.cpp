/***************************************************************************
 *   Copyright (C) 2004 by jfurr                                           *
 *   jfurr@jabba.albmolecular.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "runmopac.h"
#include "qprocess.h"
#include <iostream>
#include <iomanip>

using namespace std;

runMopac::runMopac(QWidget *parent, const char *name)
 : QWidget(parent, name)
{
}


runMopac::~runMopac()
{
}

void runMopac::start() {
   ////////////cout <<"Yep you are here"<<endl;
   done = false;
   QProcess *proc = new QProcess;
   proc->addArgument( "mopac" );
   proc->addArgument( "mol" );
   proc->start();
   connect( proc, SIGNAL(processExited()), this, SLOT(mopacDone()) );
   //while (!done){}
}

void runMopac::mopacDone() {
  ////////////cout <<"mopacDone()"<<endl;
  done = true;
}

bool runMopac::Done() {return this->done;}





























