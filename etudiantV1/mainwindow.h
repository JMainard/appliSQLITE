#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSql>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
     // void avoirEtudiant();

    void on_pushButtonQuit_clicked();
    void afficherEtudiant();

    void on_pushButtonAdd_clicked();

    void on_pushButtonSuppr_clicked();

    //void on_tableWidgetEtudiant_itemClicked(QTableWidgetItem *item);

    void on_tableWidgetEtudiant_cellDoubleClicked(int row, int column);

    void on_pushButtonModif_clicked();

    void on_actionA_Propos_triggered();

    void afficherSpe();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
