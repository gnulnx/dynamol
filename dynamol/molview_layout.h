/********************************************************************************
** Form generated from reading ui file 'testview.ui'
**
** Created: Mon Jan 28 10:28:54 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TESTVIEW_H
#define UI_TESTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

#include "molview.h"
#include "scriptengine.h"

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QWidget *widget;

    void setupUi(QWidget *Form)
    {
    if (Form->objectName().isEmpty())
        Form->setObjectName(QString::fromUtf8("Form"));
    QSize size(407, 306);
    size = size.expandedTo(Form->minimumSizeHint());
    Form->resize(size);
    QPalette palette;
    QBrush brush(QColor(255, 255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    QBrush brush1(QColor(0, 0, 0, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Button, brush1);
    palette.setBrush(QPalette::Active, QPalette::Light, brush1);
    palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
    palette.setBrush(QPalette::Active, QPalette::Dark, brush1);
    palette.setBrush(QPalette::Active, QPalette::Mid, brush1);
    palette.setBrush(QPalette::Active, QPalette::Text, brush);
    palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Active, QPalette::Base, brush1);
    palette.setBrush(QPalette::Active, QPalette::Window, brush1);
    palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
    palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
    Form->setPalette(palette);
    gridLayout = new QGridLayout(Form);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label = new QLabel(Form);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout->addWidget(label);

    //lineEdit = new QLineEdit(Form);
	//You Changed Here
	lineEdit = new dynamol::ScriptEngine(Form);
	
    //lineEdit->setStyleSheet("color:black;" "frame:true;" "border->radius: 10px;");
    lineEdit->setStyleSheet(
     "border: 2px solid #0066FF;"
     "border-radius: 10px;"
     "padding: 0 8px;"
     "background: black;"
     "color: #99FFFF;"
     "selection-background-color: darkgray;"
 );
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
    lineEdit->setSizePolicy(sizePolicy);
	
    hboxLayout->addWidget(lineEdit);
	lineEdit->setFrame(true);
    gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

	//You Changed Here
	widget = new dynamol::molView(Form);

    widget->setObjectName(QString::fromUtf8("widget"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
    widget->setSizePolicy(sizePolicy1);
    QPalette palette1;
    palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
    QBrush brush2(QColor(255, 170, 0, 255));
    brush2.setStyle(Qt::SolidPattern);
    palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
    palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
    palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
    palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
    palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
    widget->setPalette(palette1);
    widget->setAutoFillBackground(true);

    gridLayout->addWidget(widget, 0, 0, 1, 1);


    retranslateUi(Form);

    QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
    Form->setWindowTitle(QApplication::translate("Form", "Dynamol V2", 0));
    label->setText(QApplication::translate("Form", "DynPy>", 0));
    label->setStyleSheet("color: #99FFFF;");
	Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

#endif // UI_TESTVIEW_H
