#ifndef MAGASIN_H
#define MAGASIN_H
#include <QString>
#include <QSqlQueryModel>

class magasin
{
public:
    magasin();
    magasin(QString,int,QString);

    QString getnom();
    int getprix();
    QString getetat();
    int getid();

    void setnom (QString);
    void setprix (int);
    void setetat (QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer (int id);
    bool modifier(int,QString,int,QString);
    QSqlQueryModel * trie_id();
    QSqlQueryModel * trie_nom();
    QSqlQueryModel * trie_etat();
 private:
    QString nom , etat;
    int prix,id;
};

#endif // MAGASIN_H
