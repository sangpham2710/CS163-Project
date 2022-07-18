#include "widgetsearch.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <filesystem>

#include "App.h"
#include "Dictionary.h"
#include "ui_widgetsearch.h"
#include "widgetdefinition.h"

WidgetSearch::WidgetSearch(QWidget* parent)
    : QWidget(parent), ui(new Ui::WidgetSearch) {
    ui->setupUi(this);
    App::get();
    for (auto& dictName : App::get().getListDictionaries()) {
        ui->comboBoxDictionaryType->addItem(dictName);
    }
    currentDictName = ui->comboBoxDictionaryType->currentText();

    ui->tabWidgetDefinition->clear();
    ui->radioButtonSearchKeyword->setChecked(true);
    ui->pushButtonAddWord->setEnabled(false);
    loadHistory();
}

WidgetSearch::~WidgetSearch() {
    delete ui;
}

// Double click to word in history
void WidgetSearch::on_listWidgetHistory_itemDoubleClicked(
    QListWidgetItem* item) {
    QString word = item->text();
    for (int tabIndex = 0; tabIndex < ui->tabWidgetDefinition->count();
         ++tabIndex) {
        if (ui->tabWidgetDefinition->tabText(tabIndex) == word) {
            ui->tabWidgetDefinition->setCurrentIndex(tabIndex);
            return;
        }
    }
    auto newTab = new WidgetDefinition(this);
    ui->tabWidgetDefinition->addTab(newTab, word);
    ui->tabWidgetDefinition->setCurrentIndex(ui->tabWidgetDefinition->count() -
                                             1);
    // set title of the definition
    newTab->setWord(word);

    // set definition of the definition
    QString definition = App::get().getDefinition(word);
    newTab->setDefinition(definition);

    // set favorite
    newTab->setFavoriteState(word);
}

void WidgetSearch::removeCurrentTabDefinition() {
    int index = ui->tabWidgetDefinition->currentIndex();
    ui->tabWidgetDefinition->removeTab(index);
}

void WidgetSearch::reloadFavoriteStates() {
    QList<QString> words;
    for (int tabIndex = 0; tabIndex < ui->tabWidgetDefinition->count();
         ++tabIndex) {
        words.push_back(ui->tabWidgetDefinition->tabText(tabIndex));
    }
    ui->tabWidgetDefinition->clear();
    for (auto& word : words) {
        auto newTab = new WidgetDefinition(this);
        ui->tabWidgetDefinition->addTab(newTab, word);
        ui->tabWidgetDefinition->setCurrentIndex(
            ui->tabWidgetDefinition->count() - 1);
        // set title of the definition
        newTab->setWord(word);

        // set definition of the definition
        QString definition = App::get().getDefinition(word);
        newTab->setDefinition(definition);

        // set favorite
        newTab->setFavoriteState(word);
    }
}

void WidgetSearch::clearWidgetHistory() {
    ui->listWidgetHistory->clear();
}

void WidgetSearch::clearLineEditSearch() {
    ui->lineEditSearch->clear();
}


void WidgetSearch::on_tabWidgetDefinition_tabCloseRequested(int index) {
    ui->tabWidgetDefinition->removeTab(index);
}


void WidgetSearch::on_pushButtonRandomWord_clicked() {
    QString word = App::get().getRandomWord();
    for (int tabIndex = 0; tabIndex < ui->tabWidgetDefinition->count();
         ++tabIndex) {
        if (ui->tabWidgetDefinition->tabText(tabIndex) == word) {
            ui->tabWidgetDefinition->setCurrentIndex(tabIndex);
            return;
        }
    }
    auto newTab = new WidgetDefinition(this);
    ui->tabWidgetDefinition->addTab(newTab, word);
    ui->tabWidgetDefinition->setCurrentIndex(ui->tabWidgetDefinition->count() -
                                             1);
    // set title of the definition
    newTab->setWord(word);

    // set definition of the definition
    QString definition = App::get().getDefinition(word);
    newTab->setDefinition(definition);

    // set favorite
    newTab->setFavoriteState(word);
}

// Change text in combo box dictionary type
void WidgetSearch::on_comboBoxDictionaryType_currentTextChanged(
    const QString& text) {
    QString dictName = ui->comboBoxDictionaryType->currentText();
    App::get().changeDictionary(dictName);
    currentDictName = dictName;
    ui->lineEditSearch->clear();
    ui->tabWidgetDefinition->clear();
    loadHistory();
}

