/****************************************************************************
** Form interface generated from reading ui file 'hits.ui'
**
** Created: Mon Oct 17 13:19:31 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef HITSDIALOG_H
#define HITSDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <map>
#include <set>
#include <vector>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTable;

class hitsDialog : public QDialog
{
    Q_OBJECT

public:
    hitsDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~hitsDialog();

    QPushButton* save;
    QPushButton* buttonCancel;
    QTable* table1;

public slots:
    virtual void saveSlot();
    virtual void buildTable( std::vector<std::pair<QString, float> > & hitVec, std::set<QString> & actives, std::set<QString> & act_and_test, int maxResults );

protected:
    QGridLayout* hitsDialogLayout;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

};

#endif // HITSDIALOG_H

