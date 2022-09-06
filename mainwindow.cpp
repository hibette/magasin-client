#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QDebug>
#include<QSystemTrayIcon>
#include <QRegExp>
#include "connection.h"
#include <QFileDialog>
#include <QPainter>
#include <QDate>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include <QPdfWriter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include "qrcode.h"

using namespace qrcodegen;
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->stackedWidget->setCurrentIndex(0);
    // appel de ft afficher
    ui->tableView->setModel(c.afficher());
    ui->tableView_2->setModel((m.afficher()));
    //input__control
    ui->lineEdit_23->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_15->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_19->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_6->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_5->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_11->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_12->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_25->setValidator(new QIntValidator(0,999999,this));
    QRegExp rx("[a-zA-Z]+");
    QValidator *validator = new
            QRegExpValidator (rx,this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit_4->setValidator(validator);
    ui->lineEdit_8->setValidator(validator);
    ui->lineEdit_9->setValidator(validator);
    ui->lineEdit_10->setValidator(validator);
    ui->lineEdit_22->setValidator(validator);
    ui->lineEdit_14->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
///////////////////////////////////////////////////////GESTION CLIENTS ////////////////////////////////////////////
// ajouter
void MainWindow::on_pushButton_3_clicked()
{
        QString nom =ui->lineEdit->text(); //recuperation des donnéées
        QString prenom =ui->lineEdit_2->text();
        QString email =ui->lineEdit_3->text();
        QString street =ui->lineEdit_4->text();
        QString genre =ui->comboBox->currentText();
        int age =ui->lineEdit_5->text().toInt();
        Client c(nom,prenom,email,street,genre,age); //constructeur parametré
        bool test=c.ajouter(); //appel a la ft ajouter plus test
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("ajoute \n"
                                                 "click to cancel"), QMessageBox::Cancel);
            ui->tableView->setModel(c.afficher());
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok") , QObject::tr("non effecue"),QMessageBox::Cancel);
}
//supprimer
void MainWindow::on_pushButton_5_clicked()
{
        int id =ui->lineEdit_12->text().toUInt();
        bool test=c.supprimer(id);
        if (test)
        {
            QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("supprimé \n" "click to cancel"),QMessageBox::Cancel);
            ui->tableView->setModel(c.afficher());
        }
        else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("suppression non effectué"),QMessageBox::Cancel);
}
//modifier
void MainWindow::on_pushButton_4_clicked()
{
            int id=ui->lineEdit_11->text().toUInt();
            QString nom=ui->lineEdit_8->text();
            QString prenom=ui->lineEdit_9->text();
            QString email=ui->lineEdit_7->text();
            QString street=ui->lineEdit_10->text();
            QString genre=ui->comboBox_2->currentText();
            int age=ui->lineEdit_6->text().toUInt();
            bool test=c.modifier(id,nom,prenom,email,street,genre,age);
            if(test)
            {
                QMessageBox::information(nullptr, QObject::tr("ok"),
                                         QObject::tr("modifier \n"
                                                     "click to cancel"), QMessageBox::Cancel);
                ui->tableView->setModel(c.afficher());
            }
            else
                QMessageBox::critical(nullptr, QObject::tr("not ok") , QObject::tr("non effecue"),QMessageBox::Cancel);
}
// selection avec click sur tableau
void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from CLIENT1  where id='"+val+"' or nom='"+val+"' or prenom='"+val+"' or email='"+val+"' or street='"+val+"' or genre='"+val+"' or age='"+val+"'");

    if (qry.exec())
    { while (qry.next())
        {
            //modifier
            ui->lineEdit_11->setText(qry.value(0).toString()); //id
            ui->lineEdit_8->setText(qry.value(1).toString()); //nom
            ui->lineEdit_9->setText(qry.value(2).toString()); //prenom
            ui->lineEdit_10->setText(qry.value(4).toString()); //adresse
            ui->lineEdit_7->setText(qry.value(3).toString()); //mail
            ui->lineEdit_6->setText(qry.value(6).toString()); //age
            //supprimer
            ui->lineEdit_12->setText(qry.value(0).toString()); //id
        }
    }
}
//trie par id
void MainWindow::on_pushButton_6_clicked()
{
    ui->tableView->setModel(c.trie_id());
}
//trie par nom
void MainWindow::on_pushButton_7_clicked()
{
    ui->tableView->setModel(c.trie_nom());
}
//trie par age
void MainWindow::on_pushButton_8_clicked()
{
    ui->tableView->setModel(c.trie_age());
}
//pdf
void MainWindow::on_pushButton_9_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
                           QPainter painter(&pdf);
                          int i = 4000;
                               painter.drawText(900,650,"gestion client");//titre

                               painter.setPen(Qt::red);//couleur du titre
                               painter.setFont(QFont("Time New Roman", 25)); //police et taille
                               painter.drawText(3000,1400,"list des clients"); //sous titre
                               painter.setPen(Qt::black);//couleur de sous titre
                               painter.setFont(QFont("Time New Roman", 15)); //police et taille de sous titre
                               painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                               painter.drawRect(100,3000,9400,500);
                               painter.setFont(QFont("Time New Roman", 9));//police et taille des données
                               painter.drawText(300,3300,"ID");
                               painter.drawText(2000,3300,"Nom");
                               painter.drawText(4000,3300,"prenom");
                               painter.drawText(5600,3300,"mail");
                               painter.drawText(7000,3300,"adresse");
                               painter.drawText(8000,3300,"genre");
                               painter.drawText(9000,3300,"age");
                               painter.drawRect(100,3000,9400,10700);
                               QTextDocument previewDoc;
                               QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                               QTextCursor cursor(&previewDoc); //date de l 'enregistreement pdf
                               QSqlQuery query;
                               query.prepare("select * from CLIENT1");
                               query.exec();
                               while (query.next())
                               {
                                   painter.drawText(300,i,query.value(0).toString());
                                   painter.drawText(2000,i,query.value(1).toString());
                                   painter.drawText(4000,i,query.value(2).toString());
                                   painter.drawText(5600,i,query.value(3).toString());
                                   painter.drawText(7000,i,query.value(4).toString());
                                   painter.drawText(8000,i,query.value(5).toString());
                                   painter.drawText(9000,i,query.value(6).toString());

                                  i = i +500;
                               }
                               int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                   QMessageBox::Yes|QMessageBox::No);//message de generer pdf
                                   if (reponse == QMessageBox::Yes)
                                   {
                                       QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                       painter.end();
                                   }
                                   else
                                   {
                                        painter.end();
}
}
//recherche
void MainWindow::on_lineEdit_13_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM CLIENT1 WHERE id LIKE'"+arg1+"%' or nom  LIKE'"+arg1+"%' or prenom  LIKE'"+arg1+"%'");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tableView->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !!\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
//stat
void MainWindow::on_pushButton_10_clicked()
{
                              QSqlQueryModel * model= new QSqlQueryModel();
                              model->setQuery("select * from CLIENT1 where genre = 'Femme' ");
                              float cat1=model->rowCount();
                              model->setQuery("select * from CLIENT1 where genre = 'Homme' ");
                              float cat2=model->rowCount();
                              float total=cat1+cat2;
                              QString a=QString("Femme "+QString::number((cat1*100)/total,'f',2)+"%" );
                              QString b=QString("Homme "+QString::number((cat2*100)/total,'f',2)+"%" );
                              QPieSeries *series = new QPieSeries();
                              series->append(a,cat1);
                              series->append(b,cat2);
                      if (cat1!=0)
                      {QPieSlice *slice = series->slices().at(0);
                       slice->setLabelVisible();
                       slice->setPen(QPen());}
                      if (cat2!=0)
                      {
                               // Add label, explode and define brush for 2nd slice
                               QPieSlice *slice1 = series->slices().at(1);
                               //slice1->setExploded();
                               slice1->setLabelVisible();
                      }
                              // Create the chart widget
                              QChart *chart = new QChart();
                              // Add data to chart with title and hide legend
                              chart->addSeries(series);
                              chart->setTitle("Pourcentage homme/femme : nombre de clients : "+ QString::number(total));
                              chart->legend()->hide();
                              // Used to display the chart
                              QChartView *chartView = new QChartView(chart);
                              chartView->setRenderHint(QPainter::Antialiasing);
                              chartView->resize(1000,500);
                              chartView->show();
}


