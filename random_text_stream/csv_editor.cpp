#include "csv_editor.h"

#include <QDebug>

#include "random_text_stream.h"

CsvEditor::CsvEditor()
    : rows(0)
    , columns(0)
    , table(new RandomTextStream)
    , f(nullptr)
{
}

CsvEditor::CsvEditor(int rows, int columns)
    : rows(rows)
    , columns(columns)
    , table(new RandomTextStream)
    , f(nullptr)
{
    for (int i = 0; i < rows; ++i)
        appendEmptyRow();
}

CsvEditor::~CsvEditor()
{
    if (table) {
        delete table;
        table = nullptr;
    }
    ClearFile();
}

bool CsvEditor::openNew(const QString &file)
{
    ClearFile();
    f = new QFile(file);
    return f->open(QFile::WriteOnly | QFile::Truncate);
}

bool CsvEditor::openExisting(const QString &file)
{
    ClearFile();
    f = new QFile(file);
    if (!f->open(QFile::ReadWrite)) return false;

    ClearContent();
    QByteArray line;
    for (line = f->readLine(); line.size(); line = f->readLine()) {
        QStringList line_items = splitElement(QString(line));
        appendRow(line_items);
        qDebug() << QString(line);
    }
    qDebug() << rowCount() << columnCount();
    return true;
}

void CsvEditor::save()
{
    table->write();
}

int CsvEditor::rowCount() const
{
    return rows;
}

int CsvEditor::columnCount() const
{
    return columns;
}

void CsvEditor::output() const
{
    table->output();
}

QStringList CsvEditor::getRow(int id) const
{
    if (id < 0 || id + 1 > rows)
        return {};
    else
        return splitElement(table->getLine(id));
}

QStringList CsvEditor::getColumn(int id) const
{
    if (id < 0 || id + 1 > columns)
        return {};
    else {
        QStringList list;
        for (int i = 0; i < rows; ++i) {
            QStringList row_items = splitElement(table->getLine(i));
            list.append(row_items[id]);
        }
        return list;
    }
}

void CsvEditor::appendRow(const QStringList &value)
{
    QStringList checked_row = value;
    int new_column_count = value.size();
    if (new_column_count > columns)
        setColumnCount(new_column_count);
    else
        resizeList(checked_row, columns);

    table->appendLine(joinElement(checked_row));
    rows = rows + 1;
}

void CsvEditor::appendColumn(const QStringList &value)
{
    QStringList checked_column = value;
    int new_row_count = value.size();
    if (new_row_count > rows)
        setRowCount(new_row_count);
    else
        resizeList(checked_column, rows);

    for (int i = 0; i < rows; ++i) {
        QString line = table->getLine(i);
        line.append(checked_column[i]).append(",");
        table->setLine(i, line);
    }
    columns = columns + 1;
}

void CsvEditor::setRow(int id, const QStringList &value)
{
    int id1 = id + 1;
    if (id1 > rows) setRowCount(id1);
    QStringList checked_row = value;
    int new_column_count = value.size();
    if (new_column_count > columns)
        setColumnCount(new_column_count);
    else
        resizeList(checked_row, columns);

    table->setLine(id, joinElement(checked_row));
}

void CsvEditor::setColumn(int id, const QStringList &value)
{
    int id1 = id + 1;
    if (id1 > columns) setColumnCount(id1);
    QStringList checked_column = value;
    int new_row_count = value.size();
    if (new_row_count > rows)
        setRowCount(new_row_count);
    else
        resizeList(checked_column, rows);

    for (int i = 0; i < rows; ++i) {
        QString line = table->getLine(i);
        QStringList line_items = splitElement(line);
        line_items[id] = checked_column[i];
        table->setLine(i, joinElement(line_items));
    }
}

void CsvEditor::setElement(int row, int column, const QString &value)
{
    if (row + 1 > rows) setRowCount(row + 1);
    if (column + 1 > columns) setColumnCount(column + 1);

    QString line = table->getLine(row);
    QStringList line_items = splitElement(line);
    line_items[column] = value;
    table->setLine(row, joinElement(line_items));
}

QStringList CsvEditor::splitElement(const QString &line) const
{
    QStringList list = line.split(",");
    if (list.size()) list.removeLast();
    return list;
}

QString CsvEditor::joinElement(const QStringList &elements) const
{
    QString result = "";
    for (const QString &e : elements)
        result.append(e).append(",");
    return result;
}

void CsvEditor::resizeList(QStringList &list, int count) const
{
    int list_size = list.size();
    if (list_size > count)
        for (int i = 0; i < list_size - count; ++i)
            list.removeLast();
    else
        for (int i = 0; i < count - list_size; ++i)
            list.append("");
}

void CsvEditor::setRowCount(int rows)
{
    if (this->rows > rows) {
        for (int i = this->rows - 1; i >= rows; i--)
            table->removeLine(i);
    } else
        appendEmptyRows(rows - this->rows);

    this->rows = rows;
}

void CsvEditor::setColumnCount(int columns)
{
    if (this->columns > columns) {
        for (int i = 0; i < rows; ++i) {
            QString origin = table->getLine(i);
            QStringList list = splitElement(origin);
            resizeList(list, columns);
            QString new_line = joinElement(list);
            table->setLine(i, new_line);
        }
    } else
        appendEmptyColumns(columns - this->columns);

    this->columns = columns;
}

void CsvEditor::appendEmptyRow()
{
    table->appendLine(generateEmptyRow(columns));
}

void CsvEditor::appendEmptyRows(int count)
{
    for (int i = 0; i < count; ++i)
        appendEmptyRow();
}

void CsvEditor::appendEmptyColumn()
{
    for (int i = 0; i < table->lineCount(); ++i) {
        QString origin = table->getLine(i);
        origin.append(",");
        table->setLine(i, origin);
    }
}

void CsvEditor::appendEmptyColumns(int count)
{
    for (int i = 0; i < count; ++i)
        appendEmptyColumn();
}

QString CsvEditor::generateEmptyRow(int columns) const
{
    QString row;
    for (int i = 0; i < columns; ++i)
        row.append(",");
    return row;
}

void CsvEditor::ClearFile()
{
    if (f) {
        f->close();
        delete f;
        f = nullptr;
    }
}

void CsvEditor::ClearContent()
{
    setColumnCount(0);
    setRowCount(0);
}