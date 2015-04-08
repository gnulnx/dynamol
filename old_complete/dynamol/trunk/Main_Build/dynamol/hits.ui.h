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

#include <qfiledialog.h>
#include <qstring.h>
#include <fstream>
#include <qmessagebox.h>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <qpainter.h>
#include "tableexporter.h"
using namespace std;


class TextItem : public QTableItem
{
public:
 TextItem( QTable *t) : QTableItem(t,OnTyping) {}
 void paint(QPainter * p, const QColorGroup & cg, const QRect & cr, bool 
selected) {
 QColorGroup cg1(cg);
 //if (text()!=svText) {
  cg1.setColor(QColorGroup::Base,gray);  
  cg1.setColor(QColorGroup::Text,black);
  cg1.setColor(QColorGroup::HighlightedText,white);
 //}
 QTableItem::paint(p,cg1,cr,selected);
}
  void setFirstText(const QString &str) { QTableItem::setText(saveText=str); }

protected:
 QString saveText;
};


class TextItem2 : public QTableItem
{
public:
        TextItem2( QTable *t) : QTableItem(t,OnTyping) {}
        void paint(QPainter * p, const QColorGroup & cg, const QRect & cr, bool
selected) {
        QColorGroup cg1(cg);
        //if (text()!=svText) {
                cg1.setColor(QColorGroup::Base,green);
                cg1.setColor(QColorGroup::Text,black);
                cg1.setColor(QColorGroup::HighlightedText,white);
        //}
        QTableItem::paint(p,cg1,cr,selected);
}
         void setFirstText(const QString &str) { QTableItem::setText(saveText=str); }

protected:
        QString saveText;
};


class hitsItem : public QTableItem
{
public:
        hitsItem( QTable *t) : QTableItem(t,OnTyping) {}
        void paint(QPainter * p, const QColorGroup & cg, const QRect & cr, bool
selected) {
        QColorGroup cg1(cg);
        //if (text()!=svText) {
                cg1.setColor(QColorGroup::Base,yellow);
                cg1.setColor(QColorGroup::Text,black);
                cg1.setColor(QColorGroup::HighlightedText,white);
        //}
        QTableItem::paint(p,cg1,cr,selected);
}
         void setFirstText(const QString &str) { QTableItem::setText(saveText=str); }

protected:
        QString saveText;
};


void hitsDialog::saveSlot()
{
    
    QString fileName = QFileDialog::getSaveFileName(
                    "./",
                    "FingerPrints (*.fp)",
                    this,
                    "open file dialog",                    "Choose a file" );
 
   tableExport *exporter = new tableExport(table1, NULL, NULL);
   QString delim = "\t";
   exporter->exportText(fileName, delim, 0, 0);
   delete exporter;


}

void hitsDialog::buildTable( std::vector< std::pair<QString, float> > &hitVec, std::set<QString> &actives, std::set<QString> &act_and_test, int maxResults )
{
   ////cout <<"You are in buildTable" << endl;
   table1->insertRows(0, maxResults );
   QPainter *p = new QPainter(table1);
   p->setBackgroundColor(Qt::blue);
    QColorGroup g;
   if (maxResults > hitVec.size() )
      maxResults = hitVec.size()-1;

   //for (int i=0; i<hitVec.size(); i++) {
    for (int i=0; i<maxResults; i++) {
       //IF AN ACTIVE COMPOUND
       if (actives.find(hitVec[i].first) != actives.end()) {
          TextItem *ti1=new TextItem(table1);
          table1->setItem(i, 0, ti1);
          ti1->setFirstText(hitVec[i].first);
       
          //table1->setText(i, 0, hitVec[i].first);
          QString sec; sec.setNum(hitVec[i].second);
          TextItem *ti2=new TextItem(table1);
          table1->setItem(i,1,ti2);
          //ti2->setFirstText("TRAIN");
          ti2->setFirstText(sec);
       } else if (act_and_test.find(hitVec[i].first) != act_and_test.end()) {
          TextItem2 *ti1=new TextItem2(table1);
          table1->setItem(i, 0, ti1);
          ti1->setFirstText(hitVec[i].first);

          //table1->setText(i, 0, hitVec[i].first);
          QString sec; sec.setNum(hitVec[i].second);
          TextItem2 *ti2=new TextItem2(table1);
          table1->setItem(i,1,ti2);
          //ti2->setFirstText("TEST");
          ti2->setFirstText(sec);
       }
       else {
         hitsItem *ti1=new hitsItem(table1);
         table1->setItem(i, 0, ti1);
         ti1->setFirstText(hitVec[i].first);

         //table1->setText(i, 0, hitVec[i].first);
         QString sec; sec.setNum(hitVec[i].second);
         hitsItem *ti2=new hitsItem(table1);
         table1->setItem(i,1,ti2);
         //ti2->setFirstText("HIT");
         ti2->setFirstText(sec);



    //      table1->setText(i, 0, hitVec[i].first);
  //        QString sec; sec.setNum(hitVec[i].second);
//          table1->setText(i, 1, sec);
       }
       g.setColor( QColorGroup::Base, red );
       g.setColor ( QColorGroup::Background, blue);
       QRect rect = table1->cellGeometry ( i, 0);
       table1->paintCell( p, i, 0, rect, true, g );
       table1->paintCell( p, i, 1, rect, true, g );
       //QTable::paintCell ( QPainter * p, int row, int col, const QRect & cr, bool selected, const QColorGroup & cg )
   }

}





