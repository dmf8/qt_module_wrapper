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
    bool GetObjInt(const QJsonObject &obj, const QString &key, int &val);
    bool GetObjDouble(const QJsonObject &obj, const QString &key, double &val);
    bool GetObjBool(const QJsonObject &obj, const QString &key, bool &val);
    bool GetObjString(const QJsonObject &obj, const QString &key, QString &val);
    bool GetObjObj(const QJsonObject &obj, const QString &key, QJsonObject &val);
    bool GetObjArray(const QJsonObject &obj, const QString &key, QJsonArray &val);

    // write
    bool SaveDocument(const QString &file, const QJsonDocument &doc);
    bool SaveObject(const QString &file, const QJsonObject &obj);
    bool SaveArray(const QString &file, const QJsonArray &arr);
};

#endif  // JSON_HANDLER_H
