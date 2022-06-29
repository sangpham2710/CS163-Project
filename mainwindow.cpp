#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <typeinfo>
#include <QListWidgetItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_insertLineEdit_returnPressed()
{
    QString word = ui->insertLineEdit->text();
    trie.insert(word, "nghĩa của từ " + word);
    ui->resultLabel->setText("Inserted \"" + word + "\"");
    ui->insertLineEdit->setText("");
}


void MainWindow::on_findLineEdit_returnPressed()
{
    QString word = ui->findLineEdit->text();
    bool result = trie.contains(word);
    if (result) {
        ui->resultLabel->setText(trie[word]);
    } else {
        ui->resultLabel->setText("Not Found!");
    }
    ui->findLineEdit->setText("");
}


void MainWindow::on_findPrefixLineEdit_returnPressed()
{
    QString word = ui->findPrefixLineEdit->text();
    auto result = trie.searchPrefix(word);
    ui->listWidget->clear();
    for (auto x : result) {
        new QListWidgetItem(x, ui->listWidget);
    }
    ui->findPrefixLineEdit->setText("");
}

