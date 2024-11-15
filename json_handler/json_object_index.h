#ifndef JSON_OBJECT_INDEX_H
#define JSON_OBJECT_INDEX_H

#include <QJsonValue>
#include <QStringList>

#include "json_handler_global.h"

class QJsonObject;

class JSON_HANDLER_EXPORT JsonObjectIndex
{
public:
    JsonObjectIndex(QJsonObject* r = nullptr);

    void SetRoot(QJsonObject* r);
    bool GetNode(const QString& key, QJsonValue& value);
    bool AddNode(const QString& key, const QVariant& value);
    bool DeleteNode(const QString& key);

    //    template <class T>
    //    bool SetNode(const QString& key, const T& value);

    // private:
    QStringList SplitKey(const QString& key) const;

    struct NodeInfo {
        QJsonObject* parent = nullptr;
        QString key = "";
        QJsonValue value = QJsonValue();
    };

    bool GetParentObj(const QString& key, QJsonObject& parent);

    bool FindNode(const QString& key, NodeInfo& info);

    // private:
    QJsonObject* root;
};

#endif  // JSON_OBJECT_INDEX_H
