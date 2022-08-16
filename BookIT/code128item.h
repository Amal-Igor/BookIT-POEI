#ifndef CODE128ITEM_H
#define CODE128ITEM_H

#include <QGraphicsItem>
#include "code128.h"

class Code128Item : public QGraphicsItem
{
    bool m_TextVisible, m_Rotate;
    float m_Width;
    float m_Height;
    QString m_Text;
    Code128::BarCode m_Code;
    int m_CodeLength;
    bool m_HighDPI;
    int m_xPos;
    int m_yPos;

public:
    Code128Item();
    void setText ( const QString & text );
    void setPosition(int _x, int _y);
    void setWidth( float width );
    void setHeight( float height );
    void setTextVisible( bool visible );
    void setHighDPI(bool highDPI);
    void setRotate(bool _rotate);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * widget);
};
#endif // CODE128ITEM_H
