#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "json_handler_global.h"

class JSON_HANDLER_EXPORT JsonHandler
{
public:
    JsonHandler();

    // read
    bool GetDocument(const QString &file_name, QJsonDocument &doc);
    bool GetRootObj(const QJsonDocument &doc, QJsonObject &obj);
    bool GetRootArray(const QJsonDocument &doc, QJsonArray &arr);

    bool GetObject(const QJsonObject &obj, const QString &key, QJsonValue &val);
    bool GetInt(const QJsonObject &obj, const QString &key, int &val);
    bool GetDouble(const QJsonObject &obj, const QString &key, double &val);
    bool GetBool(const QJsonObject &obj, const QString &key, bool &val);
    bool GetString(const QJsonObject &obj, const QString &key, QString &val);
    bool GetObj(const QJsonObject &obj, const QString &key, QJsonObject &val);
    bool GetArr(const QJsonObject &obj, const QString &key, QJsonArray &val);

    // write
    bool Save(const QString &file, const QJsonDocument &doc);
    bool Save(const QString &file, const QJsonObject &obj);
    bool Save(const QString &file, const QJsonArray &arr);
};

#endif  // JSON_HANDLER_H
