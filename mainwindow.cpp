#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "App.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidgetDictionary->clear();
    widgetSearch = new WidgetSearch(this);
    widgetFavorite = new WidgetFavorite(this);
    widgetGame = new WidgetGame(this);
    ui->tabWidgetDictionary->addTab(widgetSearch, QString("Search"));
    ui->tabWidgetDictionary->addTab(widgetFavorite, QString("Favorite"));
    ui->tabWidgetDictionary->addTab(widgetGame, QString("Game"));
    this->setWindowTitle("Dictionary");
    App::get();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tabWidgetDictionary_tabBarClicked(int newIndex)
{
    int oldIndex = ui->tabWidgetDictionary->currentIndex();
    qDebug() << oldIndex << newIndex;
    switch (oldIndex) {
        case Tab::SEARCH:
        {
            switch (newIndex) {
                case Tab::SEARCH:
                {
                    return;
                }
                break;
                case Tab::FAVORITE:
                {
                    widgetFavorite->reloadDefinitionTabs();
                    widgetFavorite->reloadListWidgetFavorite();
                }
                break;
                case Tab::GAME:
                {
                    App::get().changeDictionary(widgetGame->getCurrentDictName());

                }
                break;
            }
        }
        break;
        case Tab::FAVORITE:
        {
            switch (newIndex) {
                case Tab::SEARCH:
                {
                    qDebug() << "HERE1";
                    App::get().changeDictionary(widgetSearch->getCurrentDictName());
                    qDebug() << "HERE2";
                    widgetSearch->reloadFavoriteStates();
                }
                break;
                case Tab::FAVORITE:
                {
                    return;
                }
                break;
                case Tab::GAME:
                {
                    App::get().changeDictionary(widgetGame->getCurrentDictName());
                }
                break;
            }
        }
        break;
        case Tab::GAME:
        {
            switch (newIndex) {
                case Tab::SEARCH:
                {
                    // Stop game
                    QMessageBox::StandardButton confirmAccept = QMessageBox::question(this, "Exit Game", "Are you sure you want to switch tab?\nYour game will be reset!",
                                                                                    QMessageBox::Yes | QMessageBox::No);
                    if (confirmAccept == QMessageBox::Yes)
                    {
                        widgetGame->resetGame();
                        App::get().changeDictionary(widgetSearch->getCurrentDictName());
                    } else {
                        return;
                    }

                }
                break;
                case Tab::FAVORITE:
                {
                    QMessageBox::StandardButton confirmAccept = QMessageBox::question(this, "Exit Game", "Are you sure you want to switch tab?\nYour game will be reset!",
                                                                                    QMessageBox::Yes | QMessageBox::No);
                    if (confirmAccept == QMessageBox::Yes)
                    {
                        widgetGame->resetGame();
                    } else {
                        return;
                    }
                }
                break;
                case Tab::GAME:
                {
                    return;
                }
                break;
            }
        }
        break;
    }
    ui->tabWidgetDictionary->setCurrentIndex(newIndex);
}

