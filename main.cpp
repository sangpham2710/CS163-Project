#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <QFile>
#include <QTextStream>
#include <CSV.h>

using namespace std;

const QString dictsPath = "input/";



QString readWordInLine(QString line) {
    QString word, defi;
    CSV::readLine(line, word, defi);
    return word;
}

bool createDictionary(QString dictName) {
    QString defisPath = "data/dicts/" + dictName + "/defis/";
    QString wordsPath = "data/dicts/" + dictName + "/words/";

    filesystem::create_directories(defisPath.toStdString());
    filesystem::create_directories(wordsPath.toStdString());

    int len = 0;
    int i = 0;
    QFile fin;
    fin.setFileName(dictsPath + dictName + ".csv");
    if(!fin.open(QFile::ReadOnly | QFile::Text)) return false;
    QString line;
    QTextStream in;
    in.setDevice(&fin);
    while (!in.atEnd()) {
        line = in.readLine();
        len++;
        QString c = QString::number(i);
        QString word;
        QFile fout;
        fout.setFileName(defisPath + c + ".csv");
        if(!fout.open(QFile::WriteOnly | QFile::Text | QFile::Append)) return false;
        QTextStream out;
        out.setDevice(&fout);
        out << line << "\n";
        fout.close();


        word = readWordInLine(line);
        fout.setFileName(wordsPath + "index.csv");
        if(!fout.open(QFile::WriteOnly | QFile::Text | QFile::Append)) return false;
        out << CSV::writeLine(word,c) << "\n";
        fout.close();

        i = (i + 1) % 1000;
    }
    fin.close();

    QFile fout;
    QTextStream out;
    fout.setFileName(defisPath + "info.txt");
    if(!fout.open(QFile::WriteOnly | QFile::Text)) return false;
    out.setDevice(&fout);
    out << len / 1000 + 1 << "\n" << 1000;
    fout.close();

    fout.setFileName(wordsPath + "info.txt");
    if(!fout.open(QFile::WriteOnly | QFile::Text)) return false;
    out << len;
    fout.close();

    return true;
}


int main() {

    createDictionary("Emotional");
    createDictionary("Eng-Fre");
    createDictionary("Eng-Ger");
    createDictionary("Eng-Ita");
    createDictionary("Eng-Por");
    createDictionary("Eng-Spa");
    createDictionary("Eng-Vie");
    createDictionary("Fre-Eng");
    createDictionary("Ger-Eng");
    createDictionary("Ita-Eng");
    createDictionary("Por-Eng");
    createDictionary("Slang");
    createDictionary("Spa-Eng");
    createDictionary("Vie-Eng");

    return 0;
}
