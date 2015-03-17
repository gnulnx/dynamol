/********************************************************************************
** Form generated from reading ui file 'MainWindow.ui'
**
** Created: Sat Mar 1 08:55:52 2008
**      by: Qt User Interface Compiler version 4.3.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(563, 551);
    actionOpen = new QAction(MainWindow);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    actionClose = new QAction(MainWindow);
    actionClose->setObjectName(QString::fromUtf8("actionClose"));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    gridLayout = new QGridLayout(centralwidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    treeWidget = new QTreeWidget(centralwidget);
    treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
    treeWidget->setSizePolicy(sizePolicy);
    treeWidget->setMaximumSize(QSize(100, 16777215));

    gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

    tabWidget = new QTabWidget(centralwidget);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    tabWidget->addTab(tab_2, QString());

    gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 563, 29));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    statusbar->setMaximumSize(QSize(250, 16777215));
    MainWindow->setStatusBar(statusbar);
    toolBar = new QToolBar(MainWindow);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

    menubar->addAction(menuFile->menuAction());
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionClose);
    menuFile->addSeparator();

    retranslateUi(MainWindow);

    tabWidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
    actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
    treeWidget->headerItem()->setText(0, QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

#endif // UI_MAINWINDOW_H
