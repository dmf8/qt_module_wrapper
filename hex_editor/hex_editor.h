#ifndef HEX_EDITOR_H
#define HEX_EDITOR_H

#include <QByteArray>

#include "hex_editor_global.h"

class QFile;

class HEX_EDITOR_EXPORT HexEditor
{
public:
    HexEditor();
    ~HexEditor();

    bool SetFile(const QString& path);
    void Close();
    bool Append(const char* arr, int len);
    bool Append(const QByteArray& data);
    bool Delete(int pos, int len = -1);
    bool Truncate();
    bool Insert(const QByteArray& data, int pos = -1);
    bool Replace(const QByteArray& data, int pos);

private:
    bool ReadAll();
    bool Open(const QString& path);
    bool WriteAll(const QByteArray& data);
    //    bool Seek(int pos);

private:
    QFile* file;
    QByteArray all_data;
};

#endif  // HEX_EDITOR_H
