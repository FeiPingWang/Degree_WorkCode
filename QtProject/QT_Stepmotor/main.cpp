#include <QtGui/QApplication>
#include "stepmotor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StepMotor w;
    w.show();
    
    return a.exec();
}
