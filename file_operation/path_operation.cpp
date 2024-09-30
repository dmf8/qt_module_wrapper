#include "path_operation.h"

#include <QDir>
#include <QFileInfo>

PathOperation::PathOperation()
{
}

PathOperation::~PathOperation()
{
}

bool PathOperation::Exists(const QString &path) const
{
    if (BaseOperation::Exists(path)) {
        QFileInfo info(path);
        return info.isDir();
    } else
        return false;
}

QString PathOperation::PathJoin(const QString &p1, const QString &p2) const
{
    QString p1_check = CheckEmpty(p1);
    QString ret = QString("%1/%2").arg(QDir().cleanPath(p1_check)).arg(QDir().cleanPath(p2));
    return QDir().cleanPath(ret);
}

bool PathOperation::ForcePathExistance(const QString &path) const
{
    QString reg = AbsoluteRegular(path);
    if (Exists(reg)) return true;
    return QDir().mkpath(reg);
}
