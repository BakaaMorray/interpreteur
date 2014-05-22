#include <QApplication>
#include "interprete.h"

int main(int argc, char * argv[])
{
    QApplication app(argc,argv);
    interprete w(argc,argv);
    w.show();

    return app.exec();
}

