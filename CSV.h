#ifndef CSV_H
#define CSV_H

#include <QList>
#include <QString>

class CSV {
   public:
    static void _readLine(const QString& line, QList<QString>& values) {
        QString value = "";
        int state = 0;
        for (const QChar& c : line) {
            switch (state) {
                case 0: {
                    switch (c.unicode()) {
                        case ',':
                            values.push_back("");
                            break;
                        case '"':
                            state = 2;
                            break;
                        default:
                            value += c;
                            state = 1;
                            break;
                    }
                    break;
                }
                case 1: {
                    switch (c.unicode()) {
                        case ',':
                            values.push_back(value);
                            value = "";
                            state = 0;
                            break;
                        case '"':
                            return;
                        default:
                            value += c;
                            break;
                    }
                    break;
                }
                case 2: {
                    switch (c.unicode()) {
                        case '"':
                            state = 3;
                            break;
                        default:
                            value += c;
                            break;
                    }
                    break;
                }
                case 3: {
                    switch (c.unicode()) {
                        case ',':
                            values.push_back(value);
                            value = "";
                            state = 0;
                            break;
                        case '"':
                            value += c;
                            state = 2;
                            break;
                        default:
                            return;
                    }
                    break;
                }
            }
        }
        switch (state) {
            case 0:
            case 1:
            case 3:
                values.push_back(value);
                break;
            case 2:
                return;
        }
    }
    static QString _writeLine(const QList<QString>& values) {
        QString line = "";
        bool first = true;
        for (const QString& value : values) {
            if (first)
                first = false;
            else
                line += ',';
            bool enclosed = false;
            for (const QChar& c : value)
                if (c == ',' || c == '"') enclosed = true;
            if (!enclosed)
                line += value;
            else {
                QString escaped = "";
                escaped += '"';
                for (QChar c : value) {
                    if (c == '"') {
                        escaped += '"';
                        escaped += '"';
                    } else {
                        escaped += c;
                    }
                }
                escaped += '"';
                line += escaped;
            }
        }
        return line;
    }

    template <class... Ts>
    static void readLine(const QString& line, Ts&... args) {
        QList<QString> values;
        _readLine(line, values);
        int index = 0;
        auto fn = [&](auto& v) {
            if (index == values.size()) return;
            v = values[index++];
        };
        (fn(args), ...);
    }

    template <class... Ts>
    static QString writeLine(Ts... args) {
        QList<QString> values;
        auto fn = [&](auto& v) { values.push_back(v); };
        (fn(args), ...);
        return _writeLine(values);
    }
};

#endif  // CSV_H
