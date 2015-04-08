/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef TABLEEXPORT_H
#define TABLEEXPORT_H

#include <qobject.h>
#include <qstring.h>

/**
@author jfurr
*/

class Table;
class QTable;
class tableExport : public QObject
{
Q_OBJECT
public:
    tableExport(Table *table, QObject *parent = 0, const char *name = 0);
    
    tableExport(QTable *table, QObject *parent = 0, const char *name = 0);

    ~tableExport();

    /** This function is called ot export entries in the table
    *   It returns true if the export was succesful and false if not
    */
    bool exportSD(QString fileName, int row, int col);
    
    /** This funcion is called to export the table as text
    *   It returns true if the export succeeds and flaes otherwise
    */
    bool exportText(QString fileName, QString delim, int row, int col);
private:
    QTable *molTable;
    Table *table;

    /** This function exports all the molecules with all the properties */
    bool exportAll(QString fileName, int row, int col);
};

#endif






