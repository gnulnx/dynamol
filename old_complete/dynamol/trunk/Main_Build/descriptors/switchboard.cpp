/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "switchboard.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <qstringlist.h>
#include <qmessagebox.h>
#include "qregexp.h"
#include "constitutional.h"
#include "counts.h"
#include "ringcounts.h"
#include "electrotop.h"
#include "functional_groups.h"
#include "fingerprints.h"

/** Header is for the desc selection tool */
#include "qlistview.h"
#include "descsel.h"
#include "atomenv.h"
#include "atomsig3.h"
#include "atomsig2.h"


/** Dynatype Includes */
#include "../dynatype/dtype.h"
#include "../dynatype/molecule.h"

using namespace std;
switchBoard::switchBoard(QObject *parent, const char *name)
 : QObject(parent, name) 
{
   ////cout <<"Building switchBoard Classes"<<endl;
   classMap["Constitutional"] = new Constitutional();
   classMap["Counts"] = new Counts();
   classMap["ringCounts"] = new ringCounts();
   classMap["ElectroTopological"] = new ElectroTop();
   classMap["Functional_Groups"] = new Functional_Groups();
   //classMap["FingerPrints"] = new FingerPrints();
   //classMap["Atom Signatures"] = new atomEnv();
   classMap["Height 3"] = new atomSig3();
   classMap["Height 2"] = new atomSig2();
   ////cout <<"Done building switchboard Classes"<<endl;
}


switchBoard::~switchBoard()
{
}

void switchBoard::selectDesc(set<QString> &descSet, vector<QString> &descVec) {
   descSel *dialog = new descSel;
   dialog->listView->setSelectionMode(QListView::Multi);
   buildDescList2(dialog);
   
   if (dialog->exec()) {
      QListViewItem *item;
      QListViewItemIterator it(dialog->listView);
      while ( it.current() ) {
         item = it.current();         
         if (item->childCount() == 0 && (item->isSelected() || selectedParent(item))) {
            QString desc = item->parent()->text(0);
            desc += ":";
            desc += item->text(0);
	    descSet.insert(desc);
            descVec.push_back(item->text(0));
	 }        
         ++it;
      }
   }
}

bool switchBoard::selectedParent(QListViewItem *item) {
   QListViewItem *tmp = item;
   while (true) {
      QListViewItem *parent = tmp->parent();
      if (parent && parent->isSelected())
         return true;
      if (!parent)
         return false;
         
      tmp = parent;
   }
   return false;
}

