
#include <qapplication.h>
#include "descriptors.h"

int main( int argc, char ** argv ) {
    QApplication a( argc, argv );
    descriptors * mw = new descriptors();
    mw->setCaption( "descriptors" );
    mw->show();
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    return a.exec();
}



