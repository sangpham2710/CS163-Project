#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <qpixmap.h>
#include <iostream>
#include <string>
#include <QString>
#include <QFile>
#include "CSV.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile fin(":/data/data/Eng-Vie.csv");

    if (!fin.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Could not open file";
    }

    QTextStream in(&fin);
    QString test = in.readLine();
    QString word, def;
    CSV::readLine(test, word, def);

    ui->label->setText(word);
    ui->label_2->setText(def);

    fin.close();

    QFile fout(":/data/data/output.txt");

    if (!fout.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Could not open file";
    }

    QTextStream out(&fout);

    out << word << " "  << def;
    fout.flush();
    fout.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

