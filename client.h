#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQueryModel>

class Client
{
public:
    Client(); // constructeur par defaut
    Client(QString,QString,QString,QString,QString,int); //constructeur parametré

    QString getnom();
    QString getprenom();
    QString getemail ();
    QString getstreet();
    QString getgenre();
    int getage ();
    int getid();

    void setnom (QString);
    void setprenom (QString);
    void setemail (QString);
    void setstreet(QString);
    void setgenre(QString);
    void setage(int);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer (int id);
    bool modifier(int,QString,QString,QString,QString,QString,int);
    QSqlQueryModel * trie_id();
    QSqlQueryModel * trie_nom();
    QSqlQueryModel * trie_age();


 private:
    QString nom , prenom , email , street, genre;
    int age ,id ; // les attributs
};

#endif // CLIENT_H
