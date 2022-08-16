#include "macket.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

macket::macket(QString ID)
{
    m_ID = ID;


    setFlag(ItemIsSelectable);

// addReservation( strtus=0 , price=0, seatNumber, Route_Id, user_Id, QDateTime::currentDateTime()  )

}

QRectF macket::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void macket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush  brush(Qt::blue);



    if(pressed)
    {
        brush.setColor(Qt::red);

    }
    else
    {
        brush.setColor(Qt::green);
    }



    painter->fillRect(rec,brush);

    painter->drawRect(rec);

}

bool macket::getPressed() const
{
    return pressed;
}

void macket::setPressed(bool newPressed)
{
    pressed = newPressed;
}

void macket::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (locked == true)
    {
        QGraphicsItem::mousePressEvent(event);
        return;
    }
    update();

        pressed = !pressed;

    QGraphicsItem::mousePressEvent(event);

   emit carre_clicked(m_ID, pressed);

}

bool macket::getLocked() const
{
    return locked;
}

void macket::setLocked(bool newLocked)
{
    pressed = newLocked;
    locked = newLocked;
}

/*
void macket::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);

}
*/