void switchBoard::buildDescList2(descSel *&dialog) {
   ////cout <<"You are in builDescList2"<<endl;
   QListView *list = dialog->listView;
   list->setSorting(-1);
   
   QListViewItem *p1, *p2, *c, *c2;
      p1 = new QListViewItem(list, "Functional_Groups");
      p2 = new QListViewItem(p1, "nEsters", "Number of Esters");
      p2 = new QListViewItem(p1, "nOH", "Number of Hydroxyl Groups");
      p2 = new QListViewItem(p1, "nSH", "Number of -SH Groups");
      
   p1 = new QListViewItem(list, "Constitutional");
      p2 = new QListViewItem(p1, "molWeight", "The Molecular Weight");
      p2 = new QListViewItem(p1, "Counts");
         c = new QListViewItem(p2, "nTriple", "Number of Triple Bonds");
         c = new QListViewItem(p2, "nDouble", "Number of Double Bonds");
         c = new QListViewItem(p2, "nSingle", "Number of Single Bonds");
         c = new QListViewItem(p2, "nOxygen", "Number of Oxygen Atoms");
         c = new QListViewItem(p2, "nCarbon", "Number f Carbon Atoms");
         c = new QListViewItem(p2, "nNitrogen", "Number of Nitrogen Atoms");
         c = new QListViewItem(p2, "nSulfer", "Number of Sulfer Atoms");
         c = new QListViewItem(p2, "nPhosporus", "Number of Phosphorus Atoms");
         c = new QListViewItem(p2, "nChlorine", "Number of Chlorine Atoms");
         c = new QListViewItem(p2, "nFlourine", "Number of Flourine Atoms");
         c = new QListViewItem(p2, "nBromine", "Number of Bromine Atoms");
         c = new QListViewItem(p2, "nIodine", "Number of Iodine Atoms");
         c = new QListViewItem(p2, "nHydrogen", "Number of Hydrogen Atoms");
         c = new QListViewItem(p2, "Hyd_Heavy_Ratio", "Ratio of Hydrogen to Heavy Atoms");       
         
         c = new QListViewItem(p2, "ringCounts");
            c2 = new QListViewItem(c, "aroCount", "Number of Aromatic Rings");
            c2 = new QListViewItem(c, "ring10", "Number of 10 Atom Rings");
            c2 = new QListViewItem(c, "ring9", "Number of 9 Atom Rings");
            c2 = new QListViewItem(c, "ring8", "Number of 8 Atom Rings");
            c2 = new QListViewItem(c, "ring7", "Number of 7 Atom Rings");
            c2 = new QListViewItem(c, "ring6", "Number of 6 Atom Rings");
            c2 = new QListViewItem(c, "ring5", "Number of 5 Atom Rings");
            c2 = new QListViewItem(c, "ring4", "Number of 4 Atom Rings");
            c2 = new QListViewItem(c, "ring3", "Number of 3 Atom Rings");
            
     p1 = new QListViewItem(list, "Topological");
         p2 = new QListViewItem(p1, "ElectroTopological");
            c = new QListViewItem(p2, "i_ESCount", "(i) E-State Count");
            c = new QListViewItem(p2, "br_ESCount", "(br) E-State Count");
            c = new QListViewItem(p2, "cl_ESCount", "(cl) E-State Count");
            c = new QListViewItem(p2, "f_ESCount", "(f) E-State Count");
            c = new QListViewItem(p2, "p5_ESCount", "(p5) E-State Count");
            c = new QListViewItem(p2, "p4_ESCount", "(p4) E-State Count");
            c = new QListViewItem(p2, "p3_ESCount", "(p3) E-State Count");
            c = new QListViewItem(p2, "p2_ESCount", "(p2) E-State Count");
            c = new QListViewItem(p2, "ss_ESCount", "(ss) E-State Count");
            c = new QListViewItem(p2, "s6_ESCount", "(s6) E-State Count");
            c = new QListViewItem(p2, "s4_ESCount", "(s4) E-State Count");
            c = new QListViewItem(p2, "s2_ESCount", "(s2) E-State Count");
            c = new QListViewItem(p2, "sh_ESCount", "(sh) E-State Count");
            c = new QListViewItem(p2, "os_ESCount", "(ow) E-State Count");
            c = new QListViewItem(p2, "oh_ESCount", "(oh) E-State Count");
            c = new QListViewItem(p2, "o_ESCount", "(o) E-State Count");
            c = new QListViewItem(p2, "nb_ESCount", "(nb) E-State Count");
            c = new QListViewItem(p2, "no_ESCount", "(no) E-State Count");
            c = new QListViewItem(p2, "nh_ESCount", "(nh) E-State Count");
            c = new QListViewItem(p2, "na_ESCount", "(na) E-State Count");
            c = new QListViewItem(p2, "n4_ESCount", "(n4) E-State Count");
            c = new QListViewItem(p2, "n3_ESCount", "(n3) E-State Count");
            c = new QListViewItem(p2, "n2_ESCount", "(n2) E-State Count");
            c = new QListViewItem(p2, "n1_ESCount", "(n1) E-State Count");
            c = new QListViewItem(p2, "n_ESCount", "(n) E-State Count");
            c = new QListViewItem(p2, "ca_ESCount", "(ca) E-State Count");
            c = new QListViewItem(p2, "c3_ESCount", "(c3) E-State Count");
            c = new QListViewItem(p2, "c2_ESCount", "(c2) E-State Count");
            c = new QListViewItem(p2, "c1_ESCount", "(c1) E-State Count");
            c = new QListViewItem(p2, "c_ESCount", "(c) E-State Count");
            
            c = new QListViewItem(p2, "i_EState", "E-State Value of the (i) Atom Type");
            c = new QListViewItem(p2, "br_EState", "E-State Value of the (br) Atom Type");
            c = new QListViewItem(p2, "cl_EState", "E-State Value of the (cl) Atom Type");
            c = new QListViewItem(p2, "f_EState", "E-State Value of the (f) Atom Type");
            c = new QListViewItem(p2, "p5_EState", "E-State Value of the (p5) Atom Type");
            c = new QListViewItem(p2, "p4_EState", "E-State Value of the (p4) Atom Type");
            c = new QListViewItem(p2, "p3_EState", "E-State Value of the (p3) Atom Type");
            c = new QListViewItem(p2, "p2_EState", "E-State Value of the (p2) Atom Type");
            c = new QListViewItem(p2, "ss_EState", "E-State Value of the (ss) Atom Type");
            c = new QListViewItem(p2, "s6_EState", "E-State Value of the (s6) Atom Type");
            c = new QListViewItem(p2, "s4_EState", "E-State Value of the (s4) Atom Type");
            c = new QListViewItem(p2, "s2_EState", "E-State Value of the (s2) Atom Type");
            c = new QListViewItem(p2, "sh_EState", "E-State Value of the (sh) Atom Type");
            c = new QListViewItem(p2, "os_EState", "E-State Value of the (os) Atom Type");
            c = new QListViewItem(p2, "oh_EState", "E-State Value of the (oh) Atom Type");
            c = new QListViewItem(p2, "o_EState", "E-State Value of the (o) Atom Type");
            c = new QListViewItem(p2, "nb_EState", "E-State Value of the (nb) Atom Type");
            c = new QListViewItem(p2, "no_EState", "E-State Value of the (no) Atom Type");
            c = new QListViewItem(p2, "nh_EState", "E-State Value of the (nh) Atom Type");
            c = new QListViewItem(p2, "na_EState", "E-State Value of the (na) Atom Type");
            c = new QListViewItem(p2, "n4_EState", "E-State Value of the (n4) Atom Type");
            c = new QListViewItem(p2, "n3_EState", "E-State Value of the (n3) Atom Type");
            c = new QListViewItem(p2, "n2_EState", "E-State Value of the (n2) Atom Type");
            c = new QListViewItem(p2, "n1_EState", "E-State Value of the (n1) Atom Type");
            c = new QListViewItem(p2, "n_EState", "E-State Value of the (n) Atom Type");
            c = new QListViewItem(p2, "ca_EState", "E-State Value of the (ca) Atom Type");
            c = new QListViewItem(p2, "c3_EState", "E-State Value of the (c3) Atom Type");
            c = new QListViewItem(p2, "c2_EState", "E-State Value of the (c2) Atom Type");
            c = new QListViewItem(p2, "c1_EState", "E-State Value of the (c1) Atom Type");
            c = new QListViewItem(p2, "c_EState", "E-State Value of the (c) Atom Type");
            
   //p1 = new QListViewItem(list, "FingerPrints");
   //   p2 = new QListViewItem(p1, "gafffp");
   p1 = new QListViewItem(list, "Atom Signatures");
   buildAtomEnvLists(p1, p2);
          
}

