/***************************************************************************
                          enumTypes.h  -  description
                             -------------------
    begin                : Sat Jan 3 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef ENUMTYPES_H
#define ENUMTYPES_H

#define PI 3.1415926535
#define ARCFIX 57.2958

enum CPK_RADIUS 			{DEFAULT, ATOM_TYPE};
enum PARAMETER  			{NORMAL, MM2, MM3, OPLSAA};
enum BONDRENDER   		{STICK, WIRE, NOBOND};
enum ATOMRENDER   		{BALL, PNT, CPK};
enum DISPLAY_TYPE        {HIDE_RIBBON, HIDE_ALL, SHOW_ALL, SHOW_BACKBONE, HIDE_BACKBONE, HIDE_SIDE_CHAIN, SHOW_SIDE_CHAIN, HIDE_HYDROGEN, SHOW_HYDROGEN, HIDE_SELECTED};
enum RIBBON_TYPE      {FLAT, CYLINDER, CARTOON};

enum PROT_TYPE        {BACKBONE, SIDE_CHAIN, NON_PROTEIN};
enum FRAG_TYPE        {HELIX, SHEET, TURN};


#endif




































