#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>

using namespace std;

Client::Client() // developpement de constructeur par defaut
{
id=0;
nom=" ";
prenom=" ";
email=" ";
street=" ";
genre=" ";
age=0;
}

Client::Client(QString nom , QString prenom, QString  email, QString street, QString genre, int age)
{
    this->nom=nom;this->prenom=prenom;this->email=email;this->street=street;this->genre=genre;this->age=age;
}

QString Client::getnom(){return nom;}  //developpement de getter
QString Client::getprenom(){return prenom;}
QString Client::getemail (){return email;}
QString Client::getstreet (){return street;}
QString Client::getgenre() {return genre;}

int Client::getage (){return age;}
//int Client::getid(){return id;}

void Client::setnom (QString nom){this->nom=nom;}
void Client::setprenom (QString prenom){this->prenom=prenom;}
void Client::setemail (QString email){this->email=email;}
void Client::setstreet (QString street){this->street=street;}
void Client::setgenre (QString genre){this->genre=genre;}
void Client::setage(int age){this->age=age;}

bool Client::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    QString age_string=QString::number(age);

         query.prepare("INSERT INTO CLIENT1 (id,nom,prenom,email,street,genre,age) "
                       "VALUES (:id, :nom, :prenom, :email, :street, :genre, :age )");
         query.bindValue(":id", id);
         query.bindValue(":nom", nom);
         query.bindValue(":prenom", prenom);
         query.bindValue(":email", email);
         query.bindValue(":street", street);
         query.bindValue(":genre", genre);

         query.bindValue(":age", age);


         return query.exec();
}



bool Client::supprimer(int id )
{   QSqlQuery query;


         query.prepare("delete from CLIENT1 where id=:id");
         query.bindValue(":id", id);


         return query.exec();




}
QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model ->setQuery("SELECT * FROM CLIENT1 ORDER BY id");

    model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("id"));
    model ->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model ->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model ->setHeaderData(3,Qt::Horizontal,QObject::tr("email"));
    model ->setHeaderData(4,Qt::Horizontal,QObject::tr("street"));
    model ->setHeaderData(5,Qt::Horizontal,QObject::tr("genre"));

    model ->setHeaderData(6,Qt::Horizontal,QObject::tr("age"));
    //model ->setHeaderData(7,Qt::Horizontal,QObject::tr("date_ajout"));

    return model;
}
QSqlQueryModel* Client::trie_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model ->setQuery("SELECT * FROM CLIENT1 ORDER BY id");

    model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("id"));
    model ->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model ->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model ->setHeaderData(3,Qt::Horizontal,QObject::tr("email"));
    model ->setHeaderData(4,Qt::Horizontal,QObject::tr("street"));
    model ->setHeaderData(5,Qt::Horizontal,QObject::tr("genre"));

    model ->setHeaderData(6,Qt::Horizontal,QObject::tr("age"));
    //model ->setHeaderData(7,Qt::Horizontal,QObject::tr("date_ajout"));

    return model;
}
QSqlQueryModel* Client::trie_nom()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model ->setQuery("SELECT * FROM CLIENT1 ORDER BY nom");

    model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("id"));
    model ->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model ->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model ->setHeaderData(3,Qt::Horizontal,QObject::tr("email"));
    model ->setHeaderData(4,Qt::Horizontal,QObject::tr("street"));
    model ->setHeaderData(5,Qt::Horizontal,QObject::tr("genre"));

    model ->setHeaderData(6,Qt::Horizontal,QObject::tr("age"));
    //model ->setHeaderData(7,Qt::Horizontal,QObject::tr("date_ajout"));

    return model;
}
QSqlQueryModel* Client::trie_age()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model ->setQuery("SELECT * FROM CLIENT1 ORDER BY age");

    model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("id"));
    model ->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model ->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model ->setHeaderData(3,Qt::Horizontal,QObject::tr("email"));
    model ->setHeaderData(4,Qt::Horizontal,QObject::tr("street"));
    model ->setHeaderData(5,Qt::Horizontal,QObject::tr("genre"));

    model ->setHeaderData(6,Qt::Horizontal,QObject::tr("age"));
    //model ->setHeaderData(7,Qt::Horizontal,QObject::tr("date_ajout"));

    return model;
}
bool Client::modifier(int id,QString nom, QString prenom, QString email, QString street, QString genre, int age)
{

    QSqlQuery query;
        query.prepare("UPDATE CLIENT1 SET nom=:nom,prenom=:prenom,email=:email,street=:street,genre=:genre,age=:age where id=(?) ");
        query.addBindValue(nom);
        query.addBindValue(prenom);
        query.addBindValue(email);
        query.addBindValue(street);
        query.addBindValue(genre);

        query.addBindValue(age);
        query.addBindValue(id);

   return  query.exec();
}




