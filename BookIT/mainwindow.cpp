#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "users.h"
#include <QJsonObject>
#include "graphavion.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addUserVerif = false;

    mTicket = new Ticket("../tickets/");

    m_Actual_Avion_Id = -1;

    mClient = new Client();
    listdepartureAndArrivalAirport();

     tabWidgetAPP = new QTabWidget;


    connect(ui->pbSearch, SIGNAL(clicked(bool)),this , SLOT(setListeOfAvailableFlight()));
    connect(ui->pbNewResearch, SIGNAL(clicked(bool)),this , SLOT(clearTable()));

    connect(ui->pbValidate, SIGNAL(clicked(bool)), this, SLOT(Add_Usert()));

    connect(ui->tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(InfoFlight(int)));

    connect(ui->pbTicket_res, SIGNAL(clicked(bool)), this, SLOT(generateTicket()));


    // Resizing table header make it spread all within the winows
    ui->tableWReservation_->horizontalHeader()->setStretchLastSection(true);
    ui->tableWReservation_->verticalHeader()->setVisible(false);



    //Connecting tab widget to Hydrate resrvation page
    ui->tabWidgetAPP->setCurrentIndex(0);
    connect(ui->tabWidgetAPP, SIGNAL(currentChanged(int)), this, SLOT(displayReservations()));
    connect(ui->pbReset_res, SIGNAL(clicked(bool)), this, SLOT(displayReservations()));
    connect(ui->pbSearchRes, SIGNAL(clicked(bool)), this, SLOT(setupResSearch()));
    connect(ui->tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(setRowFlightTable()));

    ui->tabWidgetAPP->setCurrentIndex(0);

}


void MainWindow::InfoFlight(int r)
{
    /*
     * Cette fonction retourne les information sur le vol selectionné dans le UI
     */


    QString text = ui->tableWidget->item(r,6)->text();
    m_Actual_Avion_Id = text.toInt();
    selected_flight = true;

}

void MainWindow::clearTable()
{
    ui->tableWidget->clearContents();
}



void MainWindow::setListeOfAvailableFlight()
{
    /*
     * Cette fonction affiche les vols disponible en fonction du choix de
     * l'utilisateur.
     */

    ui->tableWidget->clearContents();


        QDateTime date;

        date.setDate(ui->dateTimeEdit->date());
        date.setTime(ui->dateTimeEdit->time());

        QJsonObject ob;
        ob =  mClient->getRoutesBetweenAirports(ui->cbDeparture->currentText().right(3),ui->cbArrival->currentText().right(3),date);
        qDebug() << "hhhhhhhhhhhhhhhhhhhhhhhhhh"  << ob;



        QStringList keys =  ob.keys();

    int cpt=0;
    foreach( QString key, keys )
    {


       if( ob[key].toObject()["departure_airport"].toString() == ui->cbDeparture->currentText().right(3)  &&
               ob[key].toObject()["arrival_airport"].toString() == ui->cbArrival->currentText().right(3)  )
       {
            /*
            *
            * Ici il nous manque && ui->( dateTimeEdit->  ) verification de la date choisit,
            *  A DISCUTER SUR LE FORMAT
            *
            */


           QJsonObject info = mClient->getRoute(ob[key].toObject()["route_id"].toInt() );

           qDebug() << info;


            ui->tableWidget->insertRow(cpt);

            QTableWidgetItem *Dep = new QTableWidgetItem(ob[key].toObject()["departure_airport"].toString());
            QTableWidgetItem *Arr = new QTableWidgetItem(ob[key].toObject()["arrival_airport"].toString());
            QTableWidgetItem *DepTime = new QTableWidgetItem(tr("%1").arg( ob[key].toObject()["departure_time"].toString() ));

            QTableWidgetItem *ArrivTime = new QTableWidgetItem(tr("%1").arg( ob[key].toObject()["departure_time"].toString()));

            QTableWidgetItem *flight_id = new QTableWidgetItem(tr("%1").arg(ob[key].toObject()["flight_id"].toInt()));
             QTableWidgetItem *Route_id = new QTableWidgetItem(tr("%1").arg(ob[key].toObject()["route_id"].toInt()));


            ui->tableWidget->setItem(cpt,1,Dep);
            ui->tableWidget->setItem(cpt,2,Arr);
            ui->tableWidget->setItem(cpt,3,DepTime);
            ui->tableWidget->setItem(cpt,4,ArrivTime);
            ui->tableWidget->setItem(cpt,5,flight_id);
            ui->tableWidget->setItem(cpt,6,Route_id);

        cpt++;
       }



    }

        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);

}




