#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

#include <QMessageBox>

#include <QMainWindow>
#include <QTabWidget>
#include <QDataWidgetMapper>
#include <QObject>
#include <QString>
#include <QStringListModel>
#include <QTableWidget>
#include "QVector"
#include "QList"
#include "QCheckBox"
#include "../HttpClient/client.h"
#include "ticket.h"
#include "tool.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void listdepartureAndArrivalAirport();
    void searchInReservations(QString _firstname_res ="", QString _lastname ="", QString _email ="");

    int getCurrent_row() const;
    void setCurrent_row(int newCurrent_row);

private slots:
    void InfoFlight(int r);
    void setListeOfAvailableFlight();
    void clearTable();
    void on_pbConfirmeAndBook_clicked();
    void deleteFlight();
    void displayReservations();
    void setupResSearch();
    void deleteRes();
    void generateTicket();
    void setRowFlightTable();


//void setListeOfAvailableFlight();
//void clearTable();

//void on_pbConfirmeAndBook_clicked();

//void deleteFlight();


void Add_Usert();

signals:


private:
    Ui::MainWindow *ui;


    QTabWidget *tabWidgetAPP;
    QStringListModel *model;
    Client* mClient;
    QJsonObject mReservationsData;
    QMap<QString, QString> mSearchRes;
    Ticket* mTicket;


    int current_row;
    int m_Actual_Avion_Id;
    bool selected_flight;
    bool addUserVerif;
    //QMessageBox






};
#endif // MAINWINDOW_H
