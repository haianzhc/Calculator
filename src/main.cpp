#include <QApplication>

#include "QCalculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int ret = -1;

    QCalculator* cal = QCalculator::NewInstance();

    if(cal != NULL)
    {
        cal->show();
        ret =  a.exec();
        delete cal;
    }

    return ret;
//   QCalculatorDec c;
}
