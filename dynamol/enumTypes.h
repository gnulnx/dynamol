/***************************************************************************
                          enumTypes.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by John Furr
    email                : john.furr@gmail.com


    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

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




































