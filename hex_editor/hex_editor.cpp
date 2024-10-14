#include "hex_editor.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>

HexEditor::HexEditor()
    : file(nullptr)
{
}

HexEditor::~HexEditor()
{
    Close();
}

bool HexEditor::SetFile(const QString &path)
{
    return Open(path);
}

bool HexEditor::Append(const char *arr, int len)
{
    if (!file) return false;

    file->seek(file->size());
    return file->write(arr, len);
}

bool HexEditor::Append(const QByteArray &data)
{
    return Append(data.data(), data.size());
}

bool HexEditor::Insert(const QByteArray &data, int pos)
{
    if (!file) return false;

    if (file->size() < pos)
        if (!file->resize(pos)) return false;

    if (pos < 0) pos = file->size();

    if (!ReadAll()) return false;
    QByteArray new_data = all_data.insert(pos, data);
    return WriteAll(new_data);
}

bool HexEditor::Replace(const QByteArray &data, int pos)
{
    if (!file) return false;

    if (pos < 0) pos = file->size();
    if (pos > file->size()) file->resize(pos);
    if (!file->seek(pos)) return false;

    return file->write(data.data(), data.size());
}

bool HexEditor::Delete(int pos, int len)
{
    if (pos < 0) return false;
    if (pos > file->size()) return false;

    if (len < 0) len = file->size() - pos;

    if (!ReadAll()) return false;
    QByteArray new_data = all_data.remove(pos, len);
    return WriteAll(new_data);
}

bool HexEditor::Truncate()
{
    if (!file) return false;
    return file->resize(0);
}

bool HexEditor::ReadAll()
{
    if (!file->seek(0)) return false;
    all_data = file->readAll();
    qDebug() << __FUNCTION__ << all_data.toHex(' ');
    return true;
}

bool HexEditor::Open(const QString &path)
{
    Close();
    file = new QFile(path);
    return file->open(QFile::ReadWrite);
}

bool HexEditor::WriteAll(const QByteArray &data)
{
    if (!Truncate()) return false;
    return Append(data);
}

// bool HexEditor::Seek(int pos)
//{
//    if (pos < 0) pos = file->size();
//    if (pos > file->size()) pos = file->size();

//    return file->seek(pos);
//}

void HexEditor::Close()
{
    if (file) {
        file->close();
        delete file;
        file = nullptr;
    }
}