// Change text in searching bar -> change text in history widget
void WidgetSearch::on_lineEditSearch_textChanged(const QString& prefix) {
    if (prefix == "") {
        ui->pushButtonAddWord->setEnabled(false);
        loadHistory();
        return;
    }
    if (!ui->radioButtonSearchKeyword->isChecked()) {
        return;
    }
    auto result = App::get().getListWordsWithPrefix(prefix);
    if (result.size() == 0) {
        // Add new word enabled
        ui->pushButtonAddWord->setEnabled(true);
    } else
        ui->pushButtonAddWord->setEnabled(false);

    ui->listWidgetHistory->clear();
    for (auto& word : result) {
        new QListWidgetItem(word, ui->listWidgetHistory);
    }
}

// Change text in history widget
void WidgetSearch::loadHistory() {
    ui->listWidgetHistory->clear();
    for (auto& word : App::get().getHistory()) {
        new QListWidgetItem(word, ui->listWidgetHistory);
    }
    for (int listIndex = 0; listIndex < ui->listWidgetHistory->count();
         ++listIndex) {
        auto item = ui->listWidgetHistory->item(listIndex);
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    }
}

// Press reset button
void WidgetSearch::on_pushButtonReset_clicked() {
    QMessageBox::StandardButton confirm = QMessageBox::question(
        this, "Title", "Do you want to reset the current dictionary ?",
        QMessageBox::Yes | QMessageBox::No);
    if (confirm == QMessageBox::Yes) {
        ui->listWidgetHistory->clear();
        ui->tabWidgetDefinition->clear();
        loadHistory();
        ui->lineEditSearch->clear();
        App::get().resetDictionary();
    }
}

void WidgetSearch::openDialogAddNewWord() {
    QString newWord = ui->lineEditSearch->text();
    DialogAddNewWord dialogAddNewWord;
    dialogAddNewWord.setDataAddNewWord(newWord);
    dialogAddNewWord.exec();
}

// Press add new word button
void WidgetSearch::on_pushButtonAddWord_clicked() {
    openDialogAddNewWord();
}


void WidgetSearch::on_lineEditSearch_returnPressed() {
    if (ui->radioButtonSearchDictionary->isChecked()) {
        auto result =
            App::get().getListWordsHaveDefinition(ui->lineEditSearch->text());
        ui->listWidgetHistory->clear();
        for (auto& word : result) {
            new QListWidgetItem(word, ui->listWidgetHistory);
        }
    }
}

const QString& WidgetSearch::getCurrentDictName() const {
    return currentDictName;
}

namespace fs = std::filesystem;

void WidgetSearch::on_pushButtonAddDictionary_clicked() {
    const int NUM_PARTS = 1000;

    QString path = QFileDialog::getOpenFileName(this, "Open file", "C://",
                                                tr("CSV files (*.csv)"));

    if (path == "") return;

    int index = path.lastIndexOf('/');
    QString dictName = path.mid(index + 1, path.length() - index - 5);

    if (App::get().getListDictionaries().contains(dictName)) {
        QMessageBox::critical(this, "Add Dictionary",
                              "This dictionary already exists!");
        return;
    }

    QString defisPath = "data/dicts/" + dictName + "/defis/";
    QString wordsPath = "data/dicts/" + dictName + "/words/";

    fs::create_directories(defisPath.toStdString());
    fs::create_directories(wordsPath.toStdString());

    int len = 0;
    int i = 0;
    QFile fin;
    fin.setFileName(path);
    if (!fin.open(QFile::ReadOnly | QFile::Text)) return;
    QString line;
    QTextStream in;
    in.setDevice(&fin);
    while (!in.atEnd()) {
        line = in.readLine();
        len++;
        QString word;
        QFile fout;
        fout.setFileName(defisPath + QString::number(i) + ".csv");
        if (!fout.open(QFile::WriteOnly | QFile::Text | QFile::Append)) return;
        QTextStream out;
        out.setDevice(&fout);
        out << line << "\n";
        fout.close();


        word = CSV::readWordInLine(line);
        fout.setFileName(wordsPath + "index.csv");
        if (!fout.open(QFile::WriteOnly | QFile::Text | QFile::Append)) return;
        out << CSV::writeLine(word, QString::number(i)) << "\n";
        fout.close();

        i = (i + 1) % NUM_PARTS;
    }
    fin.close();

    QFile fout;
    QTextStream out;
    fout.setFileName(defisPath + "info.txt");
    if (!fout.open(QFile::WriteOnly | QFile::Text)) return;
    out.setDevice(&fout);
    out << len / NUM_PARTS + 1 << '\n' << NUM_PARTS;
    fout.close();

    fout.setFileName(wordsPath + "info.txt");
    if (!fout.open(QFile::WriteOnly | QFile::Text)) return;
    out << len;
    fout.close();

    fs::copy("data/dicts/" + dictName.toStdString(),
             "data/dicts-origin/" + dictName.toStdString(),
             fs::copy_options::recursive);

    ui->comboBoxDictionaryType->addItem(dictName);
    App::get().addDictionary(dictName);

    ui->comboBoxDictionaryType->setCurrentText(dictName);
    return;
}
