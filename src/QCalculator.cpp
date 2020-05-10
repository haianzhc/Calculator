#include "QCalculator.h"

QCalculator::QCalculator()
{
}

bool QCalculator::constrcut()
{
    m_ui = QCalculatorUI::NewInstance();
    if(m_ui != NULL)
    {
         m_ui->setCalculator(&m_cal);
    }
    return (m_ui != NULL);
}

QCalculator* QCalculator::NewInstance()
{
    QCalculator* ret = new QCalculator;
    if((ret == NULL) || (!ret->constrcut()))
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

void QCalculator::show()
{
    m_ui->resize(200,280);
    m_ui->show();
}

QCalculator::~QCalculator()
{
    delete m_ui;
}