void MainWindow::listdepartureAndArrivalAirport()
{

/*
 *
 * Cette fonction affiche dans les ComboBox les listes des Airoport de dappart et d'arriver dès
 * que l'objet Client() est instancier dans le constructeur.
 *
 */


    ui->cbDeparture->clear();
    ui->cbArrival->clear();

    ui->tableWidget->clearContents();


    QJsonObject ob;


    ob = mClient ->getAllAirports();


    QStringList keys =  ob.keys();

    QStringList departure;
    QStringList arrival;

    foreach( QString key, keys )
    {

       departure << ob[key].toObject()["airport_name"].toString() + ", " +  ob[key].toObject()["airport_code"].toString();
       arrival  << ob[key].toObject()["airport_name"].toString()  + ", " + ob[key].toObject()["airport_code"].toString();

    }

    QStringListModel *model1 = new QStringListModel();
    QStringListModel *model2 = new QStringListModel();
    model1->setStringList(departure);
    model2->setStringList(arrival);
    ui->cbDeparture->setModel(model1);
    ui->cbArrival->setModel(model2);

}



void MainWindow::searchInReservations(QString _firstname_res, QString _lastname, QString _email)
{
    QJsonObject obj = mClient->getAllReservations();
    ui->tableWReservation_->clearContents();
    QStringList keys =  obj.keys();

  //  QString dep;

    int cpt=0;
    //ui->tableWReservation_->setColumnCount(7);
    foreach( QString key, keys )
    {
            ui->tableWReservation_->insertRow(cpt);
         if(_firstname_res.toLower() == (obj[key].toObject()["firstname"].toString()).toLower() || _lastname.toLower() == (obj[key].toObject()["lastname"].toString()).toLower())


         {
            QTableWidgetItem *arrAir_res = new QTableWidgetItem(obj[key].toObject()["arrival_airport"].toString());
            QTableWidgetItem *depAir_res = new QTableWidgetItem(obj[key].toObject()["departure_airport"].toString());
            QTableWidgetItem *lastName_res = new QTableWidgetItem(obj[key].toObject()["lastname"].toString());
            QTableWidgetItem *firstname_res = new QTableWidgetItem(obj[key].toObject()["firstname"].toString());
            QTableWidgetItem *departure_time_res = new QTableWidgetItem(obj[key].toObject()["departure_time"].toString());
            QTableWidgetItem *route_id_res = new QTableWidgetItem(QString::number(obj[key].toObject()["route_id"].toInt()));
            QTableWidgetItem *reservation_id_res = new QTableWidgetItem(QString::number(obj[key].toObject()["reservation_id"].toInt()));

            ui->tableWReservation_->setItem(cpt,0,reservation_id_res);
            ui->tableWReservation_->setItem(cpt,1,firstname_res);
            ui->tableWReservation_->setItem(cpt,2,lastName_res);
            ui->tableWReservation_->setItem(cpt,3,departure_time_res);
            ui->tableWReservation_->setItem(cpt,4,depAir_res);
            ui->tableWReservation_->setItem(cpt,5,arrAir_res);
            ui->tableWReservation_->setItem(cpt,6,route_id_res);
            cpt++;
         }


    }
}



//void MainWindow::fillLastname()
//{
//    mSearchRes.insert("lastname", )
//}



