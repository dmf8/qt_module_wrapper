#include "csv_editor.h"

#include "random_text_stream.h"

CsvEditor::CsvEditor()
    : rows(0)
    , columns(0)
    , table(new RandomTextStream)
{
}

CsvEditor::CsvEditor(int rows, int columns)
    : rows(rows)
    , columns(columns)
    , table(new RandomTextStream)
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
}

void CsvEditor::setFile(QFile *f)
{
    table->setFile(f);
}

void CsvEditor::write()
{
    table->write();
}

void CsvEditor::output() const
{
    table->output();
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

void CsvEditor::setRows(int rows)
{
    if (table->lineCount())
        ;

    this->rows = rows;
}

void CsvEditor::setColumns(int columns)
{
}

void CsvEditor::appendEmptyRow()
{
    table->appendLine(emptyRow(columns));
}

void CsvEditor::appendEmptyColumn()
{
    for (int i = 0; i < table->lineCount(); ++i) {
        QString origin = table->getLine(i);
        origin.append(",");
        table->setLine(i, origin);
    }
}

QString CsvEditor::emptyRow(int columns) const
{
    QString row;
    for (int i = 0; i < columns; ++i)
        row.append(",");
    return row;
}
