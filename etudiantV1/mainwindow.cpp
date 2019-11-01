#include "mainwindow.h"
#include "dialogapropos.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
   // avoirEtudiant();
    afficherEtudiant();
    afficherSpe();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// sqlite implementer dans un table view permet de voir et de modifer la table
//GestionEtudiantV1

 /* void MainWindow::avoirEtudiant()
{
    QSqlTableModel *maTableEtudiants = new QSqlTableModel();
    maTableEtudiants->setTable("etudiant");
    maTableEtudiants->select();

    ui->tableViewGestion->setModel(maTableEtudiants);
    ui->tableViewGestion->hideColumn(0);
} */


void MainWindow::on_pushButtonQuit_clicked()
{
    close();
}

void MainWindow::afficherEtudiant()
{
 QSqlQuery reqEtudiant("Select etuNom,etuPrenom,speLib from etudiant inner join specialite on etuSpe=speId");
 int numLigne=0;
 ui->tableWidgetEtudiant->setRowCount(0);// On defini le nombre de ligne que fera le tableau

 while(reqEtudiant.next()) //Boucle permettant de faire ligne par ligne tout
 {
    ui->tableWidgetEtudiant->setRowCount((ui->tableWidgetEtudiant->rowCount()+1));
     QString leNom = reqEtudiant.value("etuNom").toString(); // On recupere les informations séparément
     QString lePrenom = reqEtudiant.value("etuPrenom").toString();
     QString laSpe = reqEtudiant.value("speLib").toString();


     ui->tableWidgetEtudiant->setItem(numLigne,0, new QTableWidgetItem (leNom)); // ligne puis colonne , puis l'item que l'on veut ajouter si il n'existe pas faire comme sur la ligne
     ui->tableWidgetEtudiant->setItem(numLigne,1, new QTableWidgetItem (lePrenom));
     ui->tableWidgetEtudiant->setItem(numLigne,2,new QTableWidgetItem (laSpe));
     numLigne++;

}
    ui->tableWidgetEtudiant->resizeRowsToContents();
}



void MainWindow::on_pushButtonAdd_clicked()
{
     QString nomAdd = ui->lineEditNom->text();
     QString prenomAdd = ui->lineEditPrenom->text();
     QString speAdd= ui->comboBoxOption->currentData().toString();

     QSqlQuery addEtudiant("Insert into etudiant (etuNom,etuPrenom,etuSpe) values ('"+nomAdd+"','"+prenomAdd+"','"+speAdd+"')");
     afficherEtudiant();
}

void MainWindow::on_pushButtonSuppr_clicked()
{
    //On doit supprimer la ligne que l'on a selectionner du tableau et de la base de donnée
    QSqlQuery reqSuppr("delete from etudiant where etuNom='"+ui->lineEditNom->text()+"' ");
    afficherEtudiant();

}

void MainWindow::on_tableWidgetEtudiant_cellDoubleClicked(int row, int column)
{
    ui->lineEditNom->setText(ui->tableWidgetEtudiant->item(row,0)->text());
    ui->lineEditPrenom->setText(ui->tableWidgetEtudiant->item(row,1)->text());
    ui->comboBoxOption->setCurrentText(ui->tableWidgetEtudiant->item(row,2)->text());
    QSqlQuery reqDemandeNum("select etuNum from etudiant where etuNom='"+ui->lineEditNom->text()+"'");
    reqDemandeNum.first();
    ui->labelNum->setText( reqDemandeNum.value("etuNum").toString());



}

void MainWindow::on_pushButtonModif_clicked()
{
    QSqlQuery reqModif("update etudiant set etuNom='"+ui->lineEditNom->text()+"' ,etuPrenom='"+ui->lineEditPrenom->text()+"' ,etuSpe='"+ui->comboBoxOption->currentText()+"' where etuNum='"+ui->labelNum->text()+"' ");
    //
    afficherEtudiant();
}

void MainWindow::on_actionA_Propos_triggered()
{
    DialogAPropos dAPropos(this);
    dAPropos.exec();
}

void MainWindow::afficherSpe()
{
    QSqlQuery reqComboBox("select speId,speLib from specialite ;");
    while (reqComboBox.next())
    {
        QString numSpe = reqComboBox.value("speId").toString();
        QString libSpe =reqComboBox.value("speLib").toString();

        ui->comboBoxOption->addItem(libSpe,numSpe);

    }

}
