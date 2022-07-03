#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "GameDialog.h"
QString state;
QString lang;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBoxSearch->addItem("Eng - Eng");
    ui->comboBoxSearch->addItem("Viet - Eng");
    ui->comboBoxSearch->addItem("Eng - Viet");
    ui->comboBoxSearch->addItem("Slang");
    ui->comboBoxSearch->addItem("Emoji");
    ui->comboBoxSearch->addItem("Favourite");
    this->setWindowTitle("Dictionary");
    this->setFixedHeight(544);
    this->setFixedWidth(960);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButtonAdd_clicked()
{
    dialogAddNewWord = new DialogAddNewWord(this);
    dialogAddNewWord->show();
}


void MainWindow::on_pushButtonRemove_clicked()
{
    QMessageBox::StandardButton confirm = QMessageBox::question(this, "Title", "Do you want to remove this word from the dictionary ?", QMessageBox::Yes | QMessageBox::No);
    if (confirm == QMessageBox::Yes)
    {
        //Delete the word
    }
    else
    {
        //Do nothing
    }
}


void MainWindow::on_pushButtonEdit_clicked()
{
    dialogEditWord = new DialogEditWord(this);
    dialogEditWord->show();
}


void MainWindow::on_Game_start_clicked()
{
    state=ui->qcomboboxDif->currentText();
    lang=ui->qcomboboxLang->currentText();
    GameDialog* game = new GameDialog(this, lang, state);
    game->show();
}

