#include "QCalculatorUI.h"
#include "QCalculatorDec.h"
//#include <QDebug>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>

QCalculatorUI::QCalculatorUI() :QWidget(NULL,Qt::WindowCloseButtonHint)
{
    m_cal = NULL;
}

bool QCalculatorUI::construct()
{
     bool ret = true;
     m_edit = new QLineEdit(this);

     const QString btnText[20] = {
         "7","8","9","+","(",
         "4","5","6","-",")",
         "1","2","3","*","<-",
         "0",".","=","/","C"
     };

     if(m_edit != NULL)
     {
         //m_edit->move(10,10);
         m_edit->setMinimumSize(240,30);
         m_edit->setReadOnly(true);
         m_edit->setAlignment(Qt::AlignRight);
         //qDebug() << m_edit;
     }
     else
     {
        ret = false;
     }

     for(int i = 0;(i < 4) && ret;i++)
     {
         for(int j = 0;(j < 5) && ret;j++)
         {
             m_buttons[i * 5 + j] = new QPushButton(this);

             if(m_buttons[i * 5 + j] != NULL)
             {
                m_buttons[i * 5 + j]->setMinimumSize(40,40);
                m_buttons[i * 5 + j]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
                m_buttons[i * 5 + j]->setText(btnText[i * 5 + j]);
                //qDebug() <<  m_buttons[i * 5 + j]->text();
                connect(m_buttons[i * 5 + j],SIGNAL(clicked()),this,SLOT(onButtonClicked()));
             }
             else
             {
                ret = false;
             }
         }
     }
     return ret;
}

QCalculatorUI* QCalculatorUI::NewInstance()
{
    QCalculatorUI* ret = new QCalculatorUI();
    if((ret == NULL)||(!ret->construct()))
    {
        delete ret;
        ret = NULL;
    }
    ret->layout();
    return ret;
}


void QCalculatorUI::show()
{
    QWidget::show();
    //setFixedSize(width(),height());
}

void QCalculatorUI::onButtonClicked()
{
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    if(btn != NULL)
    {
        QString clickText = btn->text();
        if(clickText == "<-")
        {
            QString text = m_edit->text();

            if(text.length() > 0)
            {
                m_edit->setText(text.remove(text.length() - 1,1));
            }
        }
        else if(clickText == "C")
        {
            m_edit->setText("");
        }
        else if(clickText == "=")
        {
            if(m_edit != NULL)
            {
                m_cal->expression(m_edit->text());
                m_edit->setText(m_cal->result());
            }
        }
        else
        {
            m_edit->setText(m_edit->text() + clickText);
        }
    }
    //QString text = m_edit->text() + btn->text();
    //m_edit->setText(text);
    //qDebug() << "onButtonClicked()";
    //qDebug() << btn->text();
}

void QCalculatorUI::layout()
{
    QHBoxLayout* m_hlayout[5];
    QVBoxLayout* m_vlayout = new QVBoxLayout();
    m_vlayout->setSpacing(10);
    for(int i = 0;i < 5;i++)
    {
        m_hlayout[i] = new QHBoxLayout();
        m_hlayout[i]->setSpacing(10);
        if(i == 0)
        {
            m_hlayout[i]->addWidget(m_edit);
        }
        else
        {
            m_hlayout[i]->addWidget(m_buttons[(i - 1) * 5 + 0]);
            m_hlayout[i]->addWidget(m_buttons[(i - 1) * 5 + 1]);
            m_hlayout[i]->addWidget(m_buttons[(i - 1) * 5 + 2]);
            m_hlayout[i]->addWidget(m_buttons[(i - 1) * 5 + 3]);
            m_hlayout[i]->addWidget(m_buttons[(i - 1) * 5 + 4]);
        }
    }
    m_vlayout->addLayout(m_hlayout[0]);
    m_vlayout->addLayout(m_hlayout[1]);
    m_vlayout->addLayout(m_hlayout[2]);
    m_vlayout->addLayout(m_hlayout[3]);
    m_vlayout->addLayout(m_hlayout[4]);
    //m_vlayout->addLayout(m_hlayout[5]);
    setLayout(m_vlayout);
}

void QCalculatorUI::setCalculator(ICalculator* cal)
{
    m_cal = cal;
}

ICalculator* QCalculatorUI::getCalculator()
{
    return m_cal;
}

QCalculatorUI::~QCalculatorUI()
{

}

