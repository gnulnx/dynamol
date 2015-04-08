/****************************************************************************
** Form implementation generated from reading ui file 'buildDialog.ui'
**
** Created: Sun Apr 3 16:18:49 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "buildDialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "buildDialog.ui.h"
static const char* const image0_data[] = { 
"104 101 174 2",
".c c #000000",
"#B c #010101",
"#b c #020202",
".h c #030303",
".o c #040404",
".7 c #050505",
".W c #060606",
"#t c #070707",
".P c #080808",
".r c #090909",
".m c #0a0a0a",
".j c #0b0b0b",
".g c #0c0c0c",
"#E c #0d0d0d",
"#G c #0e0e0e",
".d c #0f0f0f",
"#Q c #101010",
"#J c #111111",
"#N c #121212",
"a. c #131313",
"#K c #141414",
"#H c #151515",
"#6 c #161616",
"as c #171717",
"aQ c #181818",
".b c #191919",
"#2 c #1a1a1a",
"#z c #1b1b1b",
"#W c #1c1c1c",
"aR c #1d1d1d",
"#w c #1e1e1e",
".s c #1f1f1f",
"am c #202020",
"#1 c #212121",
".Q c #222222",
"#q c #242424",
".U c #252525",
"aP c #262626",
".n c #272727",
".X c #282828",
"aC c #292929",
"#m c #2a2a2a",
".Z c #2b2b2b",
"aB c #2c2c2c",
"ax c #2d2d2d",
".3 c #2e2e2e",
".a c #303030",
"aI c #313131",
"av c #323232",
"#c c #333333",
"## c #343434",
"aO c #353535",
"aJ c #363636",
".9 c #373737",
"#e c #383838",
"at c #393939",
"#4 c #3a3a3a",
"#h c #3b3b3b",
"#5 c #3c3c3c",
"aK c #3d3d3d",
"#k c #3e3e3e",
"#7 c #3f3f3f",
".5 c #404040",
"#8 c #414141",
"#o c #424242",
"aL c #434343",
"#9 c #444444",
".1 c #454545",
"aM c #464646",
"a# c #474747",
"aG c #484848",
"aa c #494949",
"#v c #4a4a4a",
"ab c #4b4b4b",
"aN c #4c4c4c",
".V c #4d4d4d",
"ac c #4e4e4e",
"aE c #4f4f4f",
"ad c #505050",
".T c #515151",
"#C c #525252",
"ae c #535353",
".O c #545454",
"aw c #555555",
"#F c #565656",
"ay c #575757",
".S c #585858",
".p c #595959",
".N c #5a5a5a",
"af c #5b5b5b",
"#3 c #5c5c5c",
".k c #5d5d5d",
"ag c #5e5e5e",
"#L c #5f5f5f",
".i c #606060",
"aD c #616161",
"ah c #626262",
".Y c #636363",
"ai c #646464",
"aF c #656565",
"aH c #666666",
"#S c #676767",
".0 c #686868",
"aj c #696969",
"aA c #6a6a6a",
"az c #6b6b6b",
"#V c #6c6c6c",
".4 c #6d6d6d",
"#P c #6e6e6e",
"ak c #6f6f6f",
"#Y c #707070",
"al c #717171",
"#X c #727272",
".8 c #737373",
"#Z c #747474",
"#U c #767676",
"#a c #777777",
"#0 c #787878",
"#R c #797979",
"an c #7b7b7b",
"#f c #7c7c7c",
"#O c #7d7d7d",
"ao c #7e7e7e",
"#i c #808080",
"ap c #828282",
"#l c #858585",
"#I c #868686",
"aq c #888888",
"#p c #898989",
"#A c #8a8a8a",
"#s c #8d8d8d",
"#x c #8e8e8e",
"#u c #919191",
".e c #929292",
"#r c #939393",
"ar c #949494",
"#y c #959595",
"#n c #969696",
"#D c #989898",
"#j c #9c9c9c",
"#g c #9e9e9e",
"#d c #9f9f9f",
"#. c #a1a1a1",
"#M c #a2a2a2",
"au c #a3a3a3",
".6 c #a4a4a4",
".2 c #a7a7a7",
"#T c #a8a8a8",
".M c #a9a9a9",
".L c #aaaaaa",
".K c #ababab",
".J c #acacac",
".t c #adadad",
".I c #aeaeae",
".H c #afafaf",
".q c #b0b0b0",
".G c #b1b1b1",
".l c #b2b2b2",
".F c #b3b3b3",
".E c #b4b4b4",
".f c #b5b5b5",
".D c #b6b6b6",
".C c #b7b7b7",
".B c #b8b8b8",
".A c #b9b9b9",
".# c #bababa",
".z c #bbbbbb",
".y c #bcbcbc",
".x c #bdbdbd",
".w c #bebebe",
".v c #bfbfbf",
".u c #c0c0c0",
".R c #c1c1c1",
"Qt c #c2c2c2",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.a.b.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.d.eQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.f.g.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.h.c.iQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.f.j.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.kQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.l.m.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.n.o.c.c.c.pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.q.r.c.c.c.c.s.t.u.v.v.w.w.w.x.y.z.z.z.#.A.B.B.B.C.D.f.f.f.E.F.l.l.l.G.q.H.I.I.J.J.K.J.K.L.M.N.c.c.c.c.c.OQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.I.P.c.c.c.c.Q.q.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.S.c.c.c.c.c.TQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J.P.c.c.c.c.U.l.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.k.c.c.c.c.c.VQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.q.W.c.c.c.c.X.E.R.R.R.R.R.v.R.R.w.R.R.R.u.R.R.u.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.RQt.R.R.R.Y.c.c.c.c.c.VQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.M.W.c.c.c.c.Z.f.R.R.R.R.R.RQtQt.R.R.R.R.RQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.0.c.c.c.c.c.1QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.2.W.c.c.c.c.3.C.R.R.R.R.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.4.c.c.c.c.c.5QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.6.7.c.c.c.c.Z.B.R.R.R.R.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.8.c.c.c.c.c.9QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#..o.c.c.c.c##.A.R.R.R.R.R.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R#a#b.c.c.c.c#cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#d.o.c.c.c.c#e.#.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#f#b.c.c.c.c.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#g.h.c.c.c.c#h.z.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#i.h.c.c.c.c.ZQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt#j.h.c.c.c.c#k.x.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#l.7.c.c.c.c#m.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt#n.h.c.c.c.c#o.x.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#p.7.c.c.c.c#q.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt#r#b.c.c.c.c#k.w.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#s#t.c.c.c.c.Q.RQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQt#u#b.c.c.c.c#v.v.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#n.W.c.c.c.c#w.uQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQt#x#b.c.c.c.c.V.v.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#y.j.c.c.c.c#z.vQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt#A#B.c.c.c.c#C.u.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#D#E.c.c.c.c.b.xQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQt#A.c.c.c.c.c#F.u.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#j#G.c.c.c.c#H.RQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQt#I#B.c.c.c.c.N.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#d#J.c.c.c.c#K.zQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQt#i#B.c.c.c.c#L.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#M#K.c.c.c.c#N.#QtQtQtQtQtQtQtQt",
"QtQtQtQtQt#O.c.c.c.c.c#P.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.t#H.c.c.c.c#Q.BQtQtQtQtQtQtQt",
"QtQtQtQt#R.c.c.c.c.c#S.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#T.b.c.c.c.c#G.CQtQtQtQtQtQt",
"QtQtQt#U.c.c.c.c.c#V.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.K#W.c.c.c.c#E.EQtQtQtQtQt",
"QtQt#X.c.c.c.c.c#Y.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.I.s.c.c.c.c.j.lQtQtQtQt",
"Qt#T#B.c.c.c#B#Z.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.q.Q.c.c.c.c.pQtQtQtQt",
"Qt#Y.c.c.c#B#0.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.l.U.c.c.W#1#pQtQtQt",
".M.g.h.c#G#f.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.RQtQt.R.E#2#2.c.c.XQtQtQt",
".i.c.c.c#3.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.RQtQt.R.R.a.c.c.c#WQtQtQt",
".i.c.c.c.i.uQtQtQt.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQtQtQt##.c.c.c#2QtQtQt",
".O.c.c.c.iQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQtQtQt#e.c.c.c.sQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQtQtQt#4.c.c.c#2QtQtQt",
".i.c.c.c.iQtQtQtQt.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQtQtQt#5.c.c.c#6QtQtQt",
".i.c.c.c#LQtQtQtQtQtQtQtQt.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQt.RQtQtQt#7.c.c.c#2QtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQt.RQtQtQt#8.c.c.c.bQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQt.RQtQtQt#9.c.c.ca.QtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.uQtQtQt.RQtQtQta#.c.c.c#NQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQtQt.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQt.RQtQtQtaa.c.c.c#HQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQtQt.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQt.RQtQtQtab.c.c.c#JQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQtQt.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQt.R.RQtQtQtac.c.c.c.dQtQtQt",
".S.c.c.c#LQtQtQtQtQtQtQtQtQtQt.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQt.v.R.RQtQtQtad.c.c.c#JQtQtQt",
".i.c.c.c.iQtQtQt.wQtQtQtQtQt.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQt.R.RQtQtQtae.c.c.c#JQtQtQt",
".i.c.c.c.iQtQtQt.wQtQtQtQtQt.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQt.R.RQtQtQt#F.c.c.c.gQtQtQt",
".i.c.c.c.iQtQtQt.u.RQtQtQtQt.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQt.R.RQtQtQt.p.c.c.c.gQtQtQt",
".i.c.c.c.iQtQtQt.u.RQtQtQtQt.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQt.R.RQtQtQtaf.c.c.c#EQtQtQt",
".i.c.c.c.iQtQtQt.R.RQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.uQtQt.R.RQtQtQtag.c.c.c.mQtQtQt",
".i.c.c.c.iQtQtQtQt.RQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQt.R.RQtQtQt.i.c.c.c.rQtQtQt",
".i.c.c.cagQtQtQtQt.RQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.RQtQtQtQt.RQtQtQtah.c.c.c.mQtQtQt",
".i.c.c.c#LQtQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.RQtQtQtQt.RQtQtQtai.c.c.c.rQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQtQt.RQtQtQt#S.c.c.c#tQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQt.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQtQt.RQtQtQtaj.c.c.c#tQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQt.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQtQt.RQtQtQt#V.c.c.c#tQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQt.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQtQt.RQtQtQtak.c.c.c.7QtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQt.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.RQtQtQtQtQt.RQtQtQtal.c.c.c.7QtQtQt",
".1.c.c.c.iQtQtQtQtQtQtQtQtQt.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQt.RQtQtQt.8.c.c.c.7QtQtQt",
"am.c.c.c.iQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQt.RQtQtQt#U.c.c.c.oQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQtQtQtQt#R.c.c.c.hQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.RQtQtQtQtQtQtQtan.c.c.c.hQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.RQtQtQtQtQtQtQtao.c.c.c.hQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.RQtQtQt.RQtQtQt#i.c.c.c#bQtQtQt",
".i.c.c.c.iQtQtQtQtQt.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQt.RQtQtQtap.c.c.c#BQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQtQtQt#l.c.c.c#BQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.uQtQtQtQtQtQtaq.c.c.c#BQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.RQtQtQt.RQtQtQt#A.c.c.c.cQtQtQt",
".i.c.c.cagQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.RQt.R.R.RQtQt#s.c.c.c.cQtQtQt",
".i.c.c.c.i.RQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.RQtQt.Rar#K.c.c.cQtQtQt",
"#u.r.o#zaq#U.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.u#F#jas#BatQtQtQt",
"Qt#z.W.c#G.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.uae.c#b.c.m#TQtQtQt",
"Qtal.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.u.O.c.c.c.c.cauQtQtQt",
"Qt.uav.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.O.c.c.c.c.c#XQtQtQtQt",
"QtQt.u.3.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.Raw.c.c.c.c.c#YQtQtQtQtQt",
"QtQtQt.uax.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R#F.c.c.c.c.c#PQtQtQtQtQtQt",
"QtQtQtQt.uax.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.Ray.c.c.c.c.cazQtQtQtQtQtQtQt",
"QtQtQtQtQt.vax.c.c.c.c.caA.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.Ray.c.c.c.c.caAQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQt.vax.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.p.c.c.c.c.c.0QtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQt.u.X.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.N.c.c.c.c.c.8QtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQt.vaB.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.N.c.c.c.c.c.YQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt.vaB.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.Raf.c.c.c.c.c.iQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQt.v.Z.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R#3.c.c.c.c.c#LQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQt.w.Z.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.O.c.c.c.c.c.kQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.w#m.c.c.c.c.caz.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.Rag.c.c.c.c.cafQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.w#m.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R#L.c.c.c.c.c.SQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt.v.n.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.i.c.c.c.c.cagQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.w#m.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.i.c.c.c.c.c.OQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.waC.c.c.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.RaD.c.c.c.c.c.TQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.w.X.c.c.c.c.caj.R.R.R.R.R.R.R.RQtQtQt.R.R.R.RQtQt.R.RQt.RQtQt.R.R.R.RQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.RQtQt.R.R.R.R.R.R.Rah.c.c.c.c.caEQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.w#m.c.c.c.c.c#X.R.R.R.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.0.c.c.c.c.c.VQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.waC.c.c.c.c.caj.R.R.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.R.Rai.c.c.c.c.cabQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.x.X.c.c.c.c.caj.R.R.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.RaF.c.c.c.c.caGQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.w.n.c.c.c.c.caj.R.R.R.R.u.R.R.RQtQtQtQtQtQtQtQt.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.RQtQt.R.R.RaH.c.c.c.c.c#kQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.xaB.c.c.c.c.caj.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.RaH.c.c.c.c.c#9QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.x.Z.c.c.c.c.caj.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R#S.c.c.c.c.c#oQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.y#m.c.c.c.c.caj.wQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R#V.c.c.c.c.c.5QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.y#m.c.c.c.c.ca#aIav##aJaJ#eat#4#5aK#k#7#8#oaL#9aMa#aa#vabaNacaEad#Caeawawayay.p.Naf.kag#L#V.c.c.c.c#k.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.y#m.c.c.c#N.n.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.5.c.c.c#h.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.yaC.c#B.h.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.h.c#k.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.waaaO.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.caP#L.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Lat#q.X.U.s#1aP.saQ.c#w#z.s#1#2#2am#zaQaR#WasaQ#W#6#H#2asa.#HaQa.a.asa.#Ja.a..P.PQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtauQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};

static const char* const image1_data[] = { 
"92 94 211 2",
".c c #000000",
"bi c #000001",
"#9 c #010101",
"#A c #010102",
".1 c #020202",
"#x c #020203",
"#I c #030303",
"#m c #030304",
".y c #040404",
"ay c #050505",
"#u c #060606",
"#c c #070707",
"bp c #07070e",
"#S c #080808",
".B c #090909",
".G c #0a0a0a",
"aF c #0b0b0b",
"aH c #0c060c",
".9 c #0c0c0c",
"aG c #0c0c18",
"#1 c #0e0e0e",
".P c #0f0f0f",
"bn c #0f0f14",
".l c #101010",
"a4 c #111111",
"bc c #121212",
"#L c #131313",
"aB c #131326",
".H c #141428",
"a6 c #151515",
"bj c #161616",
"aM c #171717",
".p c #181818",
"#X c #181830",
"#R c #181831",
"bl c #191932",
".h c #1b1b1b",
".f c #1c1c1c",
".K c #1d1d1d",
"aL c #1e1e1e",
"#J c #1f1f1f",
"#F c #202020",
".7 c #202040",
"#E c #212121",
"aI c #222222",
"#Z c #232323",
"ba c #242424",
".i c #261326",
".6 c #272727",
"#P c #282828",
"#N c #292929",
".d c #2a2a2a",
".x c #2b2b2b",
"#U c #2d2d2d",
"bb c #2d342d",
"#4 c #2e2e2e",
"#5 c #2f2f2f",
"#d c #2f362f",
".Y c #303030",
"#l c #313131",
"bo c #321932",
"#0 c #323232",
"a8 c #333333",
"#e c #343434",
".Q c #344e34",
"#z c #353535",
".F c #363636",
"aq c #373737",
"aZ c #393939",
"b. c #3a3a3a",
"a9 c #3b1d3b",
"#k c #3b3b3b",
".T c #3c3c3c",
"bg c #3d1e3d",
"aS c #3d3d3d",
"bm c #3e1f3e",
"aa c #3e3e29",
"as c #3f3f3f",
".O c #404040",
"a. c #41412b",
"a# c #414141",
"#7 c #43432c",
"#G c #434343",
"at c #44442d",
"#w c #444444",
"#s c #454545",
"ab c #464646",
".q c #47472f",
"ar c #484830",
"ag c #494949",
".X c #4a4a4a",
"ap c #4b4b32",
"ae c #4b4b4b",
"#o c #4c4c4c",
".m c #4c4c65",
"av c #4d4d4d",
"a2 c #4e4e34",
"a0 c #4e4e4e",
".g c #4f4f4f",
"ad c #505050",
"bf c #525237",
"al c #535355",
".I c #53536f",
".5 c #545454",
".t c #555555",
"aj c #57575a",
".w c #585858",
"bh c #595977",
"ak c #5a5a5a",
"aC c #5b5b5b",
"be c #5c5c5c",
"bq c #5e5e3f",
"#b c #5e5e5e",
".# c #606080",
"aJ c #626262",
".E c #636363",
"#2 c #646464",
".2 c #656565",
"#B c #676767",
"ao c #686868",
"aP c #696969",
"aN c #6a6a6a",
".j c #6c6c6c",
".N c #6d6d6d",
"#j c #6f6f6f",
"aQ c #707070",
"#r c #737373",
"#K c #758675",
"#v c #767676",
".W c #777777",
"aU c #787878",
".z c #797979",
"aX c #7a7a7a",
"#D c #7b7b7b",
"b# c #7c7c7c",
"#T c #7d7d7d",
".C c #7e7e7e",
"aW c #7f7f7f",
".8 c #808080",
"aV c #838383",
".4 c #848484",
"#C c #859885",
".v c #868686",
"a7 c #878787",
"#Q c #8a8a8a",
"bd c #8b8b8b",
"#a c #8c8c8c",
"a1 c #8d8d8d",
"#W c #8f8f8f",
".D c #909090",
"#. c #929292",
".e c #929296",
"#t c #92a892",
"#M c #939393",
"#3 c #949494",
"aR c #94b1b1",
"bk c #959595",
"#i c #969696",
"#H c #989898",
".M c #999999",
".r c #99999c",
"aK c #99b8b8",
"a5 c #9a9a9a",
"#6 c #9b9b9b",
".Z c #9b9b9f",
"aY c #9c9c9c",
"#8 c #9d9d9d",
"#V c #9e9e9e",
".0 c #9eb69e",
".L c #9f9f9f",
".R c #9f9fa3",
"#q c #a0a0a0",
"an c #a0a0a4",
".a c #a0c0c0",
"#Y c #a1a1a1",
"aT c #a3a3a3",
".V c #a4a4a4",
"ac c #a5a5a5",
"au c #a6a6a6",
"a3 c #a8a8a8",
".s c #a8c1a8",
"#g c #a9a9a9",
"aE c #aaaaaa",
"ax c #ababab",
"af c #acacac",
"#n c #adadad",
"#O c #aeaeae",
"ai c #afafaf",
".u c #b1b1b1",
".b c #b1cbb1",
"aA c #b2b2b2",
"am c #b3b3b3",
".S c #b4b4b4",
"aO c #b597b5",
".U c #b5b5b5",
"## c #b6b6b6",
"#y c #b7b7b7",
"ah c #b8b8b8",
".o c #b9b9b9",
"#p c #bababa",
".3 c #bbbbbb",
"aD c #bbd6bb",
"#f c #bcbcbc",
"az c #bcd8bc",
".n c #bdbdbd",
"#h c #bebebe",
"aw c #bedabe",
".J c #bfbfbf",
".k c #bfdbbf",
"Qt c #c0c0c0",
".A c #c0dcc0",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.c.c.c.c.c.d.eQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.f.g.h.c.c.c.c.c.i.j.kQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.l.c.c.c.c.c.c.c.c.c.c.c.m.nQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.o.c.c.c.c.c.c.p.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.q.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.s.c.c.c.c.c.c.t.u.v.w.x.y.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.x.z.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.B.CQtQtQtQtQt.o.D.E.F.G.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.H.IQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J.c.c.c.c.c.c.K.LQtQtQtQtQtQtQtQtQtQtQt.M.N.O.P.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.Q.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.S.c.c.c.c.c.c.T.UQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.V.W.X.f.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.Y.Z.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.0.c.c.c.c.c.1.2.JQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.3.4.5.6.1.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.7.8QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.9#.QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt###a#b.Y#c.c.c.c.c.c.c.c.c.c.c#d#e.c.8QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#f.c.c.c.c.c.c.6#gQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#h#i#j#k.B.c.c.c.c.c.c#l#c#m.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#n.c.c.c.c.c.c#o#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J#q#r#s.p.c.c.c.c.c.c.8QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#t.c.c.c.c.c#u#vQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt###w.c.c.c#x.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.p.MQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.3.p.c.c.c.c.8QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt#y.c.c.c.c.c.c#z.uQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#v.c.c.c#A.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.V.c.c.c.c.c.c#BQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#f.h.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQt#C.c.c.c.c.c.9.vQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#D.c.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt.n.c.c.c.c.c.c#E.VQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#h#F.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQt.u.c.c.c.c.c.c#G#yQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.8.c.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQt#H.c.c.c.c.c#I.NQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J#J.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQt#K.c.c.c.c.c#L#MQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.v.c.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQt#p.c.c.c.c.c.c#N#OQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J#P.c.c.c.c.AQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQt#g.c.c.c.c.c.c.5#fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Q.c.c.c.c#RQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQt.D.c.c.c.c.c#S#TQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#U.c.c.c.c.AQtQtQtQtQtQtQtQtQtQtQt",
"Qt.A.c.c.c.c.c.f#VQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#W.c.c.c.c#XQtQtQtQtQtQtQtQtQtQtQt",
"#Y.c.c#Z.c.c.T.SQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#0.c.c.c.c.AQtQtQtQtQtQtQtQtQtQt",
"#W.c.c.c#1#2.JQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#3.c.c.c.c#4QtQtQtQtQtQtQtQtQtQt",
"#W.c.c.c#5QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.F.c.c.c.cQtQtQtQtQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#6.c.c.c.c#7QtQtQtQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.T.c.c.c.c.JQtQtQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#8#9.c.c.ca.QtQtQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta#.c.c.c.c#hQtQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Y.1.c.c.caaQtQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtab.c.c.c.c.nQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtac#I.c.c.cadQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtae.c.c.c.c#fQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#g.1.c.c.c#oQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.g.c.c.c.c#pQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaf#u.c.c.cagQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.t.c.c.c.cahQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtai#S.c.c.cajQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtak.c.c.c.c##QtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.u.G.c.c.calQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#b.c.c.B.cQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtam.c.c.l.canQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.C.c.yad.c.8Qt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J#Z.c.c.c.cQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.v.c.c.c.c.jQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#N.c.c.c.cQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#a.c.c.c.caoQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Y.c.c.c.cQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#3.c.c.c.capQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaq.c.c.c.cQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#6.c.c.c.carQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtas.c.c.c.cQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Y#9.c.c.catQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtab.c.c.c.c.JQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtau#I.c.c.c.xQtQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtav.c.c.c.cawQtQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaxay.c.c.c.HQtQtQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.5.c.c.c.cazQtQtQtQtQtQtQtQt",
"#W.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaA#c.c.c.caBQtQtQtQtQtQtQtQtQt",
"#W.c.c.c#4QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaC.c.c.c.caDQtQtQtQtQtQtQtQtQt",
"#W.c.c.c#SacaEQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtamaF.c.c.c.cQtQtQtQtQtQtQtQtQtQt",
"#YaGaH.c#9aI#u#vQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaJ.c.c.c.caKQtQtQtQtQtQtQtQtQtQt",
"Qt.8.caLaM.c.c.cav#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#y.P.c.c.c.cQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQt.c.c.c.c.c.c#NaEQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaN.c.c.c.caOQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQt.c.c.c.c.c.c.l#WQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.o#L.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQt#e.c.c.c.c.c#IaP.JQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaQ.c.c.c.caRQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQt.W.c.c.c.c.c.caS#yQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#haM.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQt#h.c.c.c.c.c.c#FaTQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaU.c.c.c.c#rQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.GaVQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#h.K.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtaq.c.c.c.c.c.caC.nQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaW.c.c.c.caQQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtaX.c.c.c.c.c.c#e.uQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J#Z.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.laYQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.v.c.c.c.c.jQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c#u.WQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.d.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaZ.c.c.c.c.c.ca0.3QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta1.c.c.c.ca2QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#T.c.c.c.c.c.c.daEQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta3#J.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.ca4#WQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#fa5.Na#a6.c.c.c.c.capQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c#IaNQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#fa7#ba8#u.c.c.c.c.c.c#I#9.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta9.c.c.c.c.c.cb..oQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta3b#adba.1.c.c.c.c.c.c.c.c.c.cbb.c.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.C.c.c.c.c.c.c#FaTQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#6.Na#bc.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.7QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.caF.4QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Ubd#ba8.B.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c#0b#.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.cbe.nQtQtQtQtQtQtQtQtQtQta3b#adba.1.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.cbfanQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtbg.c.c.c.c.c.c#z.uQtQtQtQt#fa5.Na#a6.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.cbhQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.8.cbi.c.c.c.cbjbkbd#ba8.B.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.cbl#T.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.y.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.caqanQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c#9.c.c.c.c.c.c.c.c.c.c.c.c.cbhanQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtbm.cbn.c.1.c.c.c.c.c.c.cbob#.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.8.c.cbp.c.c.caqan.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.cbq.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};

static const char* const image2_data[] = { 
"92 94 225 2",
".c c #000000",
"bx c #000001",
"ae c #010101",
"#P c #010102",
".1 c #020202",
"#E c #020203",
"ac c #030303",
"#q c #030304",
".y c #040404",
"#5 c #050505",
"#h c #060606",
"#c c #070707",
"bD c #07070e",
"#G c #080808",
".B c #090909",
".G c #0a0a0a",
"a9 c #0b0b0b",
"b# c #0c060c",
".9 c #0c0c0c",
"b. c #0c0c18",
"av c #0e0e0e",
".P c #0f0f0f",
"bB c #0f0f14",
".l c #101010",
"bl c #111111",
"aU c #121212",
"#Z c #131313",
"a6 c #131326",
".H c #141428",
"bn c #151515",
"by c #161616",
"aa c #171717",
".p c #181818",
"as c #181830",
"ap c #181831",
"bz c #191932",
"#0 c #1a1a1a",
".h c #1b1b1b",
".f c #1c1c1c",
".K c #1d1d1d",
"#N c #1e1e1e",
"af c #1f1f1f",
"#9 c #202020",
".7 c #202040",
"#2 c #212121",
"#B c #222222",
"at c #232323",
"br c #242424",
".i c #261326",
"#i c #262626",
".6 c #272727",
"ao c #282828",
"ak c #292929",
".d c #2a2a2a",
".x c #2b2b2b",
"a4 c #2c2c2c",
"ab c #2d2d2d",
"bs c #2d342d",
"ay c #2e2e2e",
"az c #2f2f2f",
"#d c #2f362f",
".Y c #303030",
"#p c #313131",
"bC c #321932",
"au c #323232",
"#6 c #333333",
"#e c #343434",
".Q c #344e34",
"#K c #353535",
".F c #363636",
"#T c #373737",
"bh c #393939",
"bp c #3a3a3a",
"bo c #3b1d3b",
"#o c #3b3b3b",
".T c #3c3c3c",
"bv c #3d1e3d",
"bf c #3d3d3d",
"bA c #3e1f3e",
"aH c #3e3e29",
"aZ c #3f3f3f",
".O c #404040",
"aF c #41412b",
"aG c #414141",
"aC c #43432c",
"a. c #434343",
"a0 c #44442d",
"#D c #444444",
"#z c #454545",
"aI c #464646",
".q c #47472f",
"aY c #484830",
"aD c #484848",
"#Y c #494949",
".X c #4a4a4a",
"aX c #4b4b32",
"aK c #4b4b4b",
"#s c #4c4c4c",
".m c #4c4c65",
"#F c #4d4d4d",
"bk c #4e4e34",
"bi c #4e4e4e",
".g c #4f4f4f",
"#1 c #505050",
"aj c #515151",
"bu c #525237",
"aO c #535355",
".I c #53536f",
".5 c #545454",
".t c #555555",
"aA c #575757",
"aM c #57575a",
".w c #585858",
"bw c #595977",
"aN c #5a5a5a",
"a7 c #5b5b5b",
"#j c #5c5c5c",
"bE c #5e5e3f",
"#b c #5e5e5e",
".# c #606080",
"#S c #616161",
"ba c #626262",
".E c #636363",
"aw c #646464",
".2 c #656565",
"#4 c #666666",
"#Q c #676767",
"aW c #686868",
"#7 c #696969",
"ad c #6a6a6a",
".j c #6c6c6c",
".N c #6d6d6d",
"an c #6e6e6e",
"#n c #6f6f6f",
"bd c #707070",
"#H c #717171",
"#y c #737373",
"aT c #747474",
"ag c #758675",
"#v c #767676",
".W c #777777",
"aP c #787878",
".z c #797979",
"bg c #7a7a7a",
"#M c #7b7b7b",
"bq c #7c7c7c",
"aq c #7d7d7d",
".C c #7e7e7e",
"#X c #7f7f7f",
".8 c #808080",
"a# c #838383",
".4 c #848484",
"#u c #858585",
"#V c #859885",
".v c #868686",
"ai c #878787",
"aQ c #898989",
"#O c #8a8a8a",
"bt c #8b8b8b",
"#a c #8c8c8c",
"bj c #8d8d8d",
"#C c #8f8f8f",
".D c #909090",
"#. c #929292",
".e c #929296",
"#A c #92a892",
"#k c #939393",
"ax c #949494",
"be c #94b1b1",
"aR c #959595",
"#m c #969696",
"#R c #989898",
".M c #999999",
".r c #99999c",
"bb c #99b8b8",
"bm c #9a9a9a",
"aB c #9b9b9b",
".Z c #9b9b9f",
"#3 c #9c9c9c",
"aE c #9d9d9d",
"ar c #9e9e9e",
".0 c #9eb69e",
".L c #9f9f9f",
".R c #9f9fa3",
"#x c #a0a0a0",
"aS c #a0a0a4",
".a c #a0c0c0",
"#8 c #a1a1a1",
"#U c #a3a3a3",
".V c #a4a4a4",
"aJ c #a5a5a5",
"a1 c #a6a6a6",
"#I c #a8a8a8",
".s c #a8c1a8",
"#g c #a9a9a9",
"am c #aaaaaa",
"aV c #ababab",
"#w c #acacac",
"#r c #adadad",
"al c #aeaeae",
"aL c #afafaf",
"#L c #b0b0b0",
".u c #b1b1b1",
".b c #b1cbb1",
"a5 c #b2b2b2",
"#W c #b3b3b3",
".S c #b4b4b4",
"bc c #b597b5",
".U c #b5b5b5",
"## c #b6b6b6",
"#J c #b7b7b7",
"ah c #b8b8b8",
".o c #b9b9b9",
"#t c #bababa",
".3 c #bbbbbb",
"a8 c #bbd6bb",
"#f c #bcbcbc",
"a3 c #bcd8bc",
".n c #bdbdbd",
"#l c #bebebe",
"a2 c #bedabe",
".J c #bfbfbf",
".k c #bfdbbf",
"Qt c #c0c0c0",
".A c #c0dcc0",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.c.c.c.c.c.d.eQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.f.g.h.c.c.c.c.c.i.j.kQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.l.c.c.c.c.c.c.c.c.c.c.c.m.nQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.o.c.c.c.c.c.c.p.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.q.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.s.c.c.c.c.c.c.t.u.v.w.x.y.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.x.z.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.B.CQtQtQtQtQt.o.D.E.F.G.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.H.IQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J.c.c.c.c.c.c.K.LQtQtQtQtQtQtQtQtQtQtQt.M.N.O.P.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.Q.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.S.c.c.c.c.c.c.T.UQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.V.W.X.f.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.Y.Z.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.0.c.c.c.c.c.1.2.JQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.3.4.5.6.1.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.7.8QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.9#.QtQtQtQtQtQtQtQt.SQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt###a#b.Y#c.c.c.c.c.c.c.c.c.c.c#d#e.c.8QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#f.c.c.c.c.c.c.6#gQtQtQtQtQtQtQtQt###h#i#j#k#fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#l#m#n#o.B.c.c.c.c.c.c#p#c#q.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#r.c.c.c.c.c.c#s#tQtQtQtQtQtQtQtQtQt#u.c.c.c.c.G.O#v#wQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J#x#y#z.p.c.c.c.c.c.c.8QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#A.c.c.c.c.c#h#vQtQtQtQtQtQtQtQtQtQtQt.g.c.c.c.c.c.c.c.c#B.w#C.3QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt###D.c.c.c#E.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.p.MQtQtQtQtQtQtQtQtQtQtQtQt#F.c.c.c.c.c.c.c.c.c.c.c#G#o#H#IQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.3.p.c.c.c.c.8QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt#J.c.c.c.c.c.c#K.uQtQtQtQtQtQtQtQtQtQtQtQtQtQt#L#M#z.P.c.c.c.c.c.c.c.c.c.c.c#N.5#O.oQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#v.c.c.c#P.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.V.c.c.c.c.c.c#QQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J#R#S#K.c.c.c.c.c.c.c.c.c.c.c#h#T.N#UQtQtQtQtQtQtQtQtQtQtQtQt#f.h.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQt#V.c.c.c.c.c.9.vQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#W#X#Y#Z.c.c.c.c.c.c.c.c.c.c.c#0#1.v#JQtQtQtQtQtQtQtQtQt#M.c.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt.n.c.c.c.c.c.c#2.VQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J#3#4#e.c.c.c.c.c.c.c.c.c.c.c#5#6#7#8QtQtQtQtQtQt#l#9.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQt.u.c.c.c.c.c.ca.#JQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Ua##Faa.c.c.c.c.c.c.c.c.c.cabQtQtQtQtQtQtQt.8.c.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQt#R.c.c.c.c.cac.NQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#8ad#6ae.c.c.c.c.c.c.EQtQtQtQtQtQtQt.Jaf.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtag.c.c.c.c.c#Z#kQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtahaiaj.h.c.c.c.MQtQtQtQtQtQtQtQt.v.c.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQt#t.c.c.c.c.c.cakalQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaman.T.JQtQtQtQtQtQtQtQt.Jao.c.c.c.c.AQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQt#g.c.c.c.c.c.c.5#fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#O.c.c.c.capQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQt.D.c.c.c.c.c#GaqQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtab.c.c.c.c.AQtQtQtQtQtQtQtQtQtQtQt",
"Qt.A.c.c.c.c.c.farQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#C.c.c.c.casQtQtQtQtQtQtQtQtQtQtQt",
"#8.c.cat.c.c.T.SQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtau.c.c.c.c.AQtQtQtQtQtQtQtQtQtQt",
"#C.c.c.cavaw.JQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtax.c.c.c.cayQtQtQtQtQtQtQtQtQtQt",
"#C.c.c.cazQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.F.c.c.c.cQtQtQtQtQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.8.p.p.paAQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaB.c.c.c.caCQtQtQtQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.T.c.c.c.c.JQtQtQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaEae.c.c.caFQtQtQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaG.c.c.c.c#lQtQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#8.1.c.c.caHQtQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaI.c.c.c.c.nQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaJac.c.c.c#1QtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaK.c.c.c.c#fQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#g.1.c.c.c#sQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.g.c.c.c.c#tQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#w#h.c.c.c#YQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.t.c.c.c.cahQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaL#G.c.c.caMQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaN.c.c.c.c##QtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.u.G.c.c.caOQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaPQtQtQtQtQtQtQtQtQt#b.c.c.B.cQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaQ.c.daRQtQtQtQtQtQtQt#W.c.c.l.caSQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.n#9.c.c.caTQtQtQtQtQtQt.C.c.y#1.c.8Qt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#y.c.c.cae#3QtQtQtQtQt.Jat.c.c.c.cQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt##aU.c.c.c#YQtQtQtQtQtQt.v.c.c.c.c.jQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#b.c.c.c#caVQtQtQtQtQtQtak.c.c.c.cQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaVac.c.c.c#bQtQtQtQtQtQt#a.c.c.c.caWQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Y.c.c.caU##QtQtQtQtQtQt.Y.c.c.c.cQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#3ae.c.c.c#yQtQtQtQtQtQtax.c.c.c.caXQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#6.c.c.c#9.nQtQtQtQtQtQt#T.c.c.c.cQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaQ.c.c.c.caQQtQtQtQtQtQtaB.c.c.c.caYQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.n#9.c.c.c#6QtQtQtQtQtQtQtaZ.c.c.c.cQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#y.c.c.cae#3QtQtQtQtQtQt#8ae.c.c.ca0QtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt##aU.c.c.c#YQtQtQtQtQtQtQtaI.c.c.c.c.JQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#b.c.c.c#5#rQtQtQtQtQtQta1ac.c.c.c.xQtQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaV#c.c.c.c#bQtQtQtQtQtQtQt#F.c.c.c.ca2QtQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt.W.c.c.caDQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Y.c.c.caU##QtQtQtQtQtQtaV#5.c.c.c.HQtQtQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQt#.aDaDaDaTQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#3ae.c.c.c#yQtQtQtQtQtQtQt.5.c.c.c.ca3QtQtQtQtQtQtQtQt",
"#C.c.c.c.YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta4.c.c.c#9.nQtQtQtQtQtQta5#c.c.c.ca6QtQtQtQtQtQtQtQtQt",
"#C.c.c.cayQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaQ.c.c.c.caQQtQtQtQtQtQtQta7.c.c.c.ca8QtQtQtQtQtQtQtQtQt",
"#C.c.c.c#GaJamQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.n#9.c.c.cauQtQtQtQtQtQtQt#Wa9.c.c.c.cQtQtQtQtQtQtQtQtQtQt",
"#8b.b#.cae#B#h#vQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#y.c.c.cae#3QtQtQtQtQtQtQtba.c.c.c.cbbQtQtQtQtQtQtQtQtQtQt",
"Qt.8.c#Naa.c.c.c#F#tQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt##aU.c.c.c#YQtQtQtQtQtQtQt#J.P.c.c.c.cQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQt.c.c.c.c.c.cakamQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#b.c.c.c#caVQtQtQtQtQtQtQtad.c.c.c.cbcQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQt.c.c.c.c.c.c.l#CQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#uaU.c.c#bQtQtQtQtQtQtQt.o#Z.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQt#e.c.c.c.c.cac#7.JQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.o.2.f##QtQtQtQtQtQtQtbd.c.c.c.cbeQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQt.W.c.c.c.c.c.cbf#JQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.nQtQtQtQtQtQtQt#laa.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQt#l.c.c.c.c.c.c#9#UQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaP.c.c.c.c#yQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.Ga#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#l.K.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQt#T.c.c.c.c.c.ca7.nQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#X.c.c.c.cbdQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtbg.c.c.c.c.c.c#e.uQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Jat.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.l#3QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.v.c.c.c.c.jQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c#h.WQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.d.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtbh.c.c.c.c.c.cbi.3QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtbj.c.c.c.cbkQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaq.c.c.c.c.c.c.damQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Iaf.c.c.c.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.cbl#CQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#fbm.NaGbn.c.c.c.c.caXQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.cacadQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#fai#b#6#h.c.c.c.c.c.cacae.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtbo.c.c.c.c.c.cbp.oQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Ibq#1br.1.c.c.c.c.c.c.c.c.c.cbs.c.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.C.c.c.c.c.c.c#9#UQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaB.NaGaU.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.7QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.ca9.4QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Ubt#b#6.B.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.caubq.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.c.c#j.nQtQtQtQtQtQtQtQtQtQt#Ibq#1br.1.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.cbuaSQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtbv.c.c.c.c.c.c#K.uQtQtQtQt#fbm.NaGbn.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.cbwQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.8.cbx.c.c.c.cbyaRbt#b#6.B.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.cbzaq.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.c.c.y.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c#TaSQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.c.c.cae.c.c.c.c.c.c.c.c.c.c.c.c.cbwaSQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtbA.cbB.c.1.c.c.c.c.c.c.cbCbq.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.8.c.cbD.c.c.c#TaS.AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.cbE.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};

static const char* const image3_data[] = { 
"104 101 183 2",
".c c #000000",
"#E c #010101",
"#e c #020202",
".h c #030303",
".o c #040404",
".7 c #050505",
".W c #060606",
"#x c #070707",
".P c #080808",
".r c #090909",
".m c #0a0a0a",
".j c #0b0b0b",
".g c #0c0c0c",
"#H c #0d0d0d",
"#J c #0e0e0e",
".d c #0f0f0f",
"#T c #101010",
"#M c #111111",
"#Q c #121212",
"a0 c #131313",
"#N c #141414",
"#K c #151515",
"aZ c #161616",
"aF c #171717",
"#c c #181818",
".b c #191919",
"#4 c #1a1a1a",
"#C c #1b1b1b",
"#Y c #1c1c1c",
"aY c #1d1d1d",
"#z c #1e1e1e",
".s c #1f1f1f",
"at c #202020",
"#3 c #212121",
".Q c #222222",
"#u c #242424",
".U c #252525",
"aX c #262626",
".n c #272727",
".X c #282828",
"aN c #292929",
"#r c #2a2a2a",
".Z c #2b2b2b",
"aM c #2c2c2c",
"aJ c #2d2d2d",
".3 c #2e2e2e",
"aG c #2f2f2f",
".a c #303030",
"aQ c #313131",
"aH c #323232",
"#f c #333333",
"#b c #343434",
"aW c #353535",
"aR c #363636",
"## c #373737",
"#h c #383838",
"aS c #393939",
"#9 c #3a3a3a",
"#l c #3b3b3b",
"a. c #3c3c3c",
"aT c #3d3d3d",
"#o c #3e3e3e",
"a# c #3f3f3f",
".5 c #404040",
"ab c #414141",
"#p c #424242",
"aU c #434343",
"ac c #444444",
".1 c #454545",
"aV c #464646",
"ae c #474747",
"#8 c #484848",
"af c #494949",
"#y c #4a4a4a",
"ag c #4b4b4b",
"ap c #4c4c4c",
".V c #4d4d4d",
"ah c #4e4e4e",
"av c #4f4f4f",
"ai c #505050",
".T c #515151",
"#F c #525252",
"aj c #535353",
".O c #545454",
"aI c #555555",
"#I c #565656",
"aa c #575757",
".S c #585858",
".p c #595959",
".N c #5a5a5a",
"ak c #5b5b5b",
"#5 c #5c5c5c",
".k c #5d5d5d",
"al c #5e5e5e",
"#O c #5f5f5f",
".i c #606060",
"aO c #616161",
"an c #626262",
".Y c #636363",
"ao c #646464",
"aP c #656565",
"#7 c #666666",
"#V c #676767",
".0 c #686868",
"aq c #696969",
"aL c #6a6a6a",
"aK c #6b6b6b",
"#X c #6c6c6c",
".4 c #6d6d6d",
"#S c #6e6e6e",
"ar c #6f6f6f",
"#0 c #707070",
"as c #717171",
"#Z c #727272",
"#. c #737373",
"#1 c #747474",
"am c #757575",
"#W c #767676",
"#d c #777777",
"#2 c #787878",
"#U c #797979",
"ay c #7b7b7b",
"#j c #7c7c7c",
"#R c #7d7d7d",
"az c #7e7e7e",
"#m c #808080",
"aA c #828282",
"aC c #838383",
"#q c #858585",
"#L c #868686",
"aB c #888888",
"#t c #898989",
"#D c #8a8a8a",
"aD c #8c8c8c",
"#w c #8d8d8d",
"#A c #8e8e8e",
"ad c #8f8f8f",
"ax c #909090",
".8 c #919191",
".e c #929292",
"#v c #939393",
"aE c #949494",
"#B c #959595",
"#s c #969696",
".9 c #979797",
"#G c #989898",
"#n c #9c9c9c",
"#6 c #9d9d9d",
"#k c #9e9e9e",
"#g c #9f9f9f",
"#a c #a1a1a1",
"#P c #a2a2a2",
"au c #a3a3a3",
".6 c #a4a4a4",
"aw c #a5a5a5",
".2 c #a7a7a7",
"#i c #a8a8a8",
".M c #a9a9a9",
".L c #aaaaaa",
".K c #ababab",
".J c #acacac",
".t c #adadad",
".I c #aeaeae",
".H c #afafaf",
".q c #b0b0b0",
".G c #b1b1b1",
".l c #b2b2b2",
".F c #b3b3b3",
".E c #b4b4b4",
".f c #b5b5b5",
".D c #b6b6b6",
".C c #b7b7b7",
".B c #b8b8b8",
".A c #b9b9b9",
".# c #bababa",
".z c #bbbbbb",
".y c #bcbcbc",
".x c #bdbdbd",
".w c #bebebe",
".v c #bfbfbf",
".u c #c0c0c0",
".R c #c1c1c1",
"Qt c #c2c2c2",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.a.b.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.d.eQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.f.g.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.h.c.iQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.f.j.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.kQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.l.m.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.n.o.c.c.c.pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.q.r.c.c.c.c.s.t.u.v.v.w.w.w.x.y.z.z.z.#.A.B.B.B.C.D.f.f.f.E.F.l.l.l.G.q.H.I.I.J.J.K.J.K.L.M.N.c.c.c.c.c.OQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.I.P.c.c.c.c.Q.q.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.S.c.c.c.c.c.TQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J.P.c.c.c.c.U.l.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.k.c.c.c.c.c.VQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.q.W.c.c.c.c.X.E.R.R.R.R.R.v.R.R.w.R.R.R.u.R.R.u.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.RQt.R.R.R.Y.c.c.c.c.c.VQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.M.W.c.c.c.c.Z.f.R.R.R.R.R.RQtQt.R.R.R.R.RQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.0.c.c.c.c.c.1QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.2.W.c.c.c.c.3.C.R.R.R.R.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.4.c.c.c.c.c.5QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.6.7.c.c.c.c.Z.B.R.R.R.R.R.R.z.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.8.9Qt.R.R.R.R.R.R.R#..c.c.c.c.c##QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#a.o.c.c.c.c#b.A.R.R.R.R.R.R.R.M.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c#cQt.R.R.R.R.R.R.R.R#d#e.c.c.c.c#fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#g.o.c.c.c.c#h.#.R.R.R.R.R.R.R.R#i.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c#c.R.R.R.R.R.R.R.R.R.R#j#e.c.c.c.c.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#k.h.c.c.c.c#l.z.R.R.R.R.R.R.R.R.R#i.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c#c.R.R.R.R.R.R.R.R.R.R.R#m.h.c.c.c.c.ZQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt#n.h.c.c.c.c#o.x.R.R.R.R.R.R.R.R.R.R.I.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a#p.R.R.R.R.R.R.R.R.R.R.R.R#q.7.c.c.c.c#r.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt#s.h.c.c.c.c#p.x.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#t.7.c.c.c.c#u.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt#v#e.c.c.c.c#o.w.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#w#x.c.c.c.c.Q.RQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQt.8#e.c.c.c.c#y.v.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#s.W.c.c.c.c#z.uQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQt#A#e.c.c.c.c.V.v.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#B.j.c.c.c.c#C.vQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt#D#E.c.c.c.c#F.u.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#G#H.c.c.c.c.b.xQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQt#D.c.c.c.c.c#I.u.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#n#J.c.c.c.c#K.RQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQt#L#E.c.c.c.c.N.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#g#M.c.c.c.c#N.zQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQt#m#E.c.c.c.c#O.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#P#N.c.c.c.c#Q.#QtQtQtQtQtQtQtQt",
"QtQtQtQtQt#R.c.c.c.c.c#S.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.t#K.c.c.c.c#T.BQtQtQtQtQtQtQt",
"QtQtQtQt#U.c.c.c.c.c#V.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#i.b.c.c.c.c#J.CQtQtQtQtQtQt",
"QtQtQt#W.c.c.c.c.c#X.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.K#Y.c.c.c.c#H.EQtQtQtQtQt",
"QtQt#Z.c.c.c.c.c#0.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.I.s.c.c.c.c.j.lQtQtQtQt",
"Qt#i#E.c.c.c#E#1.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.q.Q.c.c.c.c.pQtQtQtQt",
"Qt#0.c.c.c#E#2.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.l.U.c.c.W#3#aQtQtQt",
".M.g.h.c#J#j.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.RQtQt.R.E#4#4.c.c.AQtQtQt",
".i.c.c.c#5.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.O.a.a.a#6Qt.R.RQtQt.R.R.a.c.c#J.#QtQtQt",
".i.c.c.c.i.uQtQtQt.RQtQtQt#D.a.a.a#7.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQtQtQtQtQt#b.c.c.c.lQtQtQt",
".O.c.c.c.iQtQtQtQtQtQtQtQt#2.c.c.c#8.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQtQtQtQtQt#h.c.c#e.FQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#2.c.c.c#8.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQtQtQtQtQt#9.c.c#pQtQtQtQt",
".i.c.c.c.iQtQtQtQt.RQtQtQt#2.c.c.c#8.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQtQtQtQtQta..c.ca.QtQtQtQt",
".i.c.c.c#OQtQtQtQtQtQtQtQt#2.c.c.c#8.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQta#.c.caaQtQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#2.c.c.c#8.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQtab.c.c#ZQtQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#2.c.c.c#8.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQtac.c.c#M.qQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#2.c.c.c#8.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.cadQtQtQt.RQtQtQtae.c.c.c.uQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#2.c.c.caf.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQtaf.c.c#MQtQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#2.c.c.caf.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQtag.c.c#CQtQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#2.c.c.caf.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQt.R.RQtQtQtah.c.c#JQtQtQtQt",
".S.c.c.c#OQtQtQtQtQtQtQtQt#2.c.c.caf.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8Qt.v.R.RQtQtQtai.c.c.cQtQtQtQt",
".i.c.c.c.iQtQtQt.wQtQtQtQt#2.c.c.caf.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQt.R.RQtQtQtaj.c.c.cQtQtQtQt",
".i.c.c.c.iQtQtQt.wQtQtQtQt#d.c.c.c#y.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQt.R.RQtQtQt#I.c.c.cQtQtQtQt",
".i.c.c.c.iQtQtQt.u.RQtQtQt#d.c.c.c#y.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQt.R.RQtQtQt.p.c.c.cQtQtQtQt",
".i.c.c.c.iQtQtQt.u.RQtQtQt#W.c.c.cag.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQt.R.RQtQtQtak.c.c.cQtQtQtQt",
".i.c.c.c.iQtQtQt.R.RQtQtQt#W.c.c.c#y.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.cadQtQt.R.RQtQtQtal.c.c.cQtQtQtQt",
".i.c.c.c.iQtQtQtQt.RQtQtQtam.c.c.cag.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQt.R.RQtQtQt.i.c.c.cQtQtQtQt",
".i.c.c.calQtQtQtQt.RQtQtQtam.c.c.cag.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQtan.c.c.c.DQtQtQt",
".i.c.c.c#OQtQtQtQtQtQtQtQtam.c.c.cag.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQtao.c.c.c.uQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtam.c.c.cap.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQt#V.c.c.c.wQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtam.c.c.cap.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQtaq.c.c.c.DQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#1.c.c.c.V.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQt#X.c.c.c.EQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#1.c.c.c.VQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQtar.c.c.c.GQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#..c.c.c.VQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQtas.c.c.c.CQtQtQt",
".1.c.c.c.iQtQtQtQtQtQtQtQt#..c.c.c.V.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQt#..c.c.c.DQtQtQt",
"at.c.c.c.iQtQtQtQtQtQtQtQt#Z.c.c.cah.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQt#W.c.c.cauQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#Z.c.c.cav.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQtQtQtQtQt#U.c.c.cawQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#Z.c.c.cav.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.caxQtQtQtQtQtQtQtay.c.c.c.fQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtas.c.c.cai.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.caxQtQtQtQtQtQtQtaz.c.c.c.BQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#0.c.c.cai.R.R.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.caxQtQtQt.RQtQtQt#m.c.c.c.BQtQtQt",
".i.c.c.c.iQtQtQtQtQt.RQtQtar.c.c.c.T.R.R.R.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQt.RQtQtQtaA.c.c.c.CQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQtar.c.c.c#F.R.R.R.R.R.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8QtQtQtQtQtQtQt#q.c.c.c.FQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt.4.c.c.caj.R.R.R.R.R.R.R.R.R.R.R.R.RQtQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.a.c.c.c.8.uQtQtQtQtQtQtaB.c.c.c.qQtQtQt",
".i.c.c.c.iQtQtQtQtQtQtQtQt#X.c.c.c.O.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R#p#c#c#c#sQtQtQt.RQtQtQt#D.c.c.c.HQtQtQt",
".i.c.c.calQtQtQtQtQtQtQtQt.l#6aC.o.O.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.RQt.R.R.RQtQt#w.c.c.c.lQtQtQt",
".i.c.c.c.i.RQtQtQtQtQtQtQt.R.R.RaD.K.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.RQtQt.RaE#N.c.jQtQtQtQt",
".8.r.o#CaB#W.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.u#I#naF#cQtQtQtQt",
"Qt#C.W.c#J.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.uaj.c#e.c##QtQtQtQt",
"Qtas.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.u.O.c.c.c.caGQtQtQtQt",
"Qt.uaH.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.O.c.c.c.c.c#UQtQtQtQt",
"QtQt.u.3.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.RaI.c.c.c.c.c#0QtQtQtQtQt",
"QtQtQt.uaJ.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R#I.c.c.c.c.c#SQtQtQtQtQtQt",
"QtQtQtQt.uaJ.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.Raa.c.c.c.c.caKQtQtQtQtQtQtQt",
"QtQtQtQtQt.vaJ.c.c.c.c.caL.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.Raa.c.c.c.c.caLQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQt.vaJ.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.p.c.c.c.c.c.0QtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQt.u.X.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.N.c.c.c.c.c#.QtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQt.vaM.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.N.c.c.c.c.c.YQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt.vaM.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.Rak.c.c.c.c.c.iQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQt.v.Z.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R#5.c.c.c.c.c#OQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQt.w.Z.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.R.O.c.c.c.c.c.kQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.w#r.c.c.c.c.caK.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQt.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.R.RQtQt.R.R.R.R.R.R.R.Ral.c.c.c.c.cakQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.w#r.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R.R.C#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2.C.R.R.RQtQt.R.R.R.R.R.R.R.R#O.c.c.c.c.c.SQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt.v.n.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R.R#i.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c#i.RQtQtQt.R.R.R.R.R.R.R.R.i.c.c.c.c.calQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.w#r.c.c.c.c.caq.R.R.R.R.R.R.R.R.R.R#i.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c#iQtQt.R.R.R.R.R.R.R.R.R.i.c.c.c.c.c.OQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.waN.c.c.c.c.caq.R.R.R.R.R.R.R.R.R#i.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c#iQtQt.R.R.R.R.R.R.R.RaO.c.c.c.c.c.TQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.w.X.c.c.c.c.caq.R.R.R.R.R.R.R.R.lafaf#8#8#8#8afaf#8#8af#8afaf#8#8#8#8afafafafafafafafafafafafaf#8#8.GQtQt.R.R.R.R.R.R.Ran.c.c.c.c.cavQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.w#r.c.c.c.c.c#Z.R.R.R.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.R.R.R.0.c.c.c.c.c.VQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.waN.c.c.c.c.caq.R.R.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.R.Rao.c.c.c.c.cagQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.x.X.c.c.c.c.caq.R.R.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R.R.RaP.c.c.c.c.c#8QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.w.n.c.c.c.c.caq.R.R.R.R.u.R.R.RQtQtQtQtQtQtQtQt.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.RQtQt.R.R.R#7.c.c.c.c.c#oQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.xaM.c.c.c.c.caq.R.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R#7.c.c.c.c.cacQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.x.Z.c.c.c.c.caq.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R.R#V.c.c.c.c.c#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.y#r.c.c.c.c.caq.wQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.R#X.c.c.c.c.c.5QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.y#r.c.c.c.c.caeaQaH#baRaR#haS#9a.aT#oa#ab#paUacaVaeaf#yagapahavai#FajaIaIaaaa.p.Nak.kal#O#X.c.c.c.c#o.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.y#r.c.c.c#Q.n.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.5.c.c.c#l.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.yaN.c#E.h.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.h.c#o.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.wafaW.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.c.caX#O.RQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.LaS#u.X.U.s#3aX.s#c.c#z#C.s#3#4#4at#C#caY#YaF#c#YaZ#K#4aFa0#K#ca0a0aFa0#Ma0a0.P.PQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtauQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};

static const char* const image4_data[] = { 
"76 85 170 2",
".d c #000000",
"#l c #010101",
".m c #020202",
".y c #030303",
".R c #050505",
"#G c #060606",
"ad c #070707",
".e c #080808",
".7 c #090909",
"#R c #0b0b0b",
".w c #0c0c0c",
"#o c #0d0d0d",
".S c #0e0e0e",
".u c #0f0f0f",
".h c #111111",
".k c #121212",
"#M c #131313",
"#W c #141414",
"aI c #141429",
".K c #151515",
".H c #171717",
"#E c #181818",
".1 c #1b1b1b",
".Y c #1d1d1d",
"at c #1e1e1e",
"#i c #1f1f1f",
"#x c #202020",
"af c #202040",
"ae c #212121",
".4 c #222222",
"ay c #232323",
"ac c #242424",
".G c #252525",
"aK c #262626",
".l c #272727",
"az c #292929",
"#r c #2a2a2a",
"#C c #2c2c2c",
"aJ c #2d2d2d",
".n c #2f2f2f",
"#J c #313131",
"aF c #323232",
"#z c #333333",
"#w c #343434",
"ag c #353535",
"#e c #363636",
".V c #383838",
"aq c #393939",
".X c #3c3c3c",
"ab c #3d3d3d",
"aB c #3e3e3e",
".r c #3f3f3f",
".q c #404040",
"#a c #424242",
"an c #434343",
"av c #454545",
"aC c #474747",
"#j c #484848",
"aG c #494930",
"aH c #494949",
"#m c #4c4c4c",
"#F c #4d4d4d",
"aw c #4e4e4e",
"ak c #505050",
".z c #515151",
"al c #545454",
"#c c #555555",
"a. c #565656",
".Q c #585858",
"aL c #595959",
"ap c #5c4a4a",
"aj c #5c5c5e",
"#p c #5d5d5d",
"#H c #5f5f5f",
".5 c #606060",
".O c #616161",
"#N c #616f61",
"#O c #626262",
"#L c #636363",
".8 c #646464",
"#P c #656565",
"#Q c #666666",
"#S c #676767",
"#T c #696969",
"#B c #6a6a6a",
"#U c #6b6b6b",
"ax c #6c6c6c",
"#n c #6d6d6d",
"#g c #6e6e6e",
"#V c #707070",
".v c #717171",
"#y c #727272",
"#X c #737373",
".N c #757575",
"#Y c #767676",
"#Z c #777777",
"#u c #787878",
"#0 c #797979",
"#1 c #7a7a7a",
".T c #7c7c7c",
".L c #7d7d7d",
".C c #7e7e7e",
"#2 c #808080",
"#3 c #818181",
"#k c #828282",
"#4 c #838383",
"#5 c #858585",
".j c #868686",
"#t c #869898",
"am c #869986",
".2 c #878787",
"#6 c #888888",
"#7 c #898989",
"aE c #89898c",
"#h c #8a8a8a",
"## c #8c8c8c",
"#8 c #8d8d8d",
".3 c #8e8e8e",
"#9 c #8f8f8f",
"#d c #909090",
".F c #919191",
"aM c #929275",
"aA c #929292",
".i c #949494",
"as c #959595",
".U c #979797",
"#s c #999999",
"#K c #9b9b9b",
".D c #9c9c9c",
".E c #9d9d9d",
"ah c #9e9e9e",
"#v c #a0a0a0",
"#q c #a1a1a1",
"ao c #a3a3a3",
".p c #a4a4a4",
".W c #a5a5a5",
".o c #a6a6a6",
".B c #a7a7a7",
"au c #a7c0a7",
"aa c #a9a9a9",
"#b c #aaaaaa",
"ai c #acacac",
".0 c #adadad",
"a# c #afafaf",
".c c #b0b0b0",
".Z c #b1b1b1",
"#f c #b1b9b1",
".J c #b2b2b2",
"aD c #b2ccb2",
".A c #b3b3b3",
"ar c #b4b4b4",
".P c #b5b5b5",
".I c #b5b5b6",
".t c #b6b6b6",
"#I c #b9b9b9",
".g c #bababa",
"#A c #bbbbbb",
"#D c #bbbdbb",
".s c #bcbcbc",
".9 c #bdbdbd",
".M c #bebebe",
".x c #bfbfbf",
"aN c #c0a0c0",
"Qt c #c0c0c0",
".6 c #c0c1c1",
".# c #c0dcc0",
".b c #c1c1c1",
"#. c #c1c3c1",
".f c #c1c4c1",
".a c #c2c2c2",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#Qt.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.d.d.d.e.f.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.g.d.d.d.d.d.d.h.i.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.j.d.d.d.d.k.l.d.d.m.n.o.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.p.d.d.d.d.d.d.d.q.d.d.d.d.d.r.s.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.t.d.d.d.d.d.d.d.u.v.w.d.d.d.d.d.d.m.r.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.x.d.d.d.d.d.d.d.y.z.AQt.B.q.d.d.d.d.d.d.d.m.C.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.D.d.d.d.d.d.d.d.n.EQtQtQtQtQt.F.G.d.d.d.d.d.d.d.H.I.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J.d.d.d.d.d.d.d.K.L.xQtQtQtQtQtQtQt.M.N.h.d.d.d.d.d.d.d.r.f.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.M.d.d.d.d.d.d.d.y.O.sQtQtQtQtQtQtQt.M.b.bQt.P.Q.R.d.d.d.d.d.d.S.T.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.U.d.d.d.d.d.d.d.V.pQtQtQtQtQtQtQtQt.b.a.a.a.b.bQt.W.X.d.d.d.d.d.d.d.Y.Z.a.a.a.b.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.0.d.d.d.d.d.d.d.1.2QtQtQtQtQtQtQtQtQt.a.a.aQt.a.a.a.aQtQt.3.4.d.d.d.d.d.d.m.5.6.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt.s.d.d.d.d.d.d.d.7.8.gQtQtQtQtQtQtQtQtQtQt.a.a.a.a.a.a.a.a.b.bQt.9.v.u.d.d.d.d.d.d.h.5#..a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt##.d.d.d.d.d.d.d#a#bQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.a.a.bQtQt.A#c.y.d.d.d.d.d.d.h#d.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQt.B.d.d.d.d.d.d.d.Y.iQtQtQtQtQtQtQtQtQtQtQtQtQt.a.a.a.a.a.a.a.a.a.a.a.a.a.bQtQt.p#e.d.d.d.d.d.d.d.H#f.a.a.a.a.bQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt.s.d.d.d.d.d.d.d.w#g.sQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.b.a.a.a.a.a.a.aQt.a.a.a.b.bQtQt#h#i.d.d.d.d.d.d.m#j.b.a.a.a.bQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQt#k.d.d.d.d.d.d#l#m.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.aQtQt.s#n#o.d.d.d.d.d.d.d#p.b.a.a.a.bQtQtQtQtQtQtQt",
"QtQtQtQtQtQt#q.d.d.d.d.d.d.d#r#sQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.a.a.a.a.a.a.a.a.a.a.a.a.a.aQt.aQtQt.J.z.y.d.d.d.d.d.d.m#t.b.a.a.bQtQtQtQtQtQt",
"QtQtQtQt.P.d.d.d.d.d.d.d.h#u.xQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.a.a.a.a.a.a.aQtQtQt#v#w.d.d.d.d.d.d.d#x.s.a.a.a.bQtQtQtQt",
"QtQt.x#u.d.d.d.d.d.d.y#c.PQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.a.a.a.a.a.a.aQtQtQt#y.S.d.d.d.d.d.d.e.F.a.a.a.bQtQtQt",
"QtQt.d.d.d.d.d.d.d#z#qQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.a.a.a.a.a.a.bQtQt#A#B.w.d.d.d.d.d.d#C#D.a.aQtQtQt",
"Qt.d.d.d.d.d.d#E#kQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.a.a.b.a.a.bQtQtQt.c#F.m.d.d.d.d.d.E.a.aQtQtQt",
"Qt.d.d.d#o#G#H#IQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.a.a.a.a.a.a.a.a.a.a.a.b.a.x.bQtQtQt.E#J.d.d.w.m#K.a.aQtQtQt",
"Qt.d.d.d.j.ZQtQtQt.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.b.a.a.a.a.a.a.a.a.a.a.a.a.aQtQtQtQt#L#o#M#C.a.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.a.a.b.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.a.a.aQtQtQtQt#N.d.d.Y.x.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.a.a.b.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.aQtQtQtQtQt#O.d.d.d#J.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.bQtQtQtQt.8.d.d.d.H.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.a.a.a.a.a.bQtQtQtQt#P.d.d.d.H.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.aQtQtQtQtQt#Q.d.d.d#R.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.bQtQtQtQtQtQtQt.a.a.b.b.a.aQtQtQtQtQt#S.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.a.a.a.a.a.b.b.b.b.a.a.b.a.a.bQtQtQtQtQt#T.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.a.a.a.a.a.a.a.a.a.a.a.a.bQtQtQtQtQtQt#B.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.a.a.a.a.a.b.bQtQtQtQtQtQtQt#U.d.d.d.e.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQt#n.d.d.d.H.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQt#g.d.d.d.H.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.aQtQtQtQtQtQtQtQtQtQt#V.d.d.d.H.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQt.v.d.d.d.k.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQt#y.d.d.d#W.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.aQtQtQtQtQtQtQtQtQtQtQt#X.d.d.d.dQt.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.aQtQtQtQtQtQtQtQtQtQtQt.N.d.d.d.d#A.a.bQtQt",
"Qt.d.d.dQtQtQtQt.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.aQtQtQtQtQtQtQtQtQtQtQt#Y.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.aQtQtQtQtQtQtQtQtQtQtQt#Z.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.bQtQtQtQtQtQtQtQtQtQtQt#0.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.a.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQtQt#1.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.aQtQtQtQtQtQtQtQtQtQtQtQt.T.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQtQtQt.L.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.a.bQtQtQtQtQtQtQtQtQtQtQtQt.C.d.d.d.d#A.a.aQtQt",
"Qt.d.d.dQtQtQtQtQt.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.aQtQtQtQtQtQtQtQtQtQtQtQtQt#2.d.d.d.d.t.a.aQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQtQtQtQt#3.d.d.d.d.g.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQt#4.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQt#4.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#5.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQt.b.b.bQtQtQtQtQtQtQtQt.j.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.aQtQtQtQt.b.a.a.a.a.a.b.bQtQtQtQt#6.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.a.bQtQtQt.b.a.a.a.a.a.a.a.a.bQtQtQt#7.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.aQtQtQtQt.b.a.a.a.a.a.a.a.a.bQtQtQt#h.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.bQtQt.b.a.a.a.a.a.a.a.a.a.aQtQtQtQt##.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.bQtQt.b.a.a.a.a.a.a.a.a.a.a.bQtQtQtQt#8.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.bQtQtQt.b.a.a.a.a.a.a.a.a.a.bQtQtQtQtQt#9.d.d.d.d.a.a.aQtQt",
"Qt.d.d.d#A.9QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.a.bQtQt.b.a.a.a.a.a.a.a.a.a.a.bQtQtQtQtQtQt.T.ka..R.da#.a.aQtQt",
"Qt.d.d.d#B.k#X.9QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQt.b.a.a.a.a.a.a.a.a.a.a.a.aQtQtQtQtQtaaab.d.dacad.da#.a.aQtQt",
"Qt.d.d.d#o.d.dae#hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.b.a.a.a.a.a.a.a.a.a.a.a.a.bQtQtQtQt#A#P.e.d.d.d.d#R#J.Z.a.aQtQt",
"Qt.#af.d.d.d.d.d.dagahQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.bQtQtQtQt##.Y.d.d.d.d.d.Sai.a.a.b.bQtQt",
"QtQtQtaj.d.d.d.d.d.d.m#m.0QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.a.a.a.a.a.b.a.a.a.a.a.a.a.a.bQtQtQtQt.Pak.d.d.d.d.d.d.mal.a.a.a.bQtQtQt",
"QtQtQtQt#b.d.d.d.d.d.d.d.m#c.gQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.a.a.a.a.a.b.x.a.a.a.a.a.a.a.a.b.bQtQtQt.s#S.7.d.d.d.d.d.d.Y.E.a.a.aQtQtQtQtQt",
"QtQtQtQtQtQt#K.d.d.d.d.d.d.d.K#u.MQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.bQtQtQtQtQt#9#i.d.d.d.d.d.d.m#a.f.a.a.bQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtam.d.d.d.d.d.d.dac#9QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.a.a.a.a.a.xQtQtQtQtQtaian.d.d.d.d.d.d.d#Cao.a.a.a.bQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt.9ap.d.d.d.d.d.d.daq#qQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.b.xQtQtQtQt.s#B.7.d.d.d.d.d.d.h#u.a.a.a.a.bQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtar.d.d.d.d.d.d.d.mak.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.x.a.a.a.a.a.a.a.MQtQtQtQtQtasat.d.d.d.d.d.d.d#C.b.a.a.a.bQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtau.d.d.d.d.d.d.d#R#Q#IQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.x.MQtQtQtQt.0av.d.d.d.d.d.d.d.Raw.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.U.d.d.d.d.d.d.d#E.T.xQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.gQtQtQtQt.sax#R.d.d.d.d.d.d.day.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta..d.d.d.d.d.d.dazaAQtQtQtQtQt.b.a.a.a.a.a.a.9.M.xQtQtQtQtaAay.d.d.d.d.d.d.d.H.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.x.d.d.d.d.d.d.d.daB.pQtQtQt.b.a.a.a.a.a.xQtQtQtQtQta#aC.d.d.d.d.d.d.d.H#y.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaD.d.d.d.d.d.d.d#l#m.tQtQt.b.b.bQtQtQtQtQtQt.9#g.w.d.d.d.d.d.daz#5.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaE.d.d.d.d.d.d.d#o#B#AQtQtQtQtQtQtQtQtasac.d.d.d.d.d.daF.o.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaG.d.d.d.d.d.d.d.1#3QtQtQtQtQt.caH.d.d.d.d.d.d.h.T.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.xaI.d.d.d.d.d.d.daJ.UQt.9#V#o.d.d.d.d.d.daKa#.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#I.d.d.d.d.d.d.d.danaL.d.d.d.d.d.d.H#L.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaM.d.d.d.d.d.day.y.d.d.d.d#Ral.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtag.d.d.d.d.Q.d.d.d.e#j.P.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.d.d.d.d.d.daKao.a.a.a.b.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaN.d.d#p.F.b.a.a.b.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.U.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.b.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};

static const char* const image5_data[] = { 
"76 85 190 2",
".d c #000000",
"#q c #010101",
".m c #020202",
".y c #030303",
"aK c #040404",
".R c #050505",
"#V c #060606",
"#D c #070707",
".e c #080808",
".7 c #090909",
"al c #0b0b0b",
".w c #0c0c0c",
"#x c #0d0d0d",
".S c #0e0e0e",
".u c #0f0f0f",
".h c #111111",
".k c #121212",
"#6 c #131313",
"#l c #141414",
"a3 c #141429",
".K c #151515",
"#3 c #161616",
".H c #171717",
"#R c #181818",
"#C c #191919",
".1 c #1b1b1b",
".Y c #1d1d1d",
"aS c #1e1e1e",
"#o c #1f1f1f",
"#K c #202020",
"aH c #202040",
"aF c #212121",
".4 c #222222",
"ay c #232323",
"au c #242424",
".G c #252525",
"a4 c #262626",
".l c #272727",
"aW c #292929",
".9 c #2a2a2a",
"#P c #2c2c2c",
"ah c #2d2d2d",
"aA c #2e2e2e",
".n c #2f2f2f",
"#0 c #313131",
"a1 c #323232",
"#M c #333333",
"#J c #343434",
"aI c #353535",
"#h c #363636",
".V c #383838",
"#u c #393939",
"#9 c #3a3a3a",
"#8 c #3b3b3b",
".X c #3c3c3c",
"aE c #3d3d3d",
"#t c #3e3e3e",
".r c #3f3f3f",
".q c #404040",
"#c c #424242",
"aG c #434343",
"aw c #454545",
"aY c #474747",
"#p c #484848",
"a2 c #494930",
"aa c #494949",
"#S c #4b4b4b",
"#r c #4c4c4c",
"#U c #4d4d4d",
"aU c #4e4e4e",
"#Z c #4f4f4f",
"aM c #505050",
".z c #515151",
"az c #525252",
"aN c #545454",
"#e c #555555",
"aC c #565656",
".Q c #585858",
"a5 c #595959",
"aP c #5c4a4a",
"aJ c #5c5c5e",
"#y c #5d5d5d",
"aL c #5e5e5e",
"#W c #5f5f5f",
".5 c #606060",
".O c #616161",
"a. c #616f61",
"ae c #626262",
"#5 c #636363",
".8 c #646464",
"#E c #656565",
"ak c #666666",
"am c #676767",
"#2 c #696969",
"#O c #6a6a6a",
"#k c #6b6b6b",
"aV c #6c6c6c",
"#w c #6d6d6d",
"#j c #6e6e6e",
"an c #707070",
".v c #717171",
"#L c #727272",
"#. c #737373",
"ab c #747474",
".N c #757575",
"ai c #767676",
"ad c #777777",
"#G c #787878",
"ao c #797979",
"ap c #7a7a7a",
".T c #7c7c7c",
".L c #7d7d7d",
".C c #7e7e7e",
"aq c #808080",
"ar c #818181",
"#m c #828282",
"as c #838383",
"#4 c #858585",
".j c #868686",
"#F c #869898",
"aO c #869986",
".2 c #878787",
"#B c #888888",
"av c #898989",
"a0 c #89898c",
"#n c #8a8a8a",
"#b c #8c8c8c",
"ax c #8d8d8d",
".3 c #8e8e8e",
"aj c #8f8f8f",
"#f c #909090",
".F c #919191",
"a6 c #929275",
"aX c #929292",
"a# c #939393",
".i c #949494",
"#H c #959595",
".U c #979797",
"#Y c #989898",
"#A c #999999",
"ac c #9a9a9a",
"#1 c #9b9b9b",
".D c #9c9c9c",
".E c #9d9d9d",
"ag c #9e9e9e",
"#T c #9f9f9f",
"#I c #a0a0a0",
"#z c #a1a1a1",
"aB c #a2a2a2",
"at c #a3a3a3",
".p c #a4a4a4",
".W c #a5a5a5",
".o c #a6a6a6",
".B c #a7a7a7",
"aT c #a7c0a7",
"#v c #a8a8a8",
"#7 c #a9a9a9",
"#d c #aaaaaa",
"#s c #acacac",
".0 c #adadad",
"aR c #aeaeae",
"aD c #afafaf",
".c c #b0b0b0",
".Z c #b1b1b1",
"#i c #b1b9b1",
".J c #b2b2b2",
"aZ c #b2ccb2",
".A c #b3b3b3",
"aQ c #b4b4b4",
".P c #b5b5b5",
".I c #b5b5b6",
".t c #b6b6b6",
"af c #b7b7b7",
"#g c #b8b8b8",
"#X c #b9b9b9",
".g c #bababa",
"#N c #bbbbbb",
"#Q c #bbbdbb",
".s c #bcbcbc",
"## c #bdbdbd",
".M c #bebebe",
".x c #bfbfbf",
"a7 c #c0a0c0",
"Qt c #c0c0c0",
".6 c #c0c1c1",
".# c #c0dcc0",
".b c #c1c1c1",
"#a c #c1c3c1",
".f c #c1c4c1",
".a c #c2c2c2",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#Qt.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.d.d.d.e.f.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.g.d.d.d.d.d.d.h.i.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.j.d.d.d.d.k.l.d.d.m.n.o.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.p.d.d.d.d.d.d.d.q.d.d.d.d.d.r.s.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.t.d.d.d.d.d.d.d.u.v.w.d.d.d.d.d.d.m.r.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.x.d.d.d.d.d.d.d.y.z.AQt.B.q.d.d.d.d.d.d.d.m.C.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.D.d.d.d.d.d.d.d.n.EQtQtQtQtQt.F.G.d.d.d.d.d.d.d.H.I.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.J.d.d.d.d.d.d.d.K.L.xQtQtQtQtQtQtQt.M.N.h.d.d.d.d.d.d.d.r.f.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.M.d.d.d.d.d.d.d.y.O.sQtQtQtQtQtQtQt.M.b.bQt.P.Q.R.d.d.d.d.d.d.S.T.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.U.d.d.d.d.d.d.d.V.pQtQtQtQtQtQtQtQt.b.a.a.a.b.bQt.W.X.d.d.d.d.d.d.d.Y.Z.a.a.a.b.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.0.d.d.d.d.d.d.d.1.2QtQtQtQtQtQtQtQtQt.W.g.aQt.a.a.a.aQtQt.3.4.d.d.d.d.d.d.m.5.6.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt.s.d.d.d.d.d.d.d.7.8.gQtQtQtQtQtQtQtQtQt.M.9.w#.Qt.a.a.a.a.b.bQt##.v.u.d.d.d.d.d.d.h.5#a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt#b.d.d.d.d.d.d.d#c#dQtQtQtQtQtQtQtQtQtQtQt#..d.d.d.9.E.a.a.a.a.a.bQtQt.A#e.y.d.d.d.d.d.d.h#f.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQt.B.d.d.d.d.d.d.d.Y.iQtQtQtQtQtQtQtQtQtQtQtQt.c.w.d.d.d.d.y#e#g.a.a.a.a.a.bQtQt.p#h.d.d.d.d.d.d.d.H#i.a.a.a.a.bQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt.s.d.d.d.d.d.d.d.w#j.sQtQtQtQtQtQtQtQtQtQtQtQtQt###k.7.d.d.d.d.d#l#m.aQt.a.a.a.b.bQtQt#n#o.d.d.d.d.d.d.m#p.b.a.a.a.bQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQt#m.d.d.d.d.d.d#q#r.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b#s#t.d.d.d.d.d.d#u#v.a.a.a.a.a.aQtQt.s#w#x.d.d.d.d.d.d.d#y.b.a.a.a.bQtQtQtQtQtQtQt",
"QtQtQtQtQtQt#z.d.d.d.d.d.d.d.9#AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b#B#C.d.d.d.d.d#D#E##.a.a.a.aQt.aQtQt.J.z.y.d.d.d.d.d.d.m#F.b.a.a.bQtQtQtQtQtQt",
"QtQtQtQt.P.d.d.d.d.d.d.d.h#G.xQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt###y.m.d.d.d.d.d.K#H.a.a.a.a.a.aQtQtQt#I#J.d.d.d.d.d.d.d#K.s.a.a.a.bQtQtQtQt",
"QtQt.x#G.d.d.d.d.d.d.y#e.PQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#z.n.d.d.d.d.d.d#p.J.a.a.a.a.a.aQtQtQt#L.S.d.d.d.d.d.d.e.F.a.a.a.bQtQtQt",
"QtQt.d.d.d.d.d.d.d#M#zQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.x#G.u.d.d.d.d.d#x.NQt.a.a.a.a.a.bQtQt#N#O.w.d.d.d.d.d.d#P#Q.a.aQtQtQt",
"Qt.d.d.d.d.d.d#R#mQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Z#S.d.d.d.d.d.d#P#T.a.a.b.a.a.bQtQtQt.c#U.m.d.d.d.d.d.E.a.aQtQtQt",
"Qt.d.d.d#x#V#W#XQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Y#o.d.d.d.d.d.d#Z#N.a.a.b.a.x.bQtQtQt.E#0.d.d.w.m#1.a.aQtQtQt",
"Qt.d.d.d.j.ZQtQtQt.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt###2.7.d.d.d.d.d#3#4.a.a.a.a.a.aQtQtQtQt#5#x#6#P.a.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.a.a.b.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#7#8.d.d.d.d.d.d#9#d.a.a.a.aQtQtQtQta..d.d.Y.x.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.a.aa#aa#p#pabQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtac.H.d.d.d.d.d#Vad.a.aQtQtQtQtQtae.d.d.d#0.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaf.Q.y.d.d.d.dae.a.a.bQtQtQtQt.8.d.d.d.H.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtagah.d.d.Y.s.a.a.bQtQtQtQt#E.d.d.d.H.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.xai.uaj.a.a.aQtQtQtQtQtak.d.d.dal.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.bQtQtQtQtQtQtQt.a#g.b.b.a.aQtQtQtQtQtam.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.a.a.a.a.a.b.b.b.b.a.a.b.a.a.bQtQtQtQtQt#2.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.a.a.a.a.a.a.a.a.a.a.a.a.bQtQtQtQtQtQt#O.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.a.a.a.a.a.b.bQtQtQtQtQtQtQt#k.d.d.d.e.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQt#w.d.d.d.H.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQt#j.d.d.d.H.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.aQtQtQtQtQtQtQtQtQtQtan.d.d.d.H.a.aQtQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQt.v.d.d.d.k.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQt#L.d.d.d#l.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.aQtQtQtQtQtQtQtQtQtQtQt#..d.d.d.dQt.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.aQtQtQtQtQtQtQtQtQtQtQt.N.d.d.d.d#N.a.bQtQt",
"Qt.d.d.dQtQtQtQt.a.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.aQtQtQtQtQtQtQtQtQtQtQtai.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.a.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.aQtQtQtQtQtQtQtQtQtQtQtad.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.bQtQtQtQtQtQtQtQtQtQtQtao.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.a.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQtQtap.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.aQtQtQtQtQtQtQtQtQtQtQtQt.T.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQtQtQt.L.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.a.bQtQtQtQtQtQtQtQtQtQtQtQt.C.d.d.d.d#N.a.aQtQt",
"Qt.d.d.dQtQtQtQtQt.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtaq.d.d.d.d.t.a.aQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtar.d.d.d.d.g.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.aQtQtQtQtQtQtQtQtQtQtQtQtQtQtas.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtas.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.aQtQtQtQtafQtQtQtQtQtQtQtQtQtQt#4.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.bQtQt.s#2#xat.bQtQtQtQtQtQtQtQt.j.d.d.d.d.a.a.bQtQt",
"Qt.d.d.dQtQtQtQt.b.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.aQtQt.Uau.d.d#0.b.a.a.b.bQtQtQtQt#B.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.a.a.b.P.z#q.d.d.d.d#G.a.a.a.a.bQtQtQtav.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a#G.d.d.d#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a.aar.k.d.d.d.d.dal#4.a.a.a.a.bQtQtQt#n.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.a.a.i#p#p#pabQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.a#d#u.d.d.d.d.d.daw.Z.a.a.a.a.aQtQtQtQt#b.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQt.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.M#O.e.d.d.d.d.d.1.3.a.a.a.a.a.a.bQtQtQtQtax.d.d.d.d.a.a.aQtQt",
"Qt.d.d.dQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b#vay.d.d.d.d.d.m.O.M.a.a.a.a.a.a.bQtQtQtQtQtaj.d.d.d.d.a.a.aQtQt",
"Qt.d.d.d#N##QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Paz#q.d.d.d.d.daAaB.a.a.a.a.a.a.a.bQtQtQtQtQtQt.T.kaC.R.daD.a.aQtQt",
"Qt.d.d.d#O.k#.##QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtar#6.d.d.d.d.d#xai.b.a.a.a.a.a.a.a.aQtQtQtQtQt#7aE.d.dau#D.daD.a.aQtQt",
"Qt.d.d.d#x.d.daF#nQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#vau.d.d.d.d.d.daG.P.a.a.a.a.a.a.a.a.bQtQtQtQt#N#E.e.d.d.d.dal#0.Z.a.aQtQt",
"Qt.#aH.d.d.d.d.d.daIagQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.s#2.e.d.d.d.d.d.1.3.a.a.a.a.a.a.a.a.a.bQtQtQtQt#b.Y.d.d.d.d.d.S#s.a.a.b.bQtQt",
"QtQtQtaJ.d.d.d.d.d.d.m#r.0QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Uau.d.d.d.d.daKaL.g.a.a.a.a.a.a.a.a.bQtQtQtQt.PaM.d.d.d.d.d.d.maN.a.a.a.bQtQtQt",
"QtQtQtQt#d.d.d.d.d.d.d.d.m#e.gQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.t.z#q.d.d.d.d.daA#T.a.a.a.a.a.a.a.a.b.bQtQtQt.sam.7.d.d.d.d.d.d.Y.E.a.a.aQtQtQtQtQt",
"QtQtQtQtQtQt#1.d.d.d.d.d.d.d.K#G.MQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.t#6.d.d.d.d.wai.b.a.a.a.a.a.a.a.bQtQtQtQtQtaj#o.d.d.d.d.d.d.m#c.f.a.a.bQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtaO.d.d.d.d.d.d.dauajQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b#m.d.d.daw.Z.a.a.a.a.a.a.a.xQtQtQtQtQt#saG.d.d.d.d.d.d.d#Pat.a.a.a.bQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt##aP.d.d.d.d.d.d.d#u#zQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#u.1.3.a.a.a.a.a.a.a.b.xQtQtQtQt.s#O.7.d.d.d.d.d.d.h#G.a.a.a.a.bQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtaQ.d.d.d.d.d.d.d.maM.cQtQtQtQtQtQtQtQtQtQtQtQtQtQtaR.s.a.a.a.a.a.a.a.MQtQtQtQtQt#HaS.d.d.d.d.d.d.d#P.b.a.a.a.bQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtaT.d.d.d.d.d.d.dalak#XQtQtQtQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.x.MQtQtQtQt.0aw.d.d.d.d.d.d.d.RaU.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.U.d.d.d.d.d.d.d#R.T.xQtQtQtQtQtQtQt.b.a.a.a.a.a.a.a.a.gQtQtQtQt.saVal.d.d.d.d.d.d.day.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaC.d.d.d.d.d.d.daWaXQtQtQtQtQt.b.a.a.a.a.a.a##.M.xQtQtQtQtaXay.d.d.d.d.d.d.d.H.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.x.d.d.d.d.d.d.d.d#t.pQtQtQt.b.a.a.a.a.a.xQtQtQtQtQtaDaY.d.d.d.d.d.d.d.H#L.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaZ.d.d.d.d.d.d.d#q#r.tQtQt.b.b.bQtQtQtQtQtQt###j.w.d.d.d.d.d.daW#4.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta0.d.d.d.d.d.d.d#x#O#NQtQtQtQtQtQtQtQt#Hau.d.d.d.d.d.da1.o.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta2.d.d.d.d.d.d.d.1arQtQtQtQtQt.caa.d.d.d.d.d.d.h.T.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.xa3.d.d.d.d.d.d.dah.UQt##an#x.d.d.d.d.d.da4aD.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#X.d.d.d.d.d.d.d.daGa5.d.d.d.d.d.d.H#5.b.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta6.d.d.d.d.d.day.y.d.d.d.dalaN.b.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaI.d.d.d.d.Q.d.d.d.e#p.P.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.d.d.d.d.d.da4at.a.a.a.b.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta7.d.d#y.F.b.a.a.b.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.U.a.a.a.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.b.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};

static const char* const image6_data[] = { 
"68 69 193 2",
".f c #000000",
".G c #010101",
".u c #020202",
"ak c #030303",
"#Q c #040404",
"aW c #040408",
"#0 c #040409",
"aP c #050505",
"a0 c #060606",
"#7 c #070707",
"ab c #07070e",
".U c #080808",
"aQ c #080810",
"aA c #080811",
".p c #0a0a0a",
".k c #0b0b0b",
"#g c #0c0c0c",
"av c #0d0d0d",
"#i c #0e0e09",
"aI c #0f0f0f",
"aR c #0f0f1f",
"aV c #101010",
"#u c #102000",
".o c #111111",
"a1 c #16160f",
"#O c #171717",
"a6 c #181818",
"as c #1a1a1a",
"#j c #1b1b1b",
".3 c #1b1b24",
".q c #1b1b36",
"#G c #1c1c1c",
".7 c #1c1c26",
"#q c #1d1d1d",
".e c #1e1e1e",
".j c #202020",
"aS c #202040",
"#c c #212121",
".n c #212122",
"## c #222222",
"#p c #232323",
".t c #232324",
".8 c #242424",
".y c #252525",
"aF c #262619",
".4 c #262626",
".F c #262627",
".Y c #272727",
".L c #282829",
".X c #2a1f2a",
".S c #2a2a2a",
".R c #2a2a2b",
"aO c #2b2b2b",
".M c #2c2c2c",
"a. c #2c2c2d",
"#z c #2d2d2d",
".H c #2e2e2e",
".z c #303030",
"#S c #313131",
"aH c #323232",
"aC c #333333",
".O c #343434",
"#J c #353535",
"au c #363636",
"aj c #363649",
"ap c #373737",
"am c #383838",
"ai c #393939",
"a3 c #39393a",
"#v c #3a3a3a",
"ac c #3b3b3b",
"aa c #3c3c3c",
"#9 c #3d3d3d",
"#6 c #3e3e3e",
"#3 c #3f3f3f",
"#Z c #404040",
"#W c #414141",
".K c #424242",
"#M c #434343",
"#H c #444444",
"#E c #454545",
"#B c #464646",
"aq c #494949",
"#a c #4a3131",
"ad c #4a4a4a",
".5 c #4c4c4c",
"aD c #4d4d4d",
"aU c #515151",
"a4 c #555538",
"a2 c #555555",
"aN c #555557",
"#b c #555572",
"a8 c #565639",
"#t c #585858",
"#w c #5c5c5c",
"#A c #5d5d5d",
"#r c #5e5e5e",
"a7 c #5e6c5e",
"b. c #606040",
"#k c #606060",
"a9 c #608080",
"aY c #616161",
"#d c #626262",
"#F c #636363",
".d c #646464",
".E c #666666",
".i c #676767",
".Z c #686868",
".s c #6a6a6a",
"aM c #6b6b6b",
".m c #6c6c6c",
"#K c #6c6c6f",
".x c #6d6d6d",
".C c #6e6e6e",
".I c #6f6f6f",
".A c #717171",
".Q c #737373",
".W c #757575",
"aL c #767676",
".2 c #777777",
"#U c #778977",
"#o c #787878",
".0 c #797979",
"#D c #7a7a7a",
".v c #7b7b7b",
"#L c #7c7c7c",
"#T c #7d7d7d",
"#V c #7e7e7e",
"#Y c #7f7f7f",
"#2 c #808080",
".b c #80a080",
"#5 c #818181",
"#8 c #828282",
"a# c #838383",
"aE c #839683",
"#m c #848484",
"ae c #858585",
"ah c #868686",
"ar c #877087",
"al c #878787",
"ao c #888888",
"at c #898989",
"ax c #8a8a8a",
"ay c #8b8b8b",
"aB c #8c8c8c",
"aG c #8d8d8d",
"#C c #8e8e8e",
"aK c #8f8f8f",
"a5 c #929292",
"#4 c #959595",
"aX c #969696",
"#P c #979797",
".V c #97979a",
"aJ c #999999",
"az c #9a9a9a",
"#x c #9c9c9c",
"aw c #9cb39c",
"#X c #9d9d9d",
"#s c #9e9e9e",
".T c #9f9f9f",
"aZ c #a0a0a0",
".a c #a0a0a4",
".g c #a0c0c0",
"#l c #a2a2a2",
"#e c #a3a3a3",
".9 c #a4a4a4",
".c c #a5a5a5",
"#f c #a6a6a6",
".h c #a7a7a7",
"ag c #a7bfa7",
".# c #a8a8a8",
".r c #aaaaaa",
".w c #acacac",
".J c #adadad",
"an c #aeaeae",
".B c #afafaf",
".P c #b0b0b0",
"#N c #b1b1b1",
"aT c #b2b2b2",
".1 c #b3b3b3",
".6 c #b4b4b4",
"#1 c #b5b5b5",
".l c #b6b6b6",
"#h c #b7b7b7",
".N c #b8b8b8",
"#R c #b9b9b9",
"#. c #bababa",
"#y c #bcbcbc",
"af c #bdbdbd",
"#n c #bebebe",
"#I c #bfbfbf",
"Qt c #c0c0c0",
".D c #c0dcc0",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#Qt.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.d.e.f.f.f.f.gQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.h.i.j.f.f.f.f.f.f.k.fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.l.m.n.f.f.f.f.f.f.f.o.p.f.f.qQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.r.s.t.f.f.f.f.f.f.f.f.f.f.u.f.f.f.f.vQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.w.x.y.f.f.f.f.f.f.f.f.f.u.z.A.B.C.f.f.f.f.f.DQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.l.E.F.f.f.f.f.f.f.f.f.f.G.H.I.JQtQtQtQt.K.f.f.f.f.fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.B.A.L.f.f.f.f.f.f.f.f.f.f.M.C.NQtQtQtQtQtQtQt.l.e.f.f.f.f.OQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.P.Q.R.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQtQt.T.U.f.f.f.f.VQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQt.l.W.X.f.f.f.f.f.f.f.f.f.f.Y.Z.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.0.f.f.f.f.fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQt.1.2.3.f.f.f.f.f.f.f.f.f.f.4.i.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.5.f.f.f.f.fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQt.6.0.7.f.f.f.f.f.f.f.f.f.f.8.d.9QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#.##.f.f.f.f#aQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQt#b.f.f.f.f.f.f.f.f.f.f#c#d#eQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#f#g.f.f.f.f.PQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"#h.f.f.f#i.f.f.f.f.f.f#j#k#lQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#m.f.f.f.f.f#nQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"#o.f.f.f#p.f.f.f#q#r#sQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#t.f.f.f.f#uQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
".0.f.f.f#v#j#w#xQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#y#z.f.f.f.f#AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
".0.f.f.f#BQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.w.o.f.f.f.f.wQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
".0.f.f.f#BQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#C.u.f.f.f.f#yQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"#D.f.f.f#EQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#F.f.f.f.f#GQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
".v.f.f.f#HQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#I#J.f.f.f.f#KQtQtQtQtQtQtQtQtQtQtQtQtQt",
"#L.f.f.f#MQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#N#O.f.f.f.f.9QtQtQtQtQtQtQtQtQtQtQtQt",
"#L.f.f.f#MQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#P#Q.f.f.f.f#RQtQtQtQtQtQtQtQtQtQtQt",
"#L.f.f.f#MQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.C.f.f.f.f#SQtQtQtQtQtQtQtQtQtQtQt",
"#T.f.f.f.KQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.K.f.f.f.f#UQtQtQtQtQtQtQtQtQtQt",
"#V.f.f.f#WQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.l.e.f.f.f.f#XQtQtQtQtQtQtQtQtQt",
"#Y.f.f.f#ZQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.T.U.f.f.f#0#1QtQtQtQtQtQtQtQt",
"#2.f.f.f#ZQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#L.f.f.f.f.SQtQtQtQtQtQtQtQt",
"#2.f.f.f#3QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.5.f.f.f.f.mQtQtQtQtQtQtQt",
"#2.f.f.f#3QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#R.y.f.f.f.f#4QtQtQtQtQtQt",
"#5.f.f.f#6QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#f#g.f.f.f#7.PQtQtQtQtQt",
"#8.f.f.f#9QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#m.f.f.f.fa.#nQtQtQtQt",
"a#.f.f.faaQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#t.f.f.f.f.sQtQtQtQt",
"a#.f.f.faaQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#y#z.f.fab.fQtQtQtQt",
"#m.f.f.facQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.I.uad.f.f#2QtQtQt",
"#m.f.f.facQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.##g.f#Q#Z.fQtQtQtQt",
"ae.f.f.f#vQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaf#z.f.f.f.fagQtQtQtQt",
"ah.f.f.faiQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#F.f.f.f.fajQtQtQtQtQt",
"ah.f.f.faiQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Pak.f.f.f.f#IQtQtQtQtQt",
"al.f.f.famQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.l#j.f.f.f.fanQtQtQtQtQtQt",
"ao.f.f.fapQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaq.f.f.f.farQtQtQtQtQtQtQt",
"ao.f.f.fapQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#m.f.f.f.fasQtQtQtQtQtQtQtQt",
"at.f.f.fauQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.rav.f.f.f.f#RQtQtQtQtQtQtQtQt",
"at.f.f.fauQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#n#S.f.f.f.fawQtQtQtQtQtQtQtQtQt",
"ax.f.f.f#JQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.i.f.f.f.f#BQtQtQtQtQtQtQtQtQtQt",
"ay.f.f.f.OQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaz#Q.f.f.faA#IQtQtQtQtQtQtQtQtQtQt",
"ay.f.f.f.OQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.N.e.f.f.f.f.wQtQtQtQtQtQtQtQtQtQtQt",
"aB.f.f.faCQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaD.f.f.f.faEQtQtQtQtQtQtQtQtQtQtQtQt",
"aB.f.f.faCQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaB.f.f.f.faFQtQtQtQtQtQtQtQtQtQtQtQtQt",
"aG.f.f.faHQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.JaI.f.f.f.f#hQtQtQtQtQtQtQtQtQtQtQtQtQt",
"#C.f.f.f#SQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#I.O.f.f.f.faJQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"aK.f.f.f.zaL.6QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaM.f.f.f.faNQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"aK.f.f.faO.u.f.S.s.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#XaP.f.f.faQ#nQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
".haRaR#k#B.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#R.j.f.f.f.f.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtaS.f#Z.L.f.f.f.f.f.f.f.f#9.saTQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaU.f.f.f.f#2QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"Qt.D.a.f.f.f.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtao.f.f.f.f.zQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQt.b.f.f.f.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.1aV.f.f.faW.lQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQt.a.f.f.f.f.f.f.f.f.f.f.f.f.f#J.s.PQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Iam.f.f.f.faXQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQt.a.f.f.f.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQtQtQtQtQt.I.f.f.f.faYQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt.aam.f.f.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQtaZa0.f.f.fa1afQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.aam.f.f.f.f.f.f.f.f.f.f.f.f#z.sanQtQtQtQtQtQt#.#p.f.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.aam.f.f.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQta2.f.f.f.f.vQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.aam.f.f.f.f.f.f.f.f.f.f.f.f.S.s#L.f.f.f.fa3QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.aam.f.f.f.f.f.f.f.f.f.f.f.f.f.f.f.U.6QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Da4.f.f.f.f.f.f.f.faC#G.f.fa5QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Da4.f.f.f.f.fa6.f.fa7QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Da8.f.f.f.fa9QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Db.#ZQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};

static const char* const image7_data[] = { 
"68 69 204 2",
".f c #000000",
".G c #010101",
".u c #020202",
"ar c #030303",
"aa c #040404",
"bb c #040408",
"ap c #040409",
"#F c #050505",
"#9 c #060606",
"ay c #070707",
"aI c #07070e",
".U c #080808",
"a9 c #080810",
"aZ c #080811",
"#M c #090909",
".p c #0a0a0a",
".k c #0b0b0b",
"#k c #0c0c0c",
"aU c #0d0d0d",
"#m c #0e0e09",
"a5 c #0f0f0f",
"b. c #0f0f1f",
"aB c #101010",
"#A c #102000",
".o c #111111",
"#N c #141414",
"bc c #16160f",
"#5 c #161616",
"#7 c #171717",
"#T c #181818",
"a. c #1a1a1a",
"#n c #1b1b1b",
".3 c #1b1b24",
".q c #1b1b36",
"#W c #1c1c1c",
".7 c #1c1c26",
"#v c #1d1d1d",
".e c #1e1e1e",
".j c #202020",
"b# c #202040",
"#e c #212121",
".n c #212122",
"#b c #222222",
"#u c #232323",
".t c #232324",
".8 c #242424",
".y c #252525",
"a3 c #262619",
".4 c #262626",
".F c #262627",
".Y c #272727",
".L c #282829",
".X c #2a1f2a",
".S c #2a2a2a",
".R c #2a2a2b",
"a8 c #2b2b2b",
".M c #2c2c2c",
"aC c #2c2c2d",
"#I c #2d2d2d",
".H c #2e2e2e",
"#P c #2f2f2f",
".z c #303030",
"ad c #313131",
"#Z c #323232",
"a0 c #333333",
".O c #343434",
"#1 c #353535",
"aT c #363636",
"aM c #363649",
"aP c #373737",
"ac c #383838",
"aL c #393939",
"bd c #39393a",
"#B c #3a3a3a",
"#y c #3b3b3b",
"aE c #3c3c3c",
"aA c #3d3d3d",
"aw c #3e3e3e",
"as c #3f3f3f",
"an c #404040",
"ai c #414141",
".K c #424242",
"#4 c #434343",
"#X c #444444",
"#S c #454545",
"#K c #464646",
"aQ c #494949",
"#c c #4a3131",
"#q c #4a4a4a",
".5 c #4c4c4c",
"a1 c #4d4d4d",
"ae c #4e4e4e",
"ba c #515151",
"aG c #535353",
"be c #555538",
"#U c #555555",
"a7 c #555557",
"#d c #555572",
"bh c #565639",
"#z c #585858",
"#C c #5c5c5c",
"#J c #5d5d5d",
"#w c #5e5e5e",
"bg c #5e6c5e",
"af c #5f5f5f",
"bj c #606040",
"#o c #606060",
"bi c #608080",
"aH c #616161",
"#f c #626262",
"#V c #636363",
".d c #646464",
".E c #666666",
".i c #676767",
".Z c #686868",
".s c #6a6a6a",
"at c #6b6b6b",
".m c #6c6c6c",
"#2 c #6c6c6f",
".x c #6d6d6d",
".C c #6e6e6e",
".I c #6f6f6f",
".A c #717171",
".Q c #737373",
".W c #757575",
"ab c #767676",
".2 c #777777",
"ag c #778977",
"#t c #787878",
".0 c #797979",
"#R c #7a7a7a",
".v c #7b7b7b",
"#3 c #7c7c7c",
"#0 c #7d7d7d",
"ah c #7e7e7e",
"am c #7f7f7f",
"#O c #808080",
".b c #80a080",
"av c #818181",
"az c #828282",
"aD c #838383",
"a2 c #839683",
"#r c #848484",
"aJ c #858585",
"ak c #868686",
"aR c #877087",
"aN c #878787",
"aF c #888888",
"aS c #898989",
"aW c #8a8a8a",
"aX c #8b8b8b",
"#. c #8c8c8c",
"a4 c #8d8d8d",
"#Q c #8e8e8e",
"ax c #8f8f8f",
"aq c #909090",
"bf c #929292",
"au c #959595",
"#G c #969696",
"a# c #979797",
".V c #97979a",
"#8 c #989898",
"a6 c #999999",
"aY c #9a9a9a",
"#D c #9c9c9c",
"aV c #9cb39c",
"al c #9d9d9d",
"#x c #9e9e9e",
".T c #9f9f9f",
"#L c #a0a0a0",
".a c #a0a0a4",
".g c #a0c0c0",
"#p c #a2a2a2",
"#g c #a3a3a3",
".9 c #a4a4a4",
".c c #a5a5a5",
"#j c #a6a6a6",
".h c #a7a7a7",
"aK c #a7bfa7",
".# c #a8a8a8",
".r c #aaaaaa",
"ao c #ababab",
".w c #acacac",
".J c #adadad",
"aO c #aeaeae",
".B c #afafaf",
".P c #b0b0b0",
"#6 c #b1b1b1",
"## c #b2b2b2",
".1 c #b3b3b3",
".6 c #b4b4b4",
"#E c #b5b5b5",
".l c #b6b6b6",
"#l c #b7b7b7",
".N c #b8b8b8",
"#i c #b9b9b9",
"#a c #bababa",
"aj c #bbbbbb",
"#H c #bcbcbc",
"#Y c #bdbdbd",
"#s c #bebebe",
"#h c #bfbfbf",
"Qt c #c0c0c0",
".D c #c0dcc0",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#Qt.a.bQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c.d.e.f.f.f.f.gQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.h.i.j.f.f.f.f.f.f.k.fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.l.m.n.f.f.f.f.f.f.f.o.p.f.f.qQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.r.s.t.f.f.f.f.f.f.f.f.f.f.u.f.f.f.f.vQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.w.x.y.f.f.f.f.f.f.f.f.f.u.z.A.B.C.f.f.f.f.f.DQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.l.E.F.f.f.f.f.f.f.f.f.f.G.H.I.JQtQtQtQt.K.f.f.f.f.fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.B.A.L.f.f.f.f.f.f.f.f.f.f.M.C.NQtQtQtQtQtQtQt.l.e.f.f.f.f.OQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.P.Q.R.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQtQt.T.U.f.f.f.f.VQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQt.l.W.X.f.f.f.f.f.f.f.f.f.f.Y.Z.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.0.f.f.f.f.fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQt.1.2.3.f.f.f.f.f.f.f.f.f.f.4.i.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.5.f.f.f.f.fQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQt.6.0.7.f.f.f.f.f.f.f.f.f.f.8.d.9QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#.##QtQtQtQt#a#b.f.f.f.f#cQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQt#d.f.f.f.f.f.f.f.f.f.f#e#f#gQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#h.d.u.Y#iQtQtQtQt#j#k.f.f.f.f.PQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"#l.f.f.f#m.f.f.f.f.f.f#n#o#pQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#i.O.f.f.f#qQtQtQtQtQt#r.f.f.f.f.f#sQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"#t.f.f.f#u.f.f.f#v#w#xQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#h#y.f.f.f.f.QQtQtQtQtQt#z.f.f.f.f#AQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
".0.f.f.f#B#n#C#DQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#E#v.f.f.f#F#GQtQtQtQt#H#I.f.f.f.f#JQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
".0.f.f.f#KQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#L#M.f.f.f#N.lQtQtQtQt.w.o.f.f.f.f.wQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
".0.f.f.f#KQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#O.f.f.f.f#P#HQtQtQtQt#Q.u.f.f.f.f#HQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"#R.f.f.f#SQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#z.f.f.f.f#UQtQtQtQtQt#V.f.f.f.f#WQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
".v.f.f.f#XQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Y#Z.f.f.f.f#0QtQtQtQt#h#1.f.f.f.f#2QtQtQtQtQtQtQtQtQtQtQtQtQt",
"#3.f.f.f#4QtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.P#5.f.f.f.U#xQtQtQtQt#6#7.f.f.f.f.9QtQtQtQtQtQtQtQtQtQtQtQt",
"#3.f.f.f#4QtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#8#9.f.f.fa.#iQtQtQtQta#aa.f.f.f.f#iQtQtQtQtQtQtQtQtQtQtQt",
"#3.f.f.f#4QtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtab.f.f.f.fac#sQtQtQtQt.C.f.f.f.fadQtQtQtQtQtQtQtQtQtQtQt",
"#0.f.f.f.KQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtae.f.f.f.fafQtQtQtQtQt.K.f.f.f.fagQtQtQtQtQtQtQtQtQtQt",
"ah.f.f.faiQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaj.S.f.f.f.GakQtQtQtQt.l.e.f.f.f.falQtQtQtQtQtQtQtQtQt",
"am.f.f.fanQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtao.o.f.f.f#k.9QtQtQtQt.T.U.f.f.fap#EQtQtQtQtQtQtQtQt",
"#O.f.f.fanQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaqar.f.f.f.jajQtQtQtQt#3.f.f.f.f.SQtQtQtQtQtQtQtQt",
"#O.f.f.fasQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtat.f.f.f.f.KQtQtQtQtQt.5.f.f.f.f.mQtQtQtQtQtQtQt",
"#O.f.f.fasQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtan.f.f.f.f.sQtQtQtQt#i.y.f.f.f.fauQtQtQtQtQtQt",
"av.f.f.fawQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#l#b.f.f.faraxQtQtQtQt#j#k.f.f.fay.PQtQtQtQtQt",
"az.f.f.faAQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.c#k.f.f.faB.rQtQtQtQt#r.f.f.f.faC#sQtQtQtQt",
"aD.f.f.faEQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaF.G.f.f.faGQtQtQtQtQt#z.f.f.f.f.sQtQtQtQt",
"aD.f.f.faEQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaH.f.f#U#HQtQtQtQtQt#H#I.f.faI.fQtQtQtQt",
"#r.f.f.f#yQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#saiahQtQtQtQtQtQtQtQt.I.u#q.f.f#OQtQtQt",
"#r.f.f.f#yQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.##k.faaan.fQtQtQtQt",
"aJ.f.f.f#BQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#Y#I.f.f.f.faKQtQtQtQt",
"ak.f.f.faLQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#V.f.f.f.faMQtQtQtQtQt",
"ak.f.f.faLQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta#ar.f.f.f.f#hQtQtQtQtQt",
"aN.f.f.facQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.l#n.f.f.f.faOQtQtQtQtQtQt",
"aF.f.f.faPQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaQ.f.f.f.faRQtQtQtQtQtQtQt",
"aF.f.f.faPQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#r.f.f.f.fa.QtQtQtQtQtQtQtQt",
"aS.f.f.faTQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.raU.f.f.f.f#iQtQtQtQtQtQtQtQt",
"aS.f.f.faTQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#sad.f.f.f.faVQtQtQtQtQtQtQtQtQt",
"aW.f.f.f#1QtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.i.f.f.f.f#KQtQtQtQtQtQtQtQtQtQt",
"aX.f.f.f.OQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaYaa.f.f.faZ#hQtQtQtQtQtQtQtQtQtQt",
"aX.f.f.f.OQtQtQtQtQt#T.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.N.e.f.f.f.f.wQtQtQtQtQtQtQtQtQtQtQt",
"#..f.f.fa0QtQtQtQtQt#I#T#T#T.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQta1.f.f.f.fa2QtQtQtQtQtQtQtQtQtQtQtQt",
"#..f.f.fa0QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#..f.f.f.fa3QtQtQtQtQtQtQtQtQtQtQtQtQt",
"a4.f.f.f#ZQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Ja5.f.f.f.f#lQtQtQtQtQtQtQtQtQtQtQtQtQt",
"#Q.f.f.fadQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#h.O.f.f.f.fa6QtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"ax.f.f.f.zab.6QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtat.f.f.f.fa7QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"ax.f.f.fa8.u.f.S.s.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtal#F.f.f.fa9#sQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
".hb.b.#o#K.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#i.j.f.f.f.f.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"Qtb#.fan.L.f.f.f.f.f.f.f.faA.s##QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtba.f.f.f.f#OQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"Qt.D.a.f.f.f.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtaF.f.f.f.f.zQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQt.b.f.f.f.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.1aB.f.f.fbb.lQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQt.a.f.f.f.f.f.f.f.f.f.f.f.f.f#1.s.PQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt#hac.f.f.f.f#GQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQt.a.f.f.f.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQtQtQtQtQt.I.f.f.f.faHQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt.aac.f.f.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQtQtQtQtQtQtQtQt#L#9.f.f.fbc#YQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.aac.f.f.f.f.f.f.f.f.f.f.f.f#I.saOQtQtQtQtQtQt#a#u.f.f.f.f.hQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.aac.f.f.f.f.f.f.f.f.f.f.f.f.S.s.rQtQtQt#U.f.f.f.f.vQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.aac.f.f.f.f.f.f.f.f.f.f.f.f.S.s#3.f.f.f.fbdQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.aac.f.f.f.f.f.f.f.f.f.f.f.f.f.f.f.U.6QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Dbe.f.f.f.f.f.f.f.fa0#W.f.fbfQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Dbe.f.f.f.f.f#T.f.fbgQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.Dbh.f.f.f.fbiQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.DbjanQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};

static const unsigned char image8_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x04,
    0x95, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0xa5, 0xd5, 0x5b, 0x6c, 0x14,
    0x55, 0x18, 0xc0, 0xf1, 0xff, 0x9c, 0x33, 0x3b, 0xb3, 0x6d, 0xb7, 0xdd,
    0x6e, 0x5b, 0x7a, 0x6f, 0x41, 0xa0, 0x54, 0xbc, 0x54, 0xa1, 0x8a, 0x66,
    0x42, 0x6a, 0x31, 0xd5, 0xac, 0xd5, 0x10, 0x94, 0x34, 0x6a, 0x7d, 0xb0,
    0x44, 0x88, 0x12, 0x8d, 0x98, 0x08, 0xe1, 0x01, 0x35, 0x31, 0x2a, 0xe2,
    0x83, 0x4f, 0x1a, 0xf4, 0x49, 0x7d, 0xf1, 0x41, 0x0c, 0x4d, 0x95, 0x60,
    0x6a, 0x6d, 0xac, 0x10, 0xb3, 0x6a, 0x21, 0x12, 0x40, 0x2e, 0xa5, 0x57,
    0xba, 0xa5, 0x6b, 0x2f, 0x6c, 0xf7, 0xd2, 0xee, 0xad, 0x3b, 0x33, 0x3e,
    0x14, 0xbb, 0xa9, 0x05, 0x5e, 0x3c, 0xc9, 0x24, 0x27, 0x33, 0x73, 0x7e,
    0xf3, 0xcd, 0x37, 0xdf, 0x7c, 0x47, 0xf1, 0xf9, 0x7c, 0xdc, 0x6e, 0x18,
    0x86, 0x61, 0xff, 0xf7, 0x9c, 0xcf, 0xe7, 0x53, 0x6e, 0xbb, 0x08, 0x50,
    0x6e, 0x06, 0x1b, 0x86, 0x61, 0xab, 0x3a, 0x48, 0x1d, 0xf4, 0x1c, 0xd0,
    0x72, 0xc0, 0x91, 0xbd, 0x70, 0xcd, 0x4c, 0x42, 0x2a, 0x06, 0xa9, 0x30,
    0xc4, 0x22, 0xb7, 0x7e, 0x88, 0xba, 0x0c, 0x6d, 0x30, 0x6c, 0x3d, 0x0f,
    0xd6, 0xd7, 0x97, 0xd2, 0xe4, 0x6d, 0x64, 0x43, 0xdd, 0x46, 0x4a, 0x8b,
    0xab, 0x10, 0x0a, 0x0c, 0x8c, 0xf7, 0xd2, 0x37, 0x7c, 0x86, 0x01, 0x7f,
    0x3f, 0x81, 0x91, 0x19, 0xc6, 0x2f, 0xa5, 0x68, 0x7a, 0xdc, 0xb0, 0xbb,
    0xbb, 0x96, 0xe3, 0x4b, 0xe0, 0x86, 0x06, 0xc3, 0x76, 0x15, 0x40, 0xdb,
    0x2b, 0xdb, 0x78, 0x7e, 0xfb, 0x4e, 0xaa, 0x4a, 0xd7, 0x11, 0x8c, 0x06,
    0xf0, 0x5f, 0xbb, 0xc2, 0xc5, 0x2b, 0x67, 0x89, 0x31, 0x85, 0xea, 0x94,
    0x54, 0x54, 0x16, 0xe0, 0x2a, 0x30, 0x29, 0x59, 0x3b, 0x8b, 0xff, 0xdc,
    0x3c, 0xcd, 0xcf, 0x34, 0xd8, 0x3f, 0xb4, 0x9f, 0x54, 0x6e, 0x0a, 0x1b,
    0x37, 0xd0, 0x37, 0xdf, 0xde, 0xc5, 0xeb, 0x2f, 0xbe, 0x4f, 0x3c, 0x11,
    0x66, 0x70, 0xe4, 0x12, 0x9d, 0x5d, 0x9d, 0xf4, 0xf7, 0x0d, 0x50, 0x5e,
    0x5e, 0xc2, 0xf0, 0xb5, 0x21, 0x66, 0xe2, 0x63, 0xb8, 0xcb, 0x4c, 0xdc,
    0xe5, 0x16, 0x2e, 0xb7, 0xe0, 0xce, 0xcd, 0x92, 0xbc, 0x42, 0x89, 0x77,
    0xeb, 0x16, 0xbb, 0xf3, 0xfb, 0x1e, 0x65, 0x09, 0x6c, 0x18, 0x0b, 0xaf,
    0xbf, 0x63, 0xf7, 0x36, 0xde, 0x68, 0xfb, 0x80, 0x78, 0x32, 0xc2, 0xb5,
    0xc9, 0x61, 0x7e, 0xec, 0xea, 0xe4, 0xee, 0x75, 0xf5, 0x1c, 0x3c, 0x70,
    0x78, 0x31, 0x92, 0x93, 0xbf, 0x1f, 0x67, 0xef, 0x7b, 0x6d, 0xa0, 0xa6,
    0xc8, 0x2f, 0x15, 0x68, 0xba, 0x46, 0xcd, 0x26, 0x48, 0x47, 0x04, 0x4d,
    0x4d, 0x4d, 0x76, 0x77, 0x77, 0xb7, 0x02, 0x20, 0x00, 0x54, 0x7d, 0x21,
    0xa7, 0xad, 0x2d, 0x2f, 0x93, 0x48, 0xcd, 0x12, 0x8c, 0x04, 0xf8, 0xa5,
    0xa7, 0x9b, 0xea, 0xb2, 0x1a, 0x5e, 0x68, 0x79, 0x89, 0x70, 0x34, 0xc8,
    0x47, 0x9f, 0xee, 0xe3, 0xec, 0x45, 0x1f, 0x0d, 0x0f, 0x3f, 0xc9, 0xab,
    0x6d, 0xfb, 0x09, 0x8e, 0xa5, 0x31, 0x53, 0x16, 0x02, 0x15, 0x29, 0x54,
    0x36, 0x3d, 0xe1, 0xa1, 0xa8, 0x32, 0x93, 0x59, 0x01, 0x0b, 0x5f, 0xff,
    0x31, 0xef, 0x23, 0xac, 0xae, 0xa8, 0x25, 0x34, 0x17, 0x60, 0x2a, 0x32,
    0x4a, 0x60, 0x7a, 0x14, 0x3d, 0xdb, 0x41, 0x38, 0x1a, 0x64, 0xcf, 0x5b,
    0xcf, 0x71, 0xf4, 0xa7, 0xcf, 0x39, 0x74, 0x78, 0x2f, 0x00, 0x2b, 0xab,
    0xd6, 0x90, 0x88, 0x9b, 0x98, 0x26, 0x60, 0x2d, 0x30, 0xd9, 0xf9, 0x92,
    0xf5, 0xf5, 0x85, 0x78, 0xbd, 0x5e, 0x1b, 0x40, 0x18, 0x86, 0x61, 0xeb,
    0x39, 0xb0, 0xb1, 0xee, 0x01, 0x82, 0x73, 0x13, 0x4c, 0x47, 0xfd, 0x4c,
    0x86, 0x87, 0x28, 0xa8, 0xb6, 0xe9, 0x38, 0xf1, 0x19, 0x8d, 0xdb, 0x6b,
    0xb8, 0xec, 0xff, 0x8d, 0x58, 0x3c, 0xc1, 0xae, 0xd6, 0x7d, 0x00, 0x5c,
    0xf5, 0xf7, 0x23, 0x1d, 0x26, 0xb6, 0x75, 0xc3, 0x45, 0x92, 0x30, 0x53,
    0xdc, 0xb5, 0xa1, 0x18, 0xcb, 0xb2, 0x32, 0x11, 0x6b, 0x39, 0x50, 0x5e,
    0x56, 0x4d, 0x30, 0x3c, 0xca, 0x44, 0x70, 0x80, 0x89, 0xd0, 0x30, 0x71,
    0x26, 0x29, 0x5a, 0x9d, 0x66, 0x65, 0x3d, 0xcc, 0x5b, 0x09, 0x5a, 0x9a,
    0xdb, 0x78, 0xd4, 0x78, 0x9a, 0x50, 0x78, 0x8a, 0x2f, 0x8f, 0x7c, 0x4c,
    0x4e, 0x21, 0xa4, 0xb1, 0xb0, 0x00, 0x5b, 0x11, 0x24, 0x52, 0x16, 0x77,
    0xd4, 0xe6, 0x23, 0x84, 0xc8, 0xc0, 0x7a, 0x36, 0xa0, 0x58, 0xfc, 0x1d,
    0x1a, 0x24, 0x10, 0x1a, 0x66, 0x3a, 0x3a, 0x4a, 0x34, 0x1e, 0x20, 0x6e,
    0x06, 0x99, 0x9d, 0x99, 0xa3, 0x38, 0x77, 0x15, 0x7b, 0x76, 0x1c, 0x04,
    0x60, 0xdf, 0x87, 0xcf, 0x32, 0x93, 0x9c, 0x44, 0x73, 0x81, 0x22, 0x00,
    0x21, 0x40, 0x4a, 0xb0, 0x25, 0x25, 0x95, 0x9e, 0xa5, 0xe5, 0x66, 0x01,
    0xfd, 0xe3, 0xbd, 0x24, 0xcc, 0x08, 0xd3, 0x91, 0x51, 0x22, 0xf1, 0x00,
    0x71, 0x33, 0x42, 0x9a, 0x04, 0xd7, 0x03, 0x26, 0xef, 0xec, 0xde, 0x4f,
    0xbe, 0x7b, 0x05, 0x5f, 0x7d, 0x7b, 0x88, 0x3f, 0x2e, 0xf4, 0x50, 0x58,
    0x05, 0x0e, 0x1d, 0x70, 0x08, 0x6c, 0x29, 0x40, 0x48, 0x34, 0xa7, 0x46,
    0x3c, 0x22, 0x51, 0x55, 0x35, 0x03, 0x9b, 0x49, 0xe8, 0x1b, 0xfa, 0x93,
    0xec, 0x7c, 0x8d, 0x70, 0x7c, 0x9c, 0x58, 0x32, 0x42, 0x2a, 0x1d, 0xc7,
    0x66, 0x1e, 0xac, 0x34, 0x9e, 0xbc, 0x42, 0x00, 0x3a, 0x4f, 0x7c, 0x83,
    0xcb, 0x03, 0xaa, 0x53, 0x45, 0xd1, 0x25, 0x9a, 0x43, 0x45, 0x73, 0x38,
    0x10, 0x52, 0xe0, 0xce, 0xcd, 0x62, 0x7c, 0x30, 0x9a, 0x49, 0x85, 0xcf,
    0xe7, 0x53, 0x52, 0x31, 0x18, 0x1a, 0x1d, 0x20, 0x34, 0x37, 0x4e, 0x2c,
    0x11, 0xc5, 0xb4, 0x93, 0x28, 0xc2, 0x42, 0x95, 0x92, 0xfc, 0x32, 0x95,
    0xe3, 0x3d, 0x5f, 0xf3, 0xee, 0x27, 0x3b, 0x09, 0x4c, 0x8c, 0xa3, 0xe7,
    0xa8, 0x68, 0x9a, 0xc4, 0xa1, 0xe9, 0xa8, 0x4e, 0x0d, 0xa1, 0x69, 0x48,
    0x55, 0x63, 0x45, 0x9e, 0x87, 0x81, 0xf3, 0xa1, 0x45, 0x58, 0x85, 0x85,
    0x86, 0x32, 0x3e, 0x32, 0x4d, 0x6e, 0xc9, 0x3c, 0xd2, 0x01, 0x90, 0xc6,
    0xa1, 0x0a, 0xb0, 0x04, 0xa5, 0x6b, 0x34, 0x4e, 0xf7, 0x7f, 0x47, 0x32,
    0x09, 0x4a, 0x16, 0xe4, 0xe6, 0x49, 0xa4, 0xee, 0x40, 0xd3, 0x9c, 0xe8,
    0xba, 0x13, 0x29, 0x55, 0x0a, 0xdc, 0x3a, 0x6e, 0x51, 0xc9, 0xf9, 0xd3,
    0xbd, 0x4b, 0xe1, 0x58, 0x04, 0xc6, 0x2e, 0x9a, 0x94, 0xd4, 0xce, 0xe2,
    0x2e, 0x54, 0x71, 0x48, 0x15, 0xa1, 0x08, 0xd0, 0x34, 0x26, 0x47, 0x52,
    0x3c, 0xb4, 0xb6, 0x85, 0x5c, 0x57, 0x3e, 0xe1, 0xd9, 0x10, 0xbd, 0x83,
    0xc7, 0x70, 0xad, 0xca, 0x46, 0xcf, 0x72, 0x22, 0x55, 0x8d, 0xac, 0x2c,
    0x95, 0xd5, 0x25, 0x15, 0x9c, 0x3a, 0x16, 0xc4, 0x3f, 0x18, 0xa6, 0xbd,
    0xbd, 0x3d, 0xf3, 0xe7, 0xf9, 0x7c, 0x3e, 0xe5, 0xfa, 0xd5, 0x34, 0xa3,
    0x67, 0x4c, 0xac, 0x94, 0x85, 0x22, 0x2d, 0xa4, 0x26, 0x90, 0x42, 0x25,
    0x3a, 0x01, 0xcd, 0x8d, 0xad, 0x1c, 0x78, 0xed, 0x30, 0x4f, 0x35, 0xb6,
    0x32, 0x77, 0x5d, 0x45, 0xd3, 0x9c, 0x38, 0xa4, 0x13, 0xa7, 0xa6, 0x52,
    0x5b, 0x59, 0xce, 0xf4, 0x79, 0x0f, 0x5d, 0xed, 0x17, 0x50, 0x94, 0x4c,
    0x1f, 0x12, 0xff, 0x4e, 0xba, 0x3b, 0x7d, 0xca, 0xd0, 0x29, 0x13, 0xff,
    0x05, 0x0b, 0x21, 0x61, 0xb1, 0xbb, 0x2b, 0x02, 0x50, 0x16, 0x6f, 0x57,
    0xa4, 0x8a, 0xaa, 0x3a, 0x70, 0xe7, 0x3a, 0xb8, 0x77, 0xe5, 0x2a, 0x22,
    0x97, 0x8b, 0x39, 0xf2, 0xc5, 0x29, 0x42, 0xc1, 0x24, 0x47, 0x8f, 0x1e,
    0x5d, 0x94, 0x97, 0x35, 0x7a, 0xef, 0xd6, 0x2d, 0x76, 0xdd, 0xe6, 0x1c,
    0x1e, 0x6c, 0xf6, 0xa0, 0xe5, 0x28, 0x8c, 0x5c, 0x9e, 0xc5, 0x7f, 0x25,
    0x41, 0x78, 0xda, 0xc2, 0x53, 0xac, 0x51, 0x5d, 0x93, 0xcb, 0x3d, 0xf7,
    0x97, 0xe3, 0xd1, 0x2a, 0xf8, 0xeb, 0xd7, 0x30, 0x3f, 0x1f, 0xeb, 0x5b,
    0x86, 0xde, 0x14, 0x06, 0x68, 0x6a, 0x6a, 0xb2, 0x8b, 0x2a, 0x55, 0x6a,
    0xef, 0x2b, 0x64, 0x5d, 0x9d, 0x87, 0xb2, 0x6a, 0x37, 0x9e, 0x22, 0x17,
    0xb1, 0x88, 0x60, 0x6a, 0x34, 0x8e, 0x7f, 0x20, 0x4a, 0xdf, 0xb9, 0x29,
    0xc6, 0x86, 0x23, 0x48, 0x29, 0x97, 0xa1, 0xb7, 0x84, 0x17, 0xa3, 0xf7,
    0x7a, 0x6d, 0xcb, 0xb2, 0x32, 0xb5, 0x29, 0xc4, 0x92, 0xa3, 0xa3, 0xa3,
    0xe3, 0x96, 0x7b, 0xdf, 0x6d, 0xe1, 0xff, 0x33, 0xfe, 0x01, 0xbe, 0x1e,
    0xd7, 0xb6, 0xbb, 0x8c, 0xca, 0x08, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
    0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};


/*
 *  Constructs a builderDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
builderDialog::builderDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl ),
      image0( (const char **) image0_data ),
      image1( (const char **) image1_data ),
      image2( (const char **) image2_data ),
      image3( (const char **) image3_data ),
      image4( (const char **) image4_data ),
      image5( (const char **) image5_data ),
      image6( (const char **) image6_data ),
      image7( (const char **) image7_data )
{
    QImage img;
    img.loadFromData( image8_data, sizeof( image8_data ), "PNG" );
    image8 = img;
    if ( !name )
	setName( "builderDialog" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setSizeGripEnabled( TRUE );
    setModal( FALSE );
    builderDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "builderDialogLayout"); 

    layout73 = new QVBoxLayout( 0, 0, 6, "layout73"); 

    layout72 = new QVBoxLayout( 0, 0, 6, "layout72"); 

    frame4 = new QFrame( this, "frame4" );
    frame4->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, frame4->sizePolicy().hasHeightForWidth() ) );
    frame4->setMinimumSize( QSize( 0, 0 ) );
    frame4->setMaximumSize( QSize( 32767, 100 ) );
    frame4->setFrameShape( QFrame::StyledPanel );
    frame4->setFrameShadow( QFrame::Raised );
    frame4Layout = new QGridLayout( frame4, 1, 1, 11, 6, "frame4Layout"); 

    modeGroup = new QButtonGroup( frame4, "modeGroup" );
    modeGroup->setMinimumSize( QSize( 0, 0 ) );
    modeGroup->setFrameShadow( QButtonGroup::Raised );
    modeGroup->setExclusive( TRUE );
    modeGroup->setColumnLayout(0, Qt::Vertical );
    modeGroup->layout()->setSpacing( 6 );
    modeGroup->layout()->setMargin( 11 );
    modeGroupLayout = new QGridLayout( modeGroup->layout() );
    modeGroupLayout->setAlignment( Qt::AlignTop );

    layout16 = new QHBoxLayout( 0, 0, 6, "layout16"); 

    draw = new QCheckBox( modeGroup, "draw" );
    draw->setChecked( TRUE );
    layout16->addWidget( draw );

    retype = new QCheckBox( modeGroup, "retype" );
    layout16->addWidget( retype );

    Delete = new QCheckBox( modeGroup, "Delete" );
    layout16->addWidget( Delete );

    modeGroupLayout->addLayout( layout16, 0, 0 );

    frame4Layout->addWidget( modeGroup, 0, 0 );
    layout72->addWidget( frame4 );

    layout71 = new QVBoxLayout( 0, 0, 6, "layout71"); 

    layout70 = new QHBoxLayout( 0, 0, 6, "layout70"); 

    frame3 = new QFrame( this, "frame3" );
    frame3->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, frame3->sizePolicy().hasHeightForWidth() ) );
    frame3->setFrameShape( QFrame::StyledPanel );
    frame3->setFrameShadow( QFrame::Raised );
    frame3Layout = new QGridLayout( frame3, 1, 1, 11, 6, "frame3Layout"); 

    atomGroup = new QButtonGroup( frame3, "atomGroup" );
    atomGroup->setFrameShadow( QButtonGroup::Raised );
    atomGroup->setLineWidth( 1 );
    atomGroup->setExclusive( TRUE );
    atomGroup->setColumnLayout(0, Qt::Vertical );
    atomGroup->layout()->setSpacing( 6 );
    atomGroup->layout()->setMargin( 11 );
    atomGroupLayout = new QGridLayout( atomGroup->layout() );
    atomGroupLayout->setAlignment( Qt::AlignTop );

    layout36 = new QGridLayout( 0, 1, 1, 0, 6, "layout36"); 

    textLabel2 = new QLabel( atomGroup, "textLabel2" );

    layout36->addWidget( textLabel2, 0, 0 );

    otherAtom = new QComboBox( FALSE, atomGroup, "otherAtom" );
    otherAtom->setMaximumSize( QSize( 120, 32767 ) );
    otherAtom->setSizeLimit( 10 );

    layout36->addWidget( otherAtom, 1, 0 );

    atomGroupLayout->addMultiCellLayout( layout36, 2, 3, 0, 2 );

    bromine = new QPushButton( atomGroup, "bromine" );
    bromine->setMaximumSize( QSize( 30, 30 ) );
    bromine->setToggleButton( TRUE );
    atomGroup->insert( bromine, 5 );

    atomGroupLayout->addWidget( bromine, 1, 2 );

    hydrogen = new QPushButton( atomGroup, "hydrogen" );
    hydrogen->setMaximumSize( QSize( 30, 30 ) );
    hydrogen->setToggleButton( TRUE );
    atomGroup->insert( hydrogen, 9 );

    atomGroupLayout->addWidget( hydrogen, 0, 3 );

    flourine = new QPushButton( atomGroup, "flourine" );
    flourine->setMaximumSize( QSize( 30, 30 ) );
    flourine->setToggleButton( TRUE );
    atomGroup->insert( flourine, 8 );

    atomGroupLayout->addWidget( flourine, 1, 0 );

    carbon = new QPushButton( atomGroup, "carbon" );
    carbon->setMaximumSize( QSize( 30, 30 ) );
    carbon->setToggleButton( TRUE );
    carbon->setOn( TRUE );
    atomGroup->insert( carbon, 0 );

    atomGroupLayout->addWidget( carbon, 0, 0 );

    oxygen = new QPushButton( atomGroup, "oxygen" );
    oxygen->setMaximumSize( QSize( 30, 30 ) );
    oxygen->setToggleButton( TRUE );
    atomGroup->insert( oxygen, 2 );

    atomGroupLayout->addWidget( oxygen, 0, 2 );

    chlorine = new QPushButton( atomGroup, "chlorine" );
    chlorine->setMaximumSize( QSize( 30, 30 ) );
    chlorine->setToggleButton( TRUE );
    atomGroup->insert( chlorine, 6 );

    atomGroupLayout->addWidget( chlorine, 1, 1 );

    nitrogen = new QPushButton( atomGroup, "nitrogen" );
    nitrogen->setMaximumSize( QSize( 30, 30 ) );
    nitrogen->setToggleButton( TRUE );
    atomGroup->insert( nitrogen, 1 );

    atomGroupLayout->addWidget( nitrogen, 0, 1 );

    iodine = new QPushButton( atomGroup, "iodine" );
    iodine->setMaximumSize( QSize( 30, 30 ) );
    iodine->setToggleButton( TRUE );
    atomGroup->insert( iodine, 7 );

    atomGroupLayout->addWidget( iodine, 1, 3 );

    sulfer = new QPushButton( atomGroup, "sulfer" );
    sulfer->setMaximumSize( QSize( 30, 30 ) );
    sulfer->setToggleButton( TRUE );
    atomGroup->insert( sulfer, 3 );

    atomGroupLayout->addWidget( sulfer, 2, 3 );

    phos = new QPushButton( atomGroup, "phos" );
    phos->setMaximumSize( QSize( 30, 30 ) );
    phos->setToggleButton( TRUE );
    atomGroup->insert( phos, 4 );

    atomGroupLayout->addWidget( phos, 3, 3 );

    frame3Layout->addWidget( atomGroup, 0, 0 );
    layout70->addWidget( frame3 );

    frame8 = new QFrame( this, "frame8" );
    frame8->setFrameShape( QFrame::StyledPanel );
    frame8->setFrameShadow( QFrame::Raised );
    frame8Layout = new QGridLayout( frame8, 1, 1, 11, 6, "frame8Layout"); 

    bondGroup = new QButtonGroup( frame8, "bondGroup" );
    bondGroup->setFrameShadow( QButtonGroup::Raised );
    bondGroup->setLineWidth( 1 );
    bondGroup->setExclusive( TRUE );
    bondGroup->setColumnLayout(0, Qt::Vertical );
    bondGroup->layout()->setSpacing( 6 );
    bondGroup->layout()->setMargin( 11 );
    bondGroupLayout = new QGridLayout( bondGroup->layout() );
    bondGroupLayout->setAlignment( Qt::AlignTop );

    doubleBond = new QCheckBox( bondGroup, "doubleBond" );
    bondGroup->insert( doubleBond, 1 );

    bondGroupLayout->addWidget( doubleBond, 1, 0 );

    tripleBond = new QCheckBox( bondGroup, "tripleBond" );
    bondGroup->insert( tripleBond, 2 );

    bondGroupLayout->addWidget( tripleBond, 2, 0 );

    singleBond = new QCheckBox( bondGroup, "singleBond" );
    singleBond->setChecked( TRUE );
    bondGroup->insert( singleBond, 0 );

    bondGroupLayout->addWidget( singleBond, 0, 0 );

    frame8Layout->addWidget( bondGroup, 0, 0 );
    layout70->addWidget( frame8 );
    layout71->addLayout( layout70 );

    layout68 = new QVBoxLayout( 0, 0, 6, "layout68"); 

    line3_2 = new QFrame( this, "line3_2" );
    line3_2->setFrameShape( QFrame::HLine );
    line3_2->setFrameShadow( QFrame::Sunken );
    line3_2->setLineWidth( 2 );
    line3_2->setFrameShape( QFrame::HLine );
    layout68->addWidget( line3_2 );

    layout67 = new QVBoxLayout( 0, 0, 6, "layout67"); 

    layout49 = new QHBoxLayout( 0, 0, 6, "layout49"); 

    frame7 = new QFrame( this, "frame7" );
    frame7->setFrameShape( QFrame::StyledPanel );
    frame7->setFrameShadow( QFrame::Raised );
    frame7Layout = new QGridLayout( frame7, 1, 1, 11, 6, "frame7Layout"); 

    ringGroup = new QButtonGroup( frame7, "ringGroup" );
    ringGroup->setEnabled( TRUE );
    ringGroup->setFrameShadow( QButtonGroup::Raised );
    ringGroup->setExclusive( TRUE );
    ringGroup->setColumnLayout(0, Qt::Vertical );
    ringGroup->layout()->setSpacing( 6 );
    ringGroup->layout()->setMargin( 11 );
    ringGroupLayout = new QGridLayout( ringGroup->layout() );
    ringGroupLayout->setAlignment( Qt::AlignTop );

    sp3_8 = new QPushButton( ringGroup, "sp3_8" );
    sp3_8->setMaximumSize( QSize( 60, 32767 ) );
    sp3_8->setToggleButton( TRUE );
    sp3_8->setIconSet( QIconSet( image0 ) );

    ringGroupLayout->addWidget( sp3_8, 0, 0 );

    sp3_7 = new QPushButton( ringGroup, "sp3_7" );
    sp3_7->setMaximumSize( QSize( 60, 32767 ) );
    sp3_7->setToggleButton( TRUE );
    sp3_7->setIconSet( QIconSet( image1 ) );

    ringGroupLayout->addWidget( sp3_7, 1, 0 );

    sp2_7 = new QPushButton( ringGroup, "sp2_7" );
    sp2_7->setMaximumSize( QSize( 60, 32767 ) );
    sp2_7->setToggleButton( TRUE );
    sp2_7->setIconSet( QIconSet( image2 ) );

    ringGroupLayout->addWidget( sp2_7, 1, 1 );

    sp2_8 = new QPushButton( ringGroup, "sp2_8" );
    sp2_8->setMaximumSize( QSize( 60, 32767 ) );
    sp2_8->setToggleButton( TRUE );
    sp2_8->setIconSet( QIconSet( image3 ) );

    ringGroupLayout->addWidget( sp2_8, 0, 1 );

    sp3_6 = new QPushButton( ringGroup, "sp3_6" );
    sp3_6->setMaximumSize( QSize( 60, 32767 ) );
    sp3_6->setToggleButton( TRUE );
    sp3_6->setIconSet( QIconSet( image4 ) );

    ringGroupLayout->addWidget( sp3_6, 2, 0 );

    sp2_6 = new QPushButton( ringGroup, "sp2_6" );
    sp2_6->setMaximumSize( QSize( 60, 32767 ) );
    sp2_6->setToggleButton( TRUE );
    sp2_6->setIconSet( QIconSet( image5 ) );

    ringGroupLayout->addWidget( sp2_6, 2, 1 );

    sp3_5 = new QPushButton( ringGroup, "sp3_5" );
    sp3_5->setMaximumSize( QSize( 60, 32767 ) );
    sp3_5->setToggleButton( TRUE );
    sp3_5->setIconSet( QIconSet( image6 ) );

    ringGroupLayout->addWidget( sp3_5, 3, 0 );

    sp2_5 = new QPushButton( ringGroup, "sp2_5" );
    sp2_5->setMaximumSize( QSize( 60, 32767 ) );
    sp2_5->setToggleButton( TRUE );
    sp2_5->setIconSet( QIconSet( image7 ) );

    ringGroupLayout->addWidget( sp2_5, 3, 1 );

    frame7Layout->addWidget( ringGroup, 0, 0 );
    layout49->addWidget( frame7 );

    frame5 = new QFrame( this, "frame5" );
    frame5->setMaximumSize( QSize( 32767, 500 ) );
    frame5->setFrameShape( QFrame::StyledPanel );
    frame5->setFrameShadow( QFrame::Raised );
    frame5Layout = new QGridLayout( frame5, 1, 1, 11, 6, "frame5Layout"); 

    strucGroup = new QButtonGroup( frame5, "strucGroup" );
    strucGroup->setFrameShadow( QButtonGroup::Raised );
    strucGroup->setColumnLayout(0, Qt::Vertical );
    strucGroup->layout()->setSpacing( 6 );
    strucGroup->layout()->setMargin( 11 );
    strucGroupLayout = new QGridLayout( strucGroup->layout() );
    strucGroupLayout->setAlignment( Qt::AlignTop );

    clean = new QPushButton( strucGroup, "clean" );

    strucGroupLayout->addWidget( clean, 0, 0 );

    remH = new QPushButton( strucGroup, "remH" );

    strucGroupLayout->addWidget( remH, 2, 0 );

    addH = new QPushButton( strucGroup, "addH" );

    strucGroupLayout->addWidget( addH, 1, 0 );

    frame5Layout->addWidget( strucGroup, 0, 0 );
    layout49->addWidget( frame5 );
    layout67->addLayout( layout49 );

    line1 = new QFrame( this, "line1" );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setLineWidth( 2 );
    line1->setFrameShape( QFrame::HLine );
    layout67->addWidget( line1 );
    layout68->addLayout( layout67 );
    layout71->addLayout( layout68 );
    layout72->addLayout( layout71 );
    layout73->addLayout( layout72 );

    layout50 = new QVBoxLayout( 0, 0, 6, "layout50"); 

    line3 = new QFrame( this, "line3" );
    line3->setFrameShape( QFrame::HLine );
    line3->setFrameShadow( QFrame::Sunken );
    line3->setLineWidth( 2 );
    line3->setFrameShape( QFrame::HLine );
    layout50->addWidget( line3 );

    layout21 = new QHBoxLayout( 0, 0, 6, "layout21"); 

    layout20 = new QHBoxLayout( 0, 0, 6, "layout20"); 

    buttonOk_2 = new QPushButton( this, "buttonOk_2" );
    buttonOk_2->setMinimumSize( QSize( 50, 40 ) );
    buttonOk_2->setPixmap( image8 );
    buttonOk_2->setAutoDefault( TRUE );
    buttonOk_2->setDefault( TRUE );
    layout20->addWidget( buttonOk_2 );
    spacer1_2_2 = new QSpacerItem( 239, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout20->addItem( spacer1_2_2 );
    layout21->addLayout( layout20 );

    layout10 = new QHBoxLayout( 0, 0, 6, "layout10"); 

    Done = new QPushButton( this, "Done" );
    Done->setAutoDefault( TRUE );
    Done->setDefault( TRUE );
    layout10->addWidget( Done );
    layout21->addLayout( layout10 );
    layout50->addLayout( layout21 );
    layout73->addLayout( layout50 );

    builderDialogLayout->addLayout( layout73, 0, 0 );
    languageChange();
    resize( QSize(368, 662).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( Done, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( atomGroup, SIGNAL( clicked(int) ), this, SLOT( atomChangeSlot() ) );
    connect( ringGroup, SIGNAL( clicked(int) ), this, SLOT( ringChangeSlot() ) );
    connect( modeGroup, SIGNAL( clicked(int) ), this, SLOT( modeChangedSlot() ) );
    connect( bondGroup, SIGNAL( clicked(int) ), this, SLOT( bondChangeSlot() ) );
    connect( buttonOk_2, SIGNAL( clicked() ), this, SLOT( helpSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
builderDialog::~builderDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void builderDialog::languageChange()
{
    setCaption( tr( "Molecular Builder" ) );
    modeGroup->setTitle( tr( "Mode" ) );
    draw->setText( tr( "Draw" ) );
    retype->setText( tr( "Retype" ) );
    Delete->setText( tr( "Delete" ) );
    atomGroup->setTitle( tr( "Change Atom" ) );
    textLabel2->setText( tr( "Other" ) );
    otherAtom->clear();
    otherAtom->insertItem( tr( "Actinium" ) );
    otherAtom->insertItem( tr( "Silver" ) );
    otherAtom->insertItem( tr( "Aluminum" ) );
    otherAtom->insertItem( tr( "Americium" ) );
    otherAtom->insertItem( tr( "Argon" ) );
    otherAtom->insertItem( tr( "Arsenic" ) );
    otherAtom->insertItem( tr( "Astatine" ) );
    otherAtom->insertItem( tr( "Gold" ) );
    otherAtom->insertItem( tr( "Boron" ) );
    otherAtom->insertItem( tr( "Barium" ) );
    otherAtom->insertItem( tr( "Beryllium" ) );
    otherAtom->insertItem( tr( "Bohrium" ) );
    otherAtom->insertItem( tr( "Bismuth" ) );
    otherAtom->insertItem( tr( "Berkelium" ) );
    otherAtom->insertItem( tr( "Bromine" ) );
    otherAtom->insertItem( tr( "Carbon" ) );
    otherAtom->insertItem( tr( "Calcium" ) );
    otherAtom->insertItem( tr( "Cadmium" ) );
    otherAtom->insertItem( tr( "Cerium" ) );
    otherAtom->insertItem( tr( "Californium" ) );
    otherAtom->insertItem( tr( "Chlorine" ) );
    otherAtom->insertItem( tr( "Curium" ) );
    otherAtom->insertItem( tr( "Cobalt" ) );
    otherAtom->insertItem( tr( "Chromium" ) );
    otherAtom->insertItem( tr( "Cesium" ) );
    otherAtom->insertItem( tr( "Copper" ) );
    otherAtom->insertItem( tr( "Dubnium" ) );
    otherAtom->insertItem( tr( "Darmstadtium" ) );
    otherAtom->insertItem( tr( "Dysprosium" ) );
    otherAtom->insertItem( tr( "Erbium" ) );
    otherAtom->insertItem( tr( "Einsteinium" ) );
    otherAtom->insertItem( tr( "Europium" ) );
    otherAtom->insertItem( tr( "Fluorine" ) );
    otherAtom->insertItem( tr( "Iron" ) );
    otherAtom->insertItem( tr( "Fermium" ) );
    otherAtom->insertItem( tr( "Francium" ) );
    otherAtom->insertItem( tr( "Gallium" ) );
    otherAtom->insertItem( tr( "Gadolinium" ) );
    otherAtom->insertItem( tr( "Germanium" ) );
    otherAtom->insertItem( tr( "Hydrogen" ) );
    otherAtom->insertItem( tr( "Helium" ) );
    otherAtom->insertItem( tr( "Hafnium" ) );
    otherAtom->insertItem( tr( "Mercury" ) );
    otherAtom->insertItem( tr( "Holmium" ) );
    otherAtom->insertItem( tr( "Hassium" ) );
    otherAtom->insertItem( tr( "Iodine" ) );
    otherAtom->insertItem( tr( "Indium" ) );
    otherAtom->insertItem( tr( "Iridium" ) );
    otherAtom->insertItem( tr( "Potassium" ) );
    otherAtom->insertItem( tr( "Krypton" ) );
    otherAtom->insertItem( tr( "Lanthanum" ) );
    otherAtom->insertItem( tr( "Lithium" ) );
    otherAtom->insertItem( tr( "Lawrencium" ) );
    otherAtom->insertItem( tr( "Lutetium" ) );
    otherAtom->insertItem( tr( "Mendelevium" ) );
    otherAtom->insertItem( tr( "Magnesium" ) );
    otherAtom->insertItem( tr( "Manganese" ) );
    otherAtom->insertItem( tr( "Molybdenum" ) );
    otherAtom->insertItem( tr( "Meitnerium" ) );
    otherAtom->insertItem( tr( "Nitrogen" ) );
    otherAtom->insertItem( tr( "Sodium" ) );
    otherAtom->insertItem( tr( "Neon" ) );
    otherAtom->insertItem( tr( "Niobium" ) );
    otherAtom->insertItem( tr( "Neodymium" ) );
    otherAtom->insertItem( tr( "Nickel" ) );
    otherAtom->insertItem( tr( "Nobelium" ) );
    otherAtom->insertItem( tr( "Neptunium" ) );
    otherAtom->insertItem( tr( "Oxygen" ) );
    otherAtom->insertItem( tr( "Osmium" ) );
    otherAtom->insertItem( tr( "Phosphorus" ) );
    otherAtom->insertItem( tr( "Palladium" ) );
    otherAtom->insertItem( tr( "Polonium" ) );
    otherAtom->insertItem( tr( "Lead" ) );
    otherAtom->insertItem( tr( "Platinum" ) );
    otherAtom->insertItem( tr( "Praseodymium" ) );
    otherAtom->insertItem( tr( "Promethium" ) );
    otherAtom->insertItem( tr( "Plutonium" ) );
    otherAtom->insertItem( tr( "Protactinium" ) );
    otherAtom->insertItem( tr( "Radium" ) );
    otherAtom->insertItem( tr( "Rubidium" ) );
    otherAtom->insertItem( tr( "Rhenium" ) );
    otherAtom->insertItem( tr( "Rutherfordium" ) );
    otherAtom->insertItem( tr( "Rhodium" ) );
    otherAtom->insertItem( tr( "Radon" ) );
    otherAtom->insertItem( tr( "Ruthenium" ) );
    otherAtom->insertItem( tr( "Sulfur" ) );
    otherAtom->insertItem( tr( "Antimony" ) );
    otherAtom->insertItem( tr( "Scandium" ) );
    otherAtom->insertItem( tr( "Selenium" ) );
    otherAtom->insertItem( tr( "Seaborgium" ) );
    otherAtom->insertItem( tr( "Silicon" ) );
    otherAtom->insertItem( tr( "Samarium" ) );
    otherAtom->insertItem( tr( "Tin" ) );
    otherAtom->insertItem( tr( "Strontium" ) );
    otherAtom->insertItem( tr( "Tantalum" ) );
    otherAtom->insertItem( tr( "Terbium" ) );
    otherAtom->insertItem( tr( "Technetium" ) );
    otherAtom->insertItem( tr( "Tellurium" ) );
    otherAtom->insertItem( tr( "Thorium" ) );
    otherAtom->insertItem( tr( "Titanium" ) );
    otherAtom->insertItem( tr( "Thallium" ) );
    otherAtom->insertItem( tr( "Thulium" ) );
    otherAtom->insertItem( tr( "Uranium" ) );
    otherAtom->insertItem( tr( "Ununbium" ) );
    otherAtom->insertItem( tr( "Ununnilium" ) );
    otherAtom->insertItem( tr( "Ununumium" ) );
    otherAtom->insertItem( tr( "Vanadium" ) );
    otherAtom->insertItem( tr( "Tungsten" ) );
    otherAtom->insertItem( tr( "Xenon" ) );
    otherAtom->insertItem( tr( "Yttrium" ) );
    otherAtom->insertItem( tr( "Ytterbium" ) );
    otherAtom->insertItem( tr( "Zinc" ) );
    otherAtom->insertItem( tr( "Zirconium" ) );
    otherAtom->insertItem( tr( "None" ) );
    otherAtom->setCurrentItem( 15 );
    bromine->setText( tr( "Br" ) );
    hydrogen->setText( tr( "H" ) );
    flourine->setText( tr( "F" ) );
    carbon->setText( tr( "C" ) );
    oxygen->setText( tr( "O" ) );
    chlorine->setText( tr( "Cl" ) );
    nitrogen->setText( tr( "N" ) );
    iodine->setText( tr( "I" ) );
    sulfer->setText( tr( "S" ) );
    phos->setText( tr( "P" ) );
    bondGroup->setTitle( tr( "Bond" ) );
    doubleBond->setText( tr( "Double" ) );
    tripleBond->setText( tr( "Triple" ) );
    singleBond->setText( tr( "Single" ) );
    ringGroup->setTitle( tr( "Rings" ) );
    sp3_8->setText( QString::null );
    sp3_7->setText( QString::null );
    sp2_7->setText( QString::null );
    sp2_8->setText( QString::null );
    sp3_6->setText( QString::null );
    sp2_6->setText( QString::null );
    sp3_5->setText( QString::null );
    sp2_5->setText( QString::null );
    strucGroup->setTitle( tr( "Structure" ) );
    clean->setText( tr( "Clean" ) );
    remH->setText( tr( "Delete H" ) );
    addH->setText( tr( "Add H" ) );
    buttonOk_2->setText( QString::null );
    buttonOk_2->setAccel( QKeySequence( QString::null ) );
    Done->setText( tr( "Done" ) );
    Done->setAccel( QKeySequence( QString::null ) );
}

