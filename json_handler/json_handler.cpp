#include "json_handler.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

JsonHandler::JsonHandler()
{
}

bool JsonHandler::GetDocument(const QString &file_name, QJsonDocument &doc)
{
    QFile f(file_name);
    bool ret = f.open(QIODevice::ReadOnly);
    QByteArray data;
    if (ret) data = f.readAll();
    f.close();

    doc = QJsonDocument::fromJson(data);

    return ret;
}

bool JsonHandler::GetRootObj(const QJsonDocument &doc, QJsonObject &obj)
{
    if (!doc.isObject()) return false;

    obj = doc.object();
    return true;
}

bool JsonHandler::GetRootArray(const QJsonDocument &doc, QJsonArray &arr)
{
    if (!doc.isArray()) return false;

    arr = doc.array();
    return true;
}

bool JsonHandler::GetObject(const QJsonObject &obj, const QString &key, QJsonValue &val)
{
    val = obj[key];
    return !val.isUndefined();
}

bool JsonHandler::GetObjInt(const QJsonObject &obj, const QString &key, int &val)
{
    QJsonValue temp;
    if (!GetObject(obj, key, temp)) return false;
    if (!temp.isDouble()) return false;

    double d = temp.toDouble();
    if (0 != d - (int)d) return false;
    val = d;
    return true;
}

bool JsonHandler::GetObjDouble(const QJsonObject &obj, const QString &key, double &val)
{
    QJsonValue temp;
    if (!GetObject(obj, key, temp)) return false;
    if (!temp.isDouble()) return false;

    val = temp.toDouble();
    return true;
}

bool JsonHandler::GetObjBool(const QJsonObject &obj, const QString &key, bool &val)
{
    QJsonValue temp;
    if (!GetObject(obj, key, temp)) return false;
    if (!temp.isBool()) return false;

    val = temp.toBool();
    return true;
}

bool JsonHandler::GetObjString(const QJsonObject &obj, const QString &key, QString &val)
{
    QJsonValue temp;
    if (!GetObject(obj, key, temp)) return false;
    if (!temp.isString()) return false;

    val = temp.toString();
    return true;
}

bool JsonHandler::GetObjObj(const QJsonObject &obj, const QString &key, QJsonObject &val)
{
    QJsonValue temp;
    if (!GetObject(obj, key, temp)) return false;
    if (!temp.isObject()) return false;

    val = temp.toObject();
    return true;
}

bool JsonHandler::GetObjArray(const QJsonObject &obj, const QString &key, QJsonArray &val)
{
    QJsonValue temp;
    if (!GetObject(obj, key, temp)) return false;
    if (!temp.isArray()) return false;

    val = temp.toArray();
    return true;
}

bool JsonHandler::Save(const QString &file, const QJsonDocument &doc)
{
    QFile f(file);
    if (!f.open(QFile::WriteOnly)) return false;

    QByteArray raw = doc.toJson();
    f.write(raw);
    f.close();
    return true;
}

bool JsonHandler::Save(const QString &file, const QJsonObject &obj)
{
    QJsonDocument doc(obj);
    return Save(file, doc);
}

bool JsonHandler::Save(const QString &file, const QJsonArray &arr)
{
    QJsonDocument doc(arr);
    return Save(file, doc);
}
