#include "json_object_index.h"

#include "json_handler.h"

JsonObjectIndex::JsonObjectIndex(QJsonObject *r)
    : root(r)
{
}

void JsonObjectIndex::SetRoot(QJsonObject *r)
{
    root = r;
}

bool JsonObjectIndex::GetNode(const QString &key, QJsonValue &value)
{
    QStringList keys = SplitKey(key);

    if (keys.size() == 0) {
        value = *root;
        return true;
    }

    QJsonObject parent;
    if (!GetParentObj(key, parent)) return false;

    value = parent[keys.last()];
    return true;
}

bool JsonObjectIndex::AddNode(const QString &key, const QVariant &value)
{
    QStringList keys = SplitKey(key);
    if (keys.size() == 0) return false;
}

bool JsonObjectIndex::DeleteNode(const QString &key)
{
    QStringList keys = SplitKey(key);

    if (keys.size() == 0) {
        *root = QJsonObject();
        return true;
    }
}

QStringList JsonObjectIndex::SplitKey(const QString &key) const
{
    return key.split("/", Qt::SkipEmptyParts);
}

bool JsonObjectIndex::GetParentObj(const QString &key, QJsonObject &parent)
{
    QStringList keys = SplitKey(key);
    if (keys.size() == 0) return false;

    parent = *root;
    JsonHandler jh;
    for (int i = 0; i < keys.size(); ++i) {
        if (!parent.contains(keys[i])) return false;
        if (i == keys.size() - 1) return true;
        if (!jh.GetObj(parent, keys[i], parent)) return false;
    }
    return true;
}

bool JsonObjectIndex::FindNode(const QString &key, JsonObjectIndex::NodeInfo &info)
{
    QStringList keys = SplitKey(key);
    info = NodeInfo();

    QJsonObject *p = root;
    JsonHandler jh;

    for (int i = 0; i < keys.size(); ++i) {
        info.parent = p;
        info.key = keys[i];
        if (!jh.GetObject(*p, keys[i], info.value))  //
            return false;

        if (i + 1 < keys.size()) {
            if (!info.value.isObject()) return false;
            (*p)[keys[i]];
            p;
        }
    }

    QJsonValue value = *root;
    for (int i = 0; i < keys.size(); ++i) {
        if (!value.isObject())  //
            return false;

        QJsonObject o = value.toObject();
        if (!jh.GetObject(o, keys[i], value))  //
            return false;
    }
    return true;
}

// template <class T>
// bool JsonObjectIndex::SetNode<T>(const QString &key, const JsonObjectIndex::T &value)
//{
//}