void switchBoard::buildAtomEnvLists(QListViewItem *p1, QListViewItem *p2) {
	QListViewItem *c;
	p2 = new QListViewItem(p1, "Height 3", "Height 3 (Angles Clusters)");
         c = new QListViewItem(p2, "h3gfp_100", "Shannon Entropy 0.238015");
         c = new QListViewItem(p2, "h3gfp_99", "Shannon Entropy 0.239314");
         c = new QListViewItem(p2, "h3gfp_98", "Shannon Entropy 0.240225");
         c = new QListViewItem(p2, "h3gfp_97", "Shannon Entropy 0.243617");
         c = new QListViewItem(p2, "h3gfp_96", "Shannon Entropy 0.244568");
         c = new QListViewItem(p2, "h3gfp_95", "Shannon Entropy 0.249716");
         c = new QListViewItem(p2, "h3gfp_94", "Shannon Entropy 0.251964");
         c = new QListViewItem(p2, "h3gfp_93", "Shannon Entropy 0.253518");
         c = new QListViewItem(p2, "h3gfp_92", "Shannon Entropy 0.254532");
         c = new QListViewItem(p2, "h3gfp_91", "Shannon Entropy 0.260651");
         c = new QListViewItem(p2, "h3gfp_90", "Shannon Entropy 0.260691");
         c = new QListViewItem(p2, "h3gfp_89", "Shannon Entropy 0.264200");
         c = new QListViewItem(p2, "h3gfp_88", "Shannon Entropy 0.265585");
         c = new QListViewItem(p2, "h3gfp_87", "Shannon Entropy 0.266566");
         c = new QListViewItem(p2, "h3gfp_86", "Shannon Entropy 0.271439");
         c = new QListViewItem(p2, "h3gfp_85", "Shannon Entropy 0.272856");
         c = new QListViewItem(p2, "h3gfp_84", "Shannon Entropy 0.275297");
         c = new QListViewItem(p2, "h3gfp_83", "Shannon Entropy 0.275929");
         c = new QListViewItem(p2, "h3gfp_82", "Shannon Entropy 0.276137");
         c = new QListViewItem(p2, "h3gfp_81", "Shannon Entropy 0.277024");
         c = new QListViewItem(p2, "h3gfp_80", "Shannon Entropy 0.278453");
         c = new QListViewItem(p2, "h3gfp_79", "Shannon Entropy 0.283031");
         c = new QListViewItem(p2, "h3gfp_78", "Shannon Entropy 0.283268");
         c = new QListViewItem(p2, "h3gfp_77", "Shannon Entropy 0.287169");
         c = new QListViewItem(p2, "h3gfp_76", "Shannon Entropy 0.288194");
         c = new QListViewItem(p2, "h3gfp_75", "Shannon Entropy 0.288737");
         c = new QListViewItem(p2, "h3gfp_74", "Shannon Entropy 0.288768");
         c = new QListViewItem(p2, "h3gfp_73", "Shannon Entropy 0.294081");
         c = new QListViewItem(p2, "h3gfp_72", "Shannon Entropy 0.294126");
         c = new QListViewItem(p2, "h3gfp_71", "Shannon Entropy 0.296138");
         c = new QListViewItem(p2, "h3gfp_70", "Shannon Entropy 0.299572");
         c = new QListViewItem(p2, "h3gfp_69", "Shannon Entropy 0.301178");
         c = new QListViewItem(p2, "h3gfp_68", "Shannon Entropy 0.302051");
         c = new QListViewItem(p2, "h3gfp_67", "Shannon Entropy 0.306700");
         c = new QListViewItem(p2, "h3gfp_66", "Shannon Entropy 0.308645");
         c = new QListViewItem(p2, "h3gfp_65", "Shannon Entropy 0.311502");
         c = new QListViewItem(p2, "h3gfp_64", "Shannon Entropy 0.313539");
         c = new QListViewItem(p2, "h3gfp_63", "Shannon Entropy 0.316820");
         c = new QListViewItem(p2, "h3gfp_62", "Shannon Entropy 0.319471");
         c = new QListViewItem(p2, "h3gfp_61", "Shannon Entropy 0.321693");
         c = new QListViewItem(p2, "h3gfp_60", "Shannon Entropy 0.325138");
         c = new QListViewItem(p2, "h3gfp_59", "Shannon Entropy 0.328893");
         c = new QListViewItem(p2, "h3gfp_58", "Shannon Entropy 0.329171");
         c = new QListViewItem(p2, "h3gfp_57", "Shannon Entropy 0.335060");
         c = new QListViewItem(p2, "h3gfp_56", "Shannon Entropy 0.335625");
         c = new QListViewItem(p2, "h3gfp_55", "Shannon Entropy 0.335929");
         c = new QListViewItem(p2, "h3gfp_54", "Shannon Entropy 0.338758");
         c = new QListViewItem(p2, "h3gfp_53", "Shannon Entropy 0.339519");
         c = new QListViewItem(p2, "h3gfp_52", "Shannon Entropy 0.345046");
         c = new QListViewItem(p2, "h3gfp_51", "Shannon Entropy 0.348304");
         c = new QListViewItem(p2, "h3gfp_50", "Shannon Entropy 0.352191");
         c = new QListViewItem(p2, "h3gfp_49", "Shannon Entropy 0.356487");
         c = new QListViewItem(p2, "h3gfp_48", "Shannon Entropy 0.357491");
         c = new QListViewItem(p2, "h3gfp_47", "Shannon Entropy 0.357735");
         c = new QListViewItem(p2, "h3gfp_46", "Shannon Entropy 0.381405");
         c = new QListViewItem(p2, "h3gfp_45", "Shannon Entropy 0.386026");
         c = new QListViewItem(p2, "h3gfp_44", "Shannon Entropy 0.391519");
         c = new QListViewItem(p2, "h3gfp_43", "Shannon Entropy 0.400762");
         c = new QListViewItem(p2, "h3gfp_42", "Shannon Entropy 0.402608");
         c = new QListViewItem(p2, "h3gfp_41", "Shannon Entropy 0.404752");
         c = new QListViewItem(p2, "h3gfp_40", "Shannon Entropy 0.414507");
         c = new QListViewItem(p2, "h3gfp_39", "Shannon Entropy 0.422128");
         c = new QListViewItem(p2, "h3gfp_38", "Shannon Entropy 0.425398");
         c = new QListViewItem(p2, "h3gfp_37", "Shannon Entropy 0.434462");
         c = new QListViewItem(p2, "h3gfp_36", "Shannon Entropy 0.434574");
         c = new QListViewItem(p2, "h3gfp_35", "Shannon Entropy 0.443591");
         c = new QListViewItem(p2, "h3gfp_34", "Shannon Entropy 0.448227");
         c = new QListViewItem(p2, "h3gfp_33", "Shannon Entropy 0.450068");
         c = new QListViewItem(p2, "h3gfp_32", "Shannon Entropy 0.460696");
         c = new QListViewItem(p2, "h3gfp_31", "Shannon Entropy 0.461595");
         c = new QListViewItem(p2, "h3gfp_30", "Shannon Entropy 0.473653");
         c = new QListViewItem(p2, "h3gfp_29", "Shannon Entropy 0.476113");
         c = new QListViewItem(p2, "h3gfp_28", "Shannon Entropy 0.486353");
         c = new QListViewItem(p2, "h3gfp_27", "Shannon Entropy 0.487064");
         c = new QListViewItem(p2, "h3gfp_26", "Shannon Entropy 0.510932");
         c = new QListViewItem(p2, "h3gfp_25", "Shannon Entropy 0.534426");
         c = new QListViewItem(p2, "h3gfp_24", "Shannon Entropy 0.534613");
         c = new QListViewItem(p2, "h3gfp_23", "Shannon Entropy 0.546746");
         c = new QListViewItem(p2, "h3gfp_22", "Shannon Entropy 0.559287");
         c = new QListViewItem(p2, "h3gfp_21", "Shannon Entropy 0.559465");
         c = new QListViewItem(p2, "h3gfp_20", "Shannon Entropy 0.568714");
         c = new QListViewItem(p2, "h3gfp_19", "Shannon Entropy 0.599573");
         c = new QListViewItem(p2, "h3gfp_18", "Shannon Entropy 0.625958");
         c = new QListViewItem(p2, "h3gfp_17", "Shannon Entropy 0.656839");
         c = new QListViewItem(p2, "h3gfp_16", "Shannon Entropy 0.682916");
         c = new QListViewItem(p2, "h3gfp_15", "Shannon Entropy 0.689681");
         c = new QListViewItem(p2, "h3gfp_14", "Shannon Entropy 0.690214");
         c = new QListViewItem(p2, "h3gfp_13", "Shannon Entropy 0.703843");
         c = new QListViewItem(p2, "h3gfp_12", "Shannon Entropy 0.744014");
         c = new QListViewItem(p2, "h3gfp_11", "Shannon Entropy 0.753013");
         c = new QListViewItem(p2, "h3gfp_10", "Shannon Entropy 0.755417");
         c = new QListViewItem(p2, "h3gfp_9", "Shannon Entropy 0.761969");
         c = new QListViewItem(p2, "h3gfp_8", "Shannon Entropy 0.787846");
         c = new QListViewItem(p2, "h3gfp_7", "Shannon Entropy 0.809077");
         c = new QListViewItem(p2, "h3gfp_6", "Shannon Entropy 0.871338");
         c = new QListViewItem(p2, "h3gfp_5", "Shannon Entropy 0.923631");
         c = new QListViewItem(p2, "h3gfp_4", "Shannon Entropy 0.953076");
         c = new QListViewItem(p2, "h3gfp_3", "Shannon Entropy 0.984772");
         c = new QListViewItem(p2, "h3gfp_2", "Shannon Entropy 0.998643");
         c = new QListViewItem(p2, "h3gfp_1", "Shannon Entropy 0.999858");

      p2 = new QListViewItem(p1, "Height 2", "Height 2 (Bond Clusters)");
         c = new QListViewItem(p2, "h2gfp_100", "Shannon Entropy 0.2349175");
         c = new QListViewItem(p2, "h2gfp_99", "Shannon Entropy 0.2358335");
         c = new QListViewItem(p2, "h2gfp_98", "Shannon Entropy 0.2360915");
         c = new QListViewItem(p2, "h2gfp_97", "Shannon Entropy 0.2365545");
         c = new QListViewItem(p2, "h2gfp_96", "Shannon Entropy 0.2439005");
         c = new QListViewItem(p2, "h2gfp_95", "Shannon Entropy 0.2462275");
         c = new QListViewItem(p2, "h2gfp_94", "Shannon Entropy 0.2487605");
         c = new QListViewItem(p2, "h2gfp_93", "Shannon Entropy 0.2494295");
         c = new QListViewItem(p2, "h2gfp_92", "Shannon Entropy 0.2504165");
         c = new QListViewItem(p2, "h2gfp_91", "Shannon Entropy 0.2514955");
         c = new QListViewItem(p2, "h2gfp_90", "Shannon Entropy 0.2535545");
         c = new QListViewItem(p2, "h2gfp_89", "Shannon Entropy 0.2556875");
         c = new QListViewItem(p2, "h2gfp_88", "Shannon Entropy 0.2730435");
         c = new QListViewItem(p2, "h2gfp_87", "Shannon Entropy 0.2779425");
         c = new QListViewItem(p2, "h2gfp_86", "Shannon Entropy 0.2793905");
         c = new QListViewItem(p2, "h2gfp_85", "Shannon Entropy 0.2876125");
         c = new QListViewItem(p2, "h2gfp_84", "Shannon Entropy 0.2905625");
         c = new QListViewItem(p2, "h2gfp_83", "Shannon Entropy 0.2974585");
         c = new QListViewItem(p2, "h2gfp_82", "Shannon Entropy 0.3027665");
         c = new QListViewItem(p2, "h2gfp_81", "Shannon Entropy 0.3045725");
         c = new QListViewItem(p2, "h2gfp_80", "Shannon Entropy 0.3128585");
         c = new QListViewItem(p2, "h2gfp_79", "Shannon Entropy 0.3133335");
         c = new QListViewItem(p2, "h2gfp_78", "Shannon Entropy 0.3212665");
         c = new QListViewItem(p2, "h2gfp_77", "Shannon Entropy 0.3215915");
         c = new QListViewItem(p2, "h2gfp_76", "Shannon Entropy 0.3260865");
         c = new QListViewItem(p2, "h2gfp_75", "Shannon Entropy 0.3267515");
         c = new QListViewItem(p2, "h2gfp_74", "Shannon Entropy 0.3307435");
         c = new QListViewItem(p2, "h2gfp_73", "Shannon Entropy 0.3331875");
         c = new QListViewItem(p2, "h2gfp_72", "Shannon Entropy 0.3365655");
         c = new QListViewItem(p2, "h2gfp_71", "Shannon Entropy 0.3385605");
         c = new QListViewItem(p2, "h2gfp_70", "Shannon Entropy 0.3413655");
         c = new QListViewItem(p2, "h2gfp_69", "Shannon Entropy 0.3418665");
         c = new QListViewItem(p2, "h2gfp_68", "Shannon Entropy 0.3452735");
         c = new QListViewItem(p2, "h2gfp_67", "Shannon Entropy 0.3501225");
         c = new QListViewItem(p2, "h2gfp_66", "Shannon Entropy 0.3521395");
         c = new QListViewItem(p2, "h2gfp_65", "Shannon Entropy 0.3542545");
         c = new QListViewItem(p2, "h2gfp_64", "Shannon Entropy 0.3849945");
         c = new QListViewItem(p2, "h2gfp_63", "Shannon Entropy 0.3941045");
         c = new QListViewItem(p2, "h2gfp_62", "Shannon Entropy 0.3944095");
         c = new QListViewItem(p2, "h2gfp_61", "Shannon Entropy 0.4000445");
         c = new QListViewItem(p2, "h2gfp_60", "Shannon Entropy 0.4032935");
         c = new QListViewItem(p2, "h2gfp_59", "Shannon Entropy 0.4098065");
         c = new QListViewItem(p2, "h2gfp_58", "Shannon Entropy 0.4162895");
         c = new QListViewItem(p2, "h2gfp_57", "Shannon Entropy 0.4220035");
         c = new QListViewItem(p2, "h2gfp_56", "Shannon Entropy 0.4252685");
         c = new QListViewItem(p2, "h2gfp_55", "Shannon Entropy 0.4253805");
         c = new QListViewItem(p2, "h2gfp_54", "Shannon Entropy 0.4254485");
         c = new QListViewItem(p2, "h2gfp_53", "Shannon Entropy 0.4329635");
         c = new QListViewItem(p2, "h2gfp_52", "Shannon Entropy 0.4342525");
         c = new QListViewItem(p2, "h2gfp_51", "Shannon Entropy 0.4345195");
         c = new QListViewItem(p2, "h2gfp_50", "Shannon Entropy 0.4346995");
         c = new QListViewItem(p2, "h2gfp_49", "Shannon Entropy 0.4423585");
         c = new QListViewItem(p2, "h2gfp_48", "Shannon Entropy 0.4438035");
         c = new QListViewItem(p2, "h2gfp_47", "Shannon Entropy 0.4452015");
         c = new QListViewItem(p2, "h2gfp_46", "Shannon Entropy 0.4459285");
         c = new QListViewItem(p2, "h2gfp_45", "Shannon Entropy 0.4537915");
         c = new QListViewItem(p2, "h2gfp_44", "Shannon Entropy 0.4728605");
         c = new QListViewItem(p2, "h2gfp_43", "Shannon Entropy 0.4757525");
         c = new QListViewItem(p2, "h2gfp_42", "Shannon Entropy 0.4803045");
         c = new QListViewItem(p2, "h2gfp_41", "Shannon Entropy 0.4904615");
         c = new QListViewItem(p2, "h2gfp_40", "Shannon Entropy 0.4907145");
         c = new QListViewItem(p2, "h2gfp_39", "Shannon Entropy 0.5006015");
         c = new QListViewItem(p2, "h2gfp_38", "Shannon Entropy 0.5016915");
         c = new QListViewItem(p2, "h2gfp_37", "Shannon Entropy 0.5069605");
         c = new QListViewItem(p2, "h2gfp_36", "Shannon Entropy 0.5441345");
         c = new QListViewItem(p2, "h2gfp_35", "Shannon Entropy 0.5458865");
         c = new QListViewItem(p2, "h2gfp_34", "Shannon Entropy 0.5479425");
         c = new QListViewItem(p2, "h2gfp_33", "Shannon Entropy 0.5501675");
         c = new QListViewItem(p2, "h2gfp_32", "Shannon Entropy 0.5584725");
         c = new QListViewItem(p2, "h2gfp_31", "Shannon Entropy 0.5586505");
         c = new QListViewItem(p2, "h2gfp_30", "Shannon Entropy 0.5757415");
         c = new QListViewItem(p2, "h2gfp_29", "Shannon Entropy 0.5849935");
         c = new QListViewItem(p2, "h2gfp_28", "Shannon Entropy 0.5936525");
         c = new QListViewItem(p2, "h2gfp_27", "Shannon Entropy 0.6287425");
         c = new QListViewItem(p2, "h2gfp_26", "Shannon Entropy 0.6376105");
         c = new QListViewItem(p2, "h2gfp_25", "Shannon Entropy 0.6439795");
         c = new QListViewItem(p2, "h2gfp_24", "Shannon Entropy 0.6792995");
         c = new QListViewItem(p2, "h2gfp_23", "Shannon Entropy 0.6991655");
         c = new QListViewItem(p2, "h2gfp_22", "Shannon Entropy 0.7158055");
         c = new QListViewItem(p2, "h2gfp_21", "Shannon Entropy 0.7252055");
         c = new QListViewItem(p2, "h2gfp_20", "Shannon Entropy 0.7380345");
         c = new QListViewItem(p2, "h2gfp_19", "Shannon Entropy 0.7449775");
         c = new QListViewItem(p2, "h2gfp_18", "Shannon Entropy 0.7515725");
         c = new QListViewItem(p2, "h2gfp_17", "Shannon Entropy 0.7561475");
         c = new QListViewItem(p2, "h2gfp_16", "Shannon Entropy 0.7687575");
         c = new QListViewItem(p2, "h2gfp_15", "Shannon Entropy 0.7833755");
         c = new QListViewItem(p2, "h2gfp_14", "Shannon Entropy 0.7923955");
         c = new QListViewItem(p2, "h2gfp_13", "Shannon Entropy 0.7972495");
         c = new QListViewItem(p2, "h2gfp_12", "Shannon Entropy 0.8150725");
         c = new QListViewItem(p2, "h2gfp_11", "Shannon Entropy 0.8184985");
         c = new QListViewItem(p2, "h2gfp_10", "Shannon Entropy 0.8438735");
         c = new QListViewItem(p2, "h2gfp_9", "Shannon Entropy 0.8594295");
         c = new QListViewItem(p2, "h2gfp_8", "Shannon Entropy 0.9167595");
         c = new QListViewItem(p2, "h2gfp_7", "Shannon Entropy 0.9494565");
         c = new QListViewItem(p2, "h2gfp_6", "Shannon Entropy 0.9690465");
         c = new QListViewItem(p2, "h2gfp_5", "Shannon Entropy 0.9690785");
         c = new QListViewItem(p2, "h2gfp_4", "Shannon Entropy 0.9691045");
         c = new QListViewItem(p2, "h2gfp_3", "Shannon Entropy 0.9800295");
         c = new QListViewItem(p2, "h2gfp_2", "Shannon Entropy 0.9833295");
         c = new QListViewItem(p2, "h2gfp_1", "Shannon Entropy 0.9910345");
}

