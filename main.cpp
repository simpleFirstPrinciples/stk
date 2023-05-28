#include "stk.h"
#include <QtWidgets/QApplication>

#include "QmitkRegisterClasses.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QmitkRegisterClasses();


    stk w;
    w.show();
    return a.exec();
}
