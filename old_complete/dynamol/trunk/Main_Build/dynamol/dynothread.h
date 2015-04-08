#ifndef DYNOTHREAD_H
#define DYNOTHREAD_H

#include <qthread.h>
#include <qwidget.h>
#include <qobject.h>
#include <qsemaphore.h>
#include <string>


using namespace std;
/**
@author jfurr
*/

class molView;


class dynoThread : public QWidget, public QThread {
Q_OBJECT
public:
    dynoThread(QWidget *parent);

    ~dynoThread();

    /** This return an identifier for the thread */
    virtual QString getName();
    int getNum();
    
    virtual void run();
    virtual void setName(QString name);
    
    virtual void stopThread();
    
    virtual int rtti();
    virtual void setSemaphore(QSemaphore *wait_sem);
    
    static void setMolView(molView *view);
  
    /** \brief Get Error Messages */
    string getErrorMsg();

    /** \brief Display Error propagated through the thread */
    void displayErrors();        
signals:
    void threadDone(dynoThread *);
    void threadDone();
    void threadStarted(dynoThread *);
    
    
protected:
    string errorMsg;

    QString name;
    int threadNum;
    static int count;
    bool stop;
    QSemaphore *wait_sem;
    
    static molView *viewer;
};

#endif





