void MainWindow::displayReservations()
{
    QJsonObject obj = mClient->getAllReservations();
    ui->tableWReservation_->setRowCount(0);
//    qDebug() << mReservationsData;

      ui->tableWReservation_->clearContents();
//    QJsonObject ob;
//    ob = mClient ->getAllRoutes();

    QStringList keys =  obj.keys();

  //  QString dep;

    int cpt=0;

    //ui->tableWReservation_->setColumnCount(7);
    foreach( QString key, keys )
    {
            ui->tableWReservation_->insertRow(cpt);

            QTableWidgetItem *arrAir_res = new QTableWidgetItem(obj[key].toObject()["arrival_airport"].toString());
            QTableWidgetItem *depAir_res = new QTableWidgetItem(obj[key].toObject()["departure_airport"].toString());
            QTableWidgetItem *lastName_res = new QTableWidgetItem(obj[key].toObject()["lastname"].toString());
            QTableWidgetItem *firstname_res = new QTableWidgetItem(obj[key].toObject()["firstname"].toString());
            QTableWidgetItem *departure_time_res = new QTableWidgetItem(obj[key].toObject()["departure_time"].toString());
            QTableWidgetItem *route_id_res = new QTableWidgetItem(QString::number(obj[key].toObject()["route_id"].toInt()));
            QTableWidgetItem *reservation_id_res = new QTableWidgetItem(QString::number(obj[key].toObject()["reservation_id"].toInt()));



            ui->tableWReservation_->setItem(cpt,0,reservation_id_res);
            ui->tableWReservation_->setItem(cpt,1,firstname_res);
            ui->tableWReservation_->setItem(cpt,2,lastName_res);
            ui->tableWReservation_->setItem(cpt,3,departure_time_res);
            ui->tableWReservation_->setItem(cpt,4,depAir_res);
            ui->tableWReservation_->setItem(cpt,5,arrAir_res);
            ui->tableWReservation_->setItem(cpt,6,route_id_res);

        cpt++;
    }



    ui->tableWReservation_->setSelectionBehavior(QAbstractItemView::SelectRows);

}

void MainWindow::setupResSearch()
{
     ui->tableWReservation_->clearContents();
     ui->tableWReservation_->setRowCount(0);
     QString lastname =  ui->leLastname_res->text();
     QString firstname = ui->leFirstname_res->text();
     searchInReservations(firstname, lastname);
}

void MainWindow::deleteRes()
{
    int res_id = ui->tableWReservation_->item(ui->tableWReservation_->currentRow(),0)->text().toInt();

     qDebug() << mClient->deleteReservation(res_id);

}

void MainWindow::generateTicket()
{
    int res_id = ui->tableWReservation_->item(ui->tableWReservation_->currentRow(),0)->text().toInt();
    QJsonObject objClient  = mClient->getReservation(res_id);
    QString name = ui->tableWReservation_->item(ui->tableWReservation_->currentRow(),1)->text() + " " + ui->tableWReservation_->item(ui->tableWReservation_->currentRow(),2)->text() ;
    qDebug() << name;
    QString seat_num =  objClient["seat_num"].toString();
    QString date_of_reservation = objClient["date_of_reservation"].toString();

    QDateTime date_dep = date_dep.fromString(date_of_reservation, "yyyy-MM-dd hh:mm:ss");


    QJsonObject objRoute = mClient->getAllInfosOnRoute(objClient["route_id"].toInt());
    QString arrival = objRoute["route_infos"].toObject()["arrival_airport"].toString();
    QString departure = objRoute["route_infos"].toObject()["departure_airport"].toString();
    //QString departure = objRoute["route_infos"].toObject()["departure"].toString();
    int flight_id = objRoute["route_infos"].toObject()["flight_id"].toInt();
    mTicket->writeData(res_id, name, seat_num, departure, arrival, flight_id, date_dep);

    qDebug() << name;
     qDebug() <<  seat_num;
     qDebug() << date_of_reservation;
    mTicket->getTicket();
}

void MainWindow::setRowFlightTable()
{
//    qDebug()<< ui->tableWidget->currentRow();

    setCurrent_row(ui->tableWidget->currentRow());
//    qDebug() << current_row;
}



MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pbConfirmeAndBook_clicked()
{


        if(addUserVerif == false){
            QMessageBox msgBox;
                msgBox.setText(" Please choose your flight in the list and inform your data !!.");
                msgBox.exec();
            return;
        }


        // ui->tableWReservation_->currentRow();
        qDebug() << "hellooo "<< ui->tableWidget->item(current_row,6)->text().toInt();

/*
 *  Ici on recupère les dimension de l'avion qui à été selectionné par l'utilisateur
 */

   QJsonObject Avion;
  // qInfo() << " clicked "  << m_Actual_Avion_Id;
   int t = m_Actual_Avion_Id;
   Avion = mClient->getAllInfosOnRoute( t );
   int nb_cols= Avion["flight_infos"].toObject()["nb_cols"].toInt();  // qInfo() << nb_cols;
   int nb_rows= Avion["flight_infos"].toObject()["nb_rows"].toInt();  // qInfo() << nb_rows;



/*
 *  Ici Je recupère la listes des place dèjà reservées dans l'avion.
 */


    QJsonObject reservedSeatsOb;
    reservedSeatsOb = Avion["reservations"].toObject();

    QStringList keys =  reservedSeatsOb.keys();

    QStringList takedSeats;

    foreach ( QString k , keys ){

        // qInfo() << "place occupée " << reservedSeatsOb[k].toObject()["seat_num"].toString();
        takedSeats.push_back(reservedSeatsOb[k].toObject()["seat_num"].toString());
    }



    /*
     * Ici On cree notre macket d'avion
     * On envoi en parametre les dimensions de l'avion,
     * la QList de sieges occupés.
     *
     */


    GraphAvion g;
    g.createGraph(nb_cols,nb_rows, takedSeats, m_Actual_Avion_Id);
    g.exec();


    mClient->addReservation(0,0,g.seat(),ui->tableWidget->item(current_row,6)->text().toInt(), ui->lePhoneNumber->text().toInt(), QDateTime::currentDateTime());


}



void MainWindow::Add_Usert()
{

/*
 * Cette fonction recupère les information de la personne qui à fait la réservation.
 *
 * On peut l'utlisisé pour l'jouter a la base de donné s'il n'est pas dèjà enregister;
 *
 */


    addUserVerif = false;


    qInfo() << "verif " << selected_flight;

    if(selected_flight==false){



        QMessageBox msgBox;
            msgBox.setText(" Please choose your flight in the list !!.");
            msgBox.exec();
    }


    bool AlreadyExist = false;

          /*
          *
         * Ici on verifie si les informations sont bien saisie
         *
         */


        if(ui->leFirstName->text().length() == 0 ){
            qInfo() << ui->leFirstName->text().length() << "Please enter your First Name";
                QMessageBox msgBox;
                msgBox.setText("Please enter your First Name");
                 msgBox.exec();

                 goto s1;

        }
        else if (ui->leLastName->text().length() == 0 ){
            QMessageBox msgBox;
                msgBox.setText("Please enter your Last Name!!");
                msgBox.exec();
                goto s1;
        }
        else if (ui->lePhoneNumber->text().length() == 0 ){
            QMessageBox msgBox;
                msgBox.setText("Please enter your Last Name!!");
                msgBox.exec();
                goto s1;
        }
        else if (ui->leEmail->text().length() == 0 ){
            QMessageBox msgBox;
            msgBox.setText("Please enter your mail adress!!");
            msgBox.exec();

            goto s1;
        }



            AlreadyExist = mClient->addUser(ui->leFirstName->text(),ui->leLastName->text(),
                                                ui->leEmail->text(),ui->lePhoneNumber->text(), ui->dateBirth->date());

           if(AlreadyExist){
               QMessageBox msgBox;
               msgBox.setText("Welcom to online reservation plateform!!, You are a new user, your information will be automatically saved ");
               msgBox.exec();
            }
            else{
                QMessageBox msgBox;
                msgBox.setText("Welcom to online reservation plateform!!. it's a pleasure to see you again!! ");
                msgBox.exec();

               }

           addUserVerif = true;
        s1:
        selected_flight = false;


        
}

int MainWindow::getCurrent_row() const
{
    return current_row;
}

void MainWindow::setCurrent_row(int newCurrent_row)
{
    current_row = newCurrent_row;
}


void MainWindow::deleteFlight()
{


   // qInfo() << ui->tableWidget->item( ui->tabWidgetAPP->currentIndex(),6)->text();

}