///////////////////////////////////////////////////////GESTION MAGASIN ////////////////////////////////////////////
//modifie
void MainWindow::on_pushButton_13_clicked()
{
    int id=ui->lineEdit_25->text().toUInt();
    QString nom=ui->lineEdit_22->text();
    QString etat=ui->comboBox_4->currentText();
    int prix=ui->lineEdit_23->text().toUInt();
    bool test=m.modifier(id,nom,prix,etat);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("modifier \n"
                                             "click to cancel"), QMessageBox::Cancel);
        ui->tableView_2->setModel(m.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok") , QObject::tr("non effecue"),QMessageBox::Cancel);
}
//supprimer
void MainWindow::on_pushButton_12_clicked()
{
            int id =ui->lineEdit_19->text().toUInt();
            bool test=m.supprimer(id);
            if (test)
            {
                QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("supprimé \n" "click to cancel"),QMessageBox::Cancel);
                ui->tableView_2->setModel(m.afficher());
            }
            else
            QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                  QObject::tr("suppression non effectué"),QMessageBox::Cancel);
}
//ajouter
void MainWindow::on_pushButton_11_clicked()
{
    QString nom =ui->lineEdit_14->text();
    QString etat =ui->comboBox_3->currentText();
    int prix =ui->lineEdit_15->text().toInt();
    magasin m(nom,prix,etat);
    bool test=m.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajoute \n"
                                             "click to cancel"), QMessageBox::Cancel);
        ui->tableView_2->setModel(m.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok") , QObject::tr("non effecue"),QMessageBox::Cancel);
}
// selection avec click sur tableau
void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
    QString val=ui->tableView_2->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from magasin where id='"+val+"' or nom='"+val+"'");
    if (qry.exec())
    { while (qry.next())
        {
            //modifier
            ui->lineEdit_25->setText(qry.value(0).toString()); //id
            ui->lineEdit_22->setText(qry.value(1).toString()); //nom
            ui->lineEdit_23->setText(qry.value(2).toString()); //prix
            //supprimer
            ui->lineEdit_19->setText(qry.value(0).toString()); //id
        }
    }
}
// trie id
void MainWindow::on_pushButton_14_clicked()
{
    ui->tableView_2->setModel(m.trie_id());
}
//trie nom
void MainWindow::on_pushButton_15_clicked()
{
    ui->tableView_2->setModel(m.trie_nom());
}
//trie etat
void MainWindow::on_pushButton_16_clicked()
{
    ui->tableView_2->setModel(m.trie_etat());
}
//stat
void MainWindow::on_pushButton_18_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from magasin where etat = 'loue' ");
    float cat1=model->rowCount();
    model->setQuery("select * from magasin where etat = 'non loue' ");
    float cat2=model->rowCount();
    float total=cat1+cat2;
    QString a=QString("loue "+QString::number((cat1*100)/total,'f',2)+"%" );
    QString b=QString("non loue "+QString::number((cat2*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,cat1);
    series->append(b,cat2);
    if (cat1!=0)
    {QPieSlice *slice = series->slices().at(0);
    slice->setLabelVisible();
    slice->setPen(QPen());}
    if (cat2!=0)
    {
         // Add label, explode and define brush for 2nd slice
         QPieSlice *slice1 = series->slices().at(1);
         //slice1->setExploded();
         slice1->setLabelVisible();
    }
        // Create the chart widget
        QChart *chart = new QChart();
        // Add data to chart with title and hide legend
        chart->addSeries(series);
        chart->setTitle("Pourcentage magasin loué : nombre de magasin : "+ QString::number(total)); //titre du graphe
        chart->legend()->hide();
        //affichage du  graphe
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(1000,500);
        chartView->show();
}
//pdf
void MainWindow::on_pushButton_17_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
                                QPainter painter(&pdf);
                                int i = 4000;
                               painter.drawText(900,650,"gestion magasin");
                               painter.setPen(Qt::red);
                               painter.setFont(QFont("Time New Roman", 25));
                               painter.drawText(3000,1400,"list des magasins");
                               painter.setPen(Qt::black);
                               painter.setFont(QFont("Time New Roman", 15));
                               painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                               painter.drawRect(100,3000,9400,500);
                               painter.setFont(QFont("Time New Roman", 9));
                               painter.drawText(300,3300,"ID");
                               painter.drawText(2000,3300,"Nom");
                               painter.drawText(4000,3300,"prix");
                               painter.drawText(5600,3300,"etat");
                               painter.drawRect(100,3000,9400,10700);
                               QTextDocument previewDoc;
                               QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                               QTextCursor cursor(&previewDoc);
                               QSqlQuery query;
                               query.prepare("select * from magasin");
                               query.exec();
                               while (query.next())
                               {
                                   painter.drawText(300,i,query.value(0).toString());
                                   painter.drawText(2000,i,query.value(1).toString());
                                   painter.drawText(4000,i,query.value(2).toString());
                                   painter.drawText(5600,i,query.value(3).toString());
                                  i = i +500;
                               }
                               int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                   QMessageBox::Yes|QMessageBox::No);
                                   if (reponse == QMessageBox::Yes)
                                   {
                                       QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                       painter.end();
                                   }
                                   else
                                   {
                                        painter.end();
}
}
//recherche
void MainWindow::on_lineEdit_26_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM magasin WHERE id LIKE'"+arg1+"%' or nom  LIKE'"+arg1+"%' or prix  LIKE'"+arg1+"%'");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tableView_2->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !!\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
//qrcode client
void MainWindow::on_pushButton_20_clicked()
{
    int tabeq=ui->tableView->currentIndex().row();
   QVariant idd=ui->tableView->model()->data(ui->tableView->model()->index(tabeq,0));
   QString id=idd.toString();
  // QString code=idd.toSTring();
   QSqlQuery qry;
   qry.prepare("select * from CLIENT1 where id=:code");
   qry.bindValue(":code",id);
   qry.exec();
   QString nom,prenom,street;//attributs
   int age;

  while(qry.next()){

      id=qry.value(0).toString();
       nom=qry.value(1).toString();
       prenom=qry.value(2).toInt();
       street=qry.value(3).toInt();
       age=qry.value(5).toInt();
   }
   id=QString(id);
          id="CODE:\t" +id+ "NOM\t:" +nom+ "prenom:\t" +prenom+ "street:\t" +street+ "age:\t" +age;
   QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

   // Read the black & white pixels
   QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
   for (int y = 0; y < qr.getSize(); y++) {
       for (int x = 0; x < qr.getSize(); x++) {
           int color = qr.getModule(x, y);  // 0 for white, 1 for black

           // You need to modify this part
           if(color==0)
               im.setPixel(x, y,qRgb(254, 254, 254));
           else
               im.setPixel(x, y,qRgb(0, 0, 0));
       }
   }
   im=im.scaled(200,200);
  ui->label_22->setPixmap(QPixmap::fromImage(im));
}

