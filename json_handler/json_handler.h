#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include "json_handler_global.h"

class QJsonObject;
class QJsonValue;
class QJsonArray;
class QJsonDocument;

class JSON_HANDLER_EXPORT JsonHandler
{
public:
    JsonHandler();

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
};

#endif // JSON_HANDLER_H
