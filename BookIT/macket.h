#ifndef MACKET_H
#define MACKET_H

#include <QPainter>
#include <QGraphicsObject>
#include <QDebug>
#include <QDialog>




class macket : public QGraphicsObject
{
    Q_OBJECT
public:
    macket(QString ID);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);




    bool getPressed() const;
    void setPressed(bool newPressed);

    bool getLocked() const;
    void setLocked(bool newLocked);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
  //  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:
    QPushButton *p;
    QString m_ID;
    bool pressed = false;
    bool locked = false;

signals:
  void carre_clicked(QString, bool);


};


#endif // MACKET_H
