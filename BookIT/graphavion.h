#ifndef GRAPHAVION_H
#define GRAPHAVION_H

#include <QGraphicsView>
#include <QDialog>

#include "../HttpClient/client.h"



#include <QDialog>
#include <QtCore>
#include <QtGui>
#include "macket.h"
#include <QLineEdit>
#include "tool.h"

class GraphAvion : public QDialog
{
    Q_OBJECT

public:
    explicit GraphAvion(QWidget *parent = nullptr);
    void createGraph(int r, int c, QStringList v, int m_Actual_Avion_Id );

    void sendSeatConfirmation();

    const QString &seat() const;
    void setSeat(const QString &newSeat);

signals:

private:
    QGraphicsScene *scene = nullptr;
    QVector<macket * > v;
    macket *car;
    QGraphicsView* view;
    QPushButton  * pbConfirm;
  //  QLineEdit *leInfo;
    Tool* t;

    QString m_seat;

    int received_ID;


signals:
  void seatConfirmed(QString seat);



protected slots:
    void carre_is_clicked(QString, bool);

private slots:
    void closeWindow();




    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // GRAPHAVION_H
