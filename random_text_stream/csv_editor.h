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
    bool openNew(const QString& file);
    bool openExisting(const QString& file);
    void save();  //

    // status
    int rowCount() const;     //
    int columnCount() const;  //
    void output() const;      //

    // read
    QStringList getRow(int id) const;     //
    QStringList getColumn(int id) const;  //

    // write
    void appendRow(const QStringList& value);                    //
    void appendColumn(const QStringList& value);                 //
    void setRow(int id, const QStringList& value);               //
    void setColumn(int id, const QStringList& value);            //
    void setElement(int row, int column, const QString& value);  //

private:
    QStringList splitElement(const QString& line) const;     //
    QString joinElement(const QStringList& elements) const;  //
    void resizeList(QStringList& list, int count) const;     //
    void setRowCount(int rows);                              //
    void setColumnCount(int columns);                        //
    void appendEmptyRow();                                   //
    void appendEmptyRows(int count);                         //
    void appendEmptyColumn();                                //
    void appendEmptyColumns(int count);                      //
    QString generateEmptyRow(int columns) const;             //
    void ClearFile();
    void ClearContent();

    // private:
    int rows;
    int columns;
    RandomTextStream* table;
    QFile* f;
};

#endif  // CSV_EDITOR_H