void switchBoard::buildDescList(descSel *&dialog) {
   //LINUX 2
   QString Path = getenv("DYNAMOL");
   Path += "/OpenDescriptor/open_desc.prj";

   //WINDOWS 1
   //QString Path = "OpenDescriptor\\open_desc.prj";

   ifstream inFile(Path.latin1(), ios::in);
   if (!inFile) {
      ////cout <<"OpenDescripter.prj not found at: " << Path << endl;
	  QMessageBox::critical( 0, "Dynamol", "Open Desc project file not opend");
	  return;
   }

   // First parse the file and build class/function lists.
   // You are only going to display public functions in classes
   // That are derived from class Desc
   vector<QString> allClasses;
   map<QString, QString> classBaseMap;
   string line;
   QString qLine;
   while ( !inFile.eof() ) {
      getline(inFile, line);
      qLine = line;
      if (qLine.contains("class") && qLine.contains("extends")) {
           QRegExp sep( " +" );
	   QString firstPart = qLine.section("{", 0);
           QString className = firstPart.section(sep, 1, 1);
	   QString baseName = firstPart.section(sep, 3);
	   classBaseMap[className] = baseName;
 	   ////cout <<"className: " << className << setw(16) << baseName << endl;
      }
   }

   map<QString, QString> derMap;
   //Now determine if the class has desc as a base class somewhere down the chain
   map<QString, QString>::iterator mI;// = classBaseMap.begin();
   for (mI = classBaseMap.begin(); mI != classBaseMap.end(); mI++) {
       QString cName = mI->first;
       QString bName = mI->second;
       QString bHold = bName;
       bool isDescClass = false;
       if (bName == "Desc") {
          ////cout <<cName <<" is derived from Desc at some Points"<<endl;
	  isDescClass = true;
	  derMap[cName] = bName;
       } 
       else {
          while (true) {
	     bName = classBaseMap[bName];
	     if (bName == "") {
		 ////cout <<cName <<" is not derived from Desc at any point"<<endl;
		 ////cout <<bName <<" is not derived from Desc"<<endl;
		 break;
	     }
	     if (bName == "Desc" ){
		////cout <<cName <<" is derived from Desc at some Points"<<endl;
		derMap[cName] = bHold;
		isDescClass = true;
		break;
	     }	
	  }
       }
   }

   map<QString, QListViewItem *> nameItemMap;
   //build the top level parents in the listView;
   QListView *list = dialog->listView;
   list->setSorting(-1);
   
   QListViewItem *parent;

//   parent = new QListViewItem(list, className);
   map<QString, QString>::iterator dI;// = derMap.begin();
   for (dI=derMap.begin(); dI != derMap.end(); dI++) {
      if (dI->second == "Desc") {
         parent = new QListViewItem(list, dI->first);
	 nameItemMap[dI->first] = parent;
      }
   }

   while (true) {
      //dI = derMap.begin();
      for (dI=derMap.begin(); dI != derMap.end(); dI++) {
         QString baseName = dI->second;
         if ( nameItemMap.find(baseName) != nameItemMap.end() ) {
	     parent = new QListViewItem(nameItemMap[dI->second], dI->first);
	     nameItemMap[dI->first] = parent;
         }
      }

      if (derMap.size() == nameItemMap.size()) 
	break;
   } 
   inFile.clear();
   inFile.close();
   inFile.open(Path.latin1(), ios::in);

   if (!inFile) {
	//cout <<"file not opened"<<endl;
	return;
   }
   bool isPrivate = true;
   QString className = "bad";
   while (true) {
     getline(inFile, line);
     QString qline = line;
     if (qline.contains("class") && qline.contains("extends") ){
        QRegExp sep( " +" );
	////cout << qline << endl;
        QString firstPart = qline.section("{", 0);
        ////cout <<"firstPart: " << firstPart << endl;
        QString tmpName = firstPart.section(sep, 1, 1);
	////cout <<"tmpName is: " << tmpName << endl;
        QString baseName = firstPart.section(sep, 3);
        isPrivate = false;
        if (nameItemMap.find(tmpName) != nameItemMap.end()) {
	   className = tmpName;
	   ////cout <<"className: " << className << endl;
        } else {
	   className = "bad";
	}
     } 
     else if (qline.contains("class") && !qline.contains("extends") ) {
	 className = "bad";
     }

     if (className != "bad") {
	////cout <<"className is: " << className << endl;
	if (qline.contains("private")) {
	   isPrivate = true;
	}

        if (qline.contains("function") && !isPrivate 
            && !qline.contains(className) && !qline.contains("static")) 
        {

	    bool endName = false;
            bool beginAuthor = false;
            string funcName;
            string author;

            QString tmp2 = qline.section("function ", 1);
            string tmp = tmp2.latin1();
            int authorCount = 0;
            for (unsigned int i=0; i<tmp.size(); i++) {
               if (tmp[i] == '(') {
                  endName = true;
               }
               if (!endName) {
                  funcName.push_back(tmp[i]);
               }
               if (beginAuthor) {
                  author.push_back(tmp[i]);
               }
               if (tmp[i] == '/') {
                 authorCount++;
                 if (authorCount == 2) {
                    beginAuthor = true;
                 }
              }
            }

            new QListViewItem(nameItemMap[className], funcName, author);
	}

     }
     if (inFile.eof()) 
     	break;  
   }
}


