#include "magasin.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>

using namespace std;


magasin::magasin()
{
id=0;
nom=" ";
prix=0;
etat=" ";
}

magasin::magasin(QString nom ,int prix, QString  etat)
{
    this->nom=nom;this->prix=prix;this->etat=etat;
}

QString magasin::getnom(){return nom;}
QString magasin::getetat(){return etat;}
int magasin::getprix (){return prix;}
int magasin::getid(){return id;}
void magasin::setnom (QString nom){this->nom=nom;}
void magasin::setetat (QString etat){this->etat=etat;}
//void magasin::setprix (int) (int prix){this->prix=prix;}


bool magasin::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    QString age_string=QString::number(prix);

         query.prepare("INSERT INTO magasin (nom,prix,etat) "
                       "VALUES (:nom, :prix, :etat)");
         query.bindValue(":nom", nom);
         query.bindValue(":prix", prix);
         query.bindValue(":etat", etat);
         return query.exec();
}



bool magasin::supprimer(int id )
{   QSqlQuery query;
         query.prepare("delete from magasin where id=:id");
         query.bindValue(":id", id);
         return query.exec();
}
QSqlQueryModel* magasin::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model ->setQuery("SELECT * FROM magasin ORDER BY id");
    model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("id"));
    model ->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model ->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
    model ->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
    return model;
}
QSqlQueryModel* magasin::trie_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model ->setQuery("SELECT * FROM magasin ORDER BY id");
    model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("id"));
    model ->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model ->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
    model ->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
    return model;
}
QSqlQueryModel* magasin::trie_nom()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model ->setQuery("SELECT * FROM magasin ORDER BY nom");
    model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("id"));
    model ->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model ->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
    model ->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
    return model;
}
QSqlQueryModel* magasin::trie_etat()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model ->setQuery("SELECT * FROM magasin ORDER BY etat");
    model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("id"));
    model ->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model ->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
    model ->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
    return model;
}
bool magasin::modifier(int id,QString nom, int prix, QString etat)
{
    QSqlQuery query;
        query.prepare("UPDATE magasin SET nom=:nom,prix=:prix,etat=:etat where id=(?) ");
        query.addBindValue(nom);
        query.addBindValue(prix);
        query.addBindValue(etat);
        query.addBindValue(id);
   return  query.exec();
}




