
#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

#include <qmainwindow.h>

class QTextEdit;

class descriptors: public QMainWindow
{
    Q_OBJECT

public:
    descriptors();
    ~descriptors();

protected:
    void closeEvent( QCloseEvent* );

private slots:
    void newDoc();
    void choose();
    void load( const QString &fileName );
    void save();
    void saveAs();
    void print();

    void about();
    void aboutQt();

private:
    QPrinter *printer;
    QTextEdit *e;
    QString filename;
};


#endif



