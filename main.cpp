#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

const string dictsPath = "dicts/";

string readWordInLine(string line) {
    string word = "";
    word.push_back(line[0]);
    int i = 1;
    while (line[i] != '<' && i < line.length()) {
        word.push_back(line[i++]);
    }
    if (word[word.size() - 1] == '"') word = word.substr(0, word.size() - 1);
    return word;
}

bool createDictionary(string dictName) {
    string defisPath = "data/" + dictName + "/defis/";
    string wordsPath = "data/" + dictName + "/words/";

    filesystem::create_directories(defisPath);
    filesystem::create_directories(wordsPath);

    int len = 0;
    int i = 0;
    ifstream fin(dictsPath + dictName + ".csv");
    if(!fin.is_open()) return false;
    string line;
    while (getline(fin, line)) {
        len++;
        string c = to_string(i);
        string word;
        ofstream fout;

        fout.open(defisPath + c + ".csv", ios::app);
        fout << line << endl;
        fout.close();


        word = readWordInLine(line);
        fout.open(wordsPath + "index.csv", ios::app);
        fout << word << c << endl;
        fout.close();

        i = (i + 1) % 1000;
    }
    fin.close();

    ofstream fout;

    fout.open(defisPath + "info.txt");
    fout << len / 1000 + 1 << endl << 1000;
    fout.close();

    fout.open(wordsPath + "info.txt");
    fout << len;
    fout.close();

    return true;
}


int main() {

    createDictionary("Eng-Eng");
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
    createDictionary("Spa-Eng");
    createDictionary("Vie-Eng");

    return 0;
}
