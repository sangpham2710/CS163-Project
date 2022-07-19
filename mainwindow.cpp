#include "mainwindow.h"

#include <QMessageBox>
#include <QPointerEvent>

#include "./ui_mainwindow.h"
#include "App.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
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

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_tabWidgetDictionary_tabBarClicked(int newIndex) {
    int oldIndex = ui->tabWidgetDictionary->currentIndex();
    switch (oldIndex) {
        case Tab::SEARCH: {
            switch (newIndex) {
                case Tab::SEARCH: {
                    return;
                } break;
                case Tab::FAVORITE: {
                    widgetFavorite->reloadDefinitionTabs();
                    widgetFavorite->reloadListWidgetFavorite();
                } break;
                case Tab::GAME: {
                    widgetGame->reloadListDictionaries();
                    App::get().changeDictionary(widgetGame->getCurrentDictName());
                } break;
            }
        } break;
        case Tab::FAVORITE: {
            switch (newIndex) {
                case Tab::SEARCH: {
                    App::get().changeDictionary(
                        widgetSearch->getCurrentDictName());
                    widgetSearch->reloadFavoriteStates();
                } break;
                case Tab::FAVORITE: {
                    return;
                } break;
                case Tab::GAME: {
                    widgetGame->reloadListDictionaries();
                    App::get().changeDictionary(widgetGame->getCurrentDictName());
                } break;
            }
        } break;
        case Tab::GAME: {
            switch (newIndex) {
                case Tab::SEARCH: {
                    // Stop game
                    if (widgetGame->isPlaying()) {
                        widgetGame->resetGame();
                    }
                    App::get().changeDictionary(widgetSearch->getCurrentDictName());
                } break;
                case Tab::FAVORITE: {
                    if (widgetGame->isPlaying()) {
                        widgetGame->resetGame();
                    }
                } break;
                case Tab::GAME: {
                    return;
                } break;
            }
        } break;
    }
    ui->tabWidgetDictionary->setCurrentIndex(newIndex);
}
