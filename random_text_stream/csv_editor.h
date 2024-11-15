#ifndef CSV_EDITOR_H
#define CSV_EDITOR_H

#include <QFile>

#include "random_text_stream_global.h"

class RandomTextStream;
class RANDOM_TEXT_STREAM_EXPORT CsvEditor
{
public:
    CsvEditor();
    CsvEditor(int rows, int columns);
    ~CsvEditor();

    // io
    void setFile(QFile* f);  //
    void write();            //

    // status
    int rowCount() const;     //
    int columnCount() const;  //
    void output() const;      //

    // read
    QStringList getRow(int id) const;
    QStringList getColumn(int id) const;

    // write
    void appendRow(const QStringList& value);
    void appendColumn(const QStringList& value);
    void setRow(int id, const QStringList& value);
    void setColumn(int id, const QStringList& value);
    void setElement(int row, int column, const QString& value);

    // private:
    QStringList splitElement(const QString& line) const;     //
    QString joinElement(const QStringList& elements) const;  //
    int vectorCount(const QStringList& vector) const;
    void setRows(int rows);
    void setColumns(int columns);
    void appendEmptyRow();                        //
    void appendEmptyColumn();                     //
    QString generateEmptyRow(int columns) const;  //

    // private:
    int rows;
    int columns;
    RandomTextStream* table;
};

#endif  // CSV_EDITOR_H
