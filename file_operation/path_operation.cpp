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
    QString reg = AbsoluteRegularPath(path);
    if (Exists(reg)) return true;
    return QDir().mkpath(reg);
}

bool PathOperation::CopyToFolder(const QString &path, const QString &folder) const
{
    return false;
}

bool PathOperation::CopyAs(const QString &path, const QString &new_file) const
{
    return false;
}

bool PathOperation::CutToFolder(const QString &path, const QString &folder) const
{
    return false;
}

bool PathOperation::CutAs(const QString &path, const QString &new_file) const
{
    return false;
}

bool PathOperation::Delete(const QString &path) const
{
    if (!Exists(path)) return true;
    QDir dir(path);
    return dir.removeRecursively();
}

bool PathOperation::Rename(const QString &path, const QString &new_name) const
{
    if (!Exists(path)) return false;
    QString reg_new_name = EndName(new_name);
    if ("" == reg_new_name) return false;

    if (IsSame(EndName(path), reg_new_name)) return true;
    QString full_new_name = PathJoin(FolderWithin(path), reg_new_name);
    return QFile::rename(AbsoluteRegularPath(path), AbsoluteRegularPath(full_new_name));
}