void MainWindow::on_pushButton_19_clicked()
{
    int tabeq=ui->tableView_2->currentIndex().row();
   QVariant idd=ui->tableView_2->model()->data(ui->tableView_2->model()->index(tabeq,0));
   QString id=idd.toString();
  // QString code=idd.toSTring();
   QSqlQuery qry;
   qry.prepare("select * from magasin where id=:code");
   qry.bindValue(":code",id);
   qry.exec();
   QString nom,etat;//attributs
   int prix;

  while(qry.next()){

      id=qry.value(0).toString();
       nom=qry.value(1).toString();
       prix=qry.value(2).toInt();
       etat=qry.value(3).toInt();
   }
   id=QString(id);
          id="CODE:\t" +id+ "NOM\t:" +nom+ "prix:\t" +prix+ "etat:\t" +etat;
   QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

   // Read the black & white pixels
   QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
   for (int y = 0; y < qr.getSize(); y++) {
       for (int x = 0; x < qr.getSize(); x++) {
           int color = qr.getModule(x, y);  // 0 for white, 1 for black

           // You need to modify this part
           if(color==0)
               im.setPixel(x, y,qRgb(254, 254, 254));//code la couleur noire
           else
               im.setPixel(x, y,qRgb(0, 0, 0));//code de la couleur blance
       }
   }
   im=im.scaled(200,200);
  ui->label_21->setPixmap(QPixmap::fromImage(im));
}
