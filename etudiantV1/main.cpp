#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QString cheminBdd = "/home/jeremy/Documents/qtCreator/etudaintV1/etudiantV1/bddEtudiantV1/gestionEtudiantsV1-11.bdd" ;
    //On teste si le fichier est existant
    if (QFileInfo(cheminBdd).exists() )
    {
         QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(cheminBdd);
        db.open();
       qDebug()<<" fichier existant";
    }
    else
    {
        qDebug()<<" fichier non existant";

        //On crée le fichier
        QFile file (cheminBdd);
        //On ouvre la base de donnée
       QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
       db.setDatabaseName(cheminBdd);
       db.open();

       //On implémente le code dans la base de données

       QString reqBdd2("create table specialite ("
                       "speId tinyint primary key,"
                       "speLib varchar(6) "
                       ")" );

       QString reqBdd ("create table etudiant ("
                       "etuNum integer primary key autoincrement, "
                       "etuNom varchar(30), "
                       "etuPrenom varchar(30),"
                       "etuSpe tinyint, "
                       "    constraint etudiant_specialite"
                       "    foreign key (etuSpe)"
                       "    references specialite (speId) "
                       ")");


       QString reqBdd3("create table parametre ("
                       "version varchar(50)primary key"
                       ")"
                       );

       QString reqSpecialite ("insert into specialite values"
                              "(1,'SLAM'),"
                              "(2,'SISR');");

       //Requete permettant
        db.exec(reqBdd2);
        db.exec(reqBdd);
        db.exec(reqBdd3);
        //qDebug() << db.exec(reqBdd);
        db.exec(reqSpecialite);
        // ou
        //QSqlQuery laReq(reqBdd);
        //laReq.exec();

    }








MainWindow w;
w.show();
return a.exec();


}