//void switchBoard::calcDesc(set<QString> &desc, dt::molecule *mol) {
void switchBoard::calcDesc(set<QString> &desc, dt::molPtr mol) {
  ////cout <<"You are in calcDesc"<<endl;
  /** This first section calculates some basic properties of each molecule
  *    It is usually going to be a good thing to type the molecules with the gaff types
  *    and calculate the rings etc.
  */
   dt::dType dt;
   dt.setPathLength(10);
   dt.setGaffTypes(mol);
   
   /** This map holds a list of top level clasess followed by either functions or other classes
   *   It parses input like  Constitutional:Counts:nCarbon
   *
   *   So on the first pass it is stored in the map like:
   *   descClasses["Constitutiona"] = "Counts:Carbon"
   * 
   *    Thus the string Counts:Carbon is passed to the class Counts
   */
   map<QString, set<QString> > descClasses;

   set<QString>::iterator si;// = desc.begin();
   for (si = desc.begin(); si != desc.end(); si++) {
      QString full = *si;
      ////cout <<"Full: " <<full << endl;
      QStringList clsFunc = QStringList::split(":", full);
      if (clsFunc.size() == 2)
         descClasses[clsFunc[0]].insert(clsFunc[1]);
   }

   ////cout <<"Now here This"<<endl;
   // Now in this section we loop through the map and call the appropriate classes 
   ////cout <<"Getting reading to loop through the map"<<endl;
   map<QString, set<QString> >::iterator mi;// = descClasses.begin();
   for (mi=descClasses.begin(); mi != descClasses.end(); mi++) {
      QString className = mi->first;
      ////cout <<"className "<< className << endl;
      if (classMap.find(className) != classMap.end()) {
          ////cout <<"Trying to call calcDesc on: " << className << endl;
         classMap[className]->calcDesc(mi->second, mol);
      }
   }
   
   ////cout <<"descClasses.size(): " << descClasses.size() << endl;
   
    
}

void switchBoard::descIn(set<QString> &desc) {
   ////cout <<"Hello from switchBoard::descIn"<<endl;
   
}

void switchBoard::dumbSlot() {

}


