#include "graphavion.h"


#include <QHBoxLayout>
#include <QPushButton>

GraphAvion::GraphAvion(QWidget *parent)   : QDialog{parent}
{

    QVBoxLayout* lay = new QVBoxLayout(this);
    setLayout(lay);


     pbConfirm = new QPushButton("Confirm and quit");
   //  leInfo = new QLineEdit;

         connect(pbConfirm, SIGNAL(clicked(bool)), this, SLOT(closeWindow()) );

    view = new QGraphicsView(this);
    lay->addWidget(view);
   // lay->addWidget(pbConfirm,Qt::AlignVCenter  );


    lay->addWidget(pbConfirm, Qt::AlignBaseline );
  //  lay->addWidget(leInfo);



setMinimumSize(500,500);




}

void GraphAvion::sendSeatConfirmation()
{
    this->setSeat(m_seat);

//    qDebug() << "On est la " <<  m_seat;
}

const QString &GraphAvion::seat() const
{
    return m_seat;
}

void GraphAvion::setSeat(const QString &newSeat)
{
    m_seat = newSeat;
}

void GraphAvion::closeWindow()
{
    sendSeatConfirmation();
    done(0);
}

void GraphAvion::resizeEvent(QResizeEvent *event)
{
    view->fitInView(QRect(0,0,300,500),Qt::KeepAspectRatio);

    QWidget::resizeEvent(event);
}
void GraphAvion::createGraph(int r, int c, QStringList v, int m_Actual_Avion_Id )
{
    received_ID = m_Actual_Avion_Id;
    if (scene != nullptr)
        delete scene;


    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,300,1900);



  view->setScene(scene);

    int row(r);
    int col(c);
    int p=0;
    int k=0;
    //char l=0;
    QString numSiege; // = "a";

    for(int i=1; i<= row; i++){
        for(int j=1; j<= col; j++){



            char l = static_cast<char>(j-1) + 'A';


            if( i<10){
                QString c = QString::number(i);
                numSiege = '0' + c + l; // + l;
            }
            else
            {
                QString c = QString::number(i);
                 numSiege = c+ l;
            }


            car = new macket(numSiege);
            if (v.indexOf(numSiege) != -1)
                car->setLocked(true);

            connect(car,SIGNAL(carre_clicked(QString, bool)), this, SLOT(carre_is_clicked(QString, bool)));

            car->setPos(i+k,j+p);

            if( j == col/3 || (col-j) == col/3  )
            p+=35;
            else
                p+=25;

            scene->addItem(car);
        }
        if (i == row/3 || (row -i) == row/3)
            k+=35;
        else
            k+=25;
        p = 0;
    }
    scene->addItem(car);
    view->fitInView(QRect(0,0,300,500),Qt::KeepAspectRatio);
    update();
}





void GraphAvion::carre_is_clicked(QString s, bool b)
{

   m_seat = s;
  qDebug() << s << b;

}
