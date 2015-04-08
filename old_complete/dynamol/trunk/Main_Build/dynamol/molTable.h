/****************************************************************************
** Form interface generated from reading ui file 'molTable.ui'
**
** Created: Fri Aug 5 12:34:01 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MOLTABLE_H
#define MOLTABLE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qmainwindow.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QTable;
class QToolButton;

class molTable : public QMainWindow
{
    Q_OBJECT

public:
    molTable( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~molTable();

    QTable* table1;
    QToolButton* toolButton1;
    QToolButton* toolButton3;
    QMenuBar *MenuBar;
    QPopupMenu *fileMenu;
    QPopupMenu *popupMenu_2;
    QPopupMenu *editMenu;
    QPopupMenu *View;
    QPopupMenu *Calculate;
    QToolBar *toolBar;
    QToolBar *Toolbar;
    QAction* fileNewAction;
    QAction* fileOpenAction;
    QAction* fileSaveAction;
    QAction* fileSaveAsAction;
    QAction* filePrintAction;
    QAction* fileExitAction;
    QAction* editUndoAction;
    QAction* editRedoAction;
    QAction* editCutAction;
    QAction* editCopyAction;
    QAction* editPasteAction;
    QAction* editFindAction;
    QAction* helpContentsAction;
    QAction* helpIndexAction;
    QAction* helpAboutAction;
    QAction* calculateDescriptorsAction;
    QAction* filetestAction;
    QAction* viewselectedAction;
    QAction* viewunselectedAction;
    QAction* fileExportAction;
    QAction* fileExportSDFAction;
    QAction* fileExporttextAction;
    QAction* calculateFingerPrintsAction;
    QAction* calculateFingerPrintsgaffFPAction;
    QAction* viewNextAction;
    QAction* viewPrevAction;

public slots:
    virtual void fileNew();
    virtual void fileOpen();
    virtual void fileSave();
    virtual void fileSaveAs();
    virtual void filePrint();
    virtual void fileExit();
    virtual void editUndo();
    virtual void editRedo();
    virtual void editCut();
    virtual void editCopy();
    virtual void editPaste();
    virtual void editFind();
    virtual void helpIndex();
    virtual void helpContents();
    virtual void helpAbout();
    virtual void molTable_toolBarPositionChanged( QToolBar * );
    virtual void fileOpenAction_2_activated();
    virtual void SDExportSlot();
    virtual void textExportSlot();
    virtual void calculateFingerPrintsgaffFPAction_activated();
    virtual void showPrevSlot();
    virtual void showNextSlot();

signals:
    void openFile();
    void sdExportSignal(QString, int, int);
    void textExportSignal(QString, QString, int, int);
    void gaffFPSignal();
    void showSelectedSignal();
    void clearListView();

protected:
    QGridLayout* molTableLayout;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;
    QPixmap image6;
    QPixmap image7;
    QPixmap image8;
    QPixmap image9;
    QPixmap image10;
    QPixmap image11;
    QPixmap image12;

};

#endif // MOLTABLE_H






