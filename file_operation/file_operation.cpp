#include "file_operation.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>

FileOperation::FileOperation()
{
}

bool FileOperation::ForcePathExistance(const QString &path) const
{
    QString temp = path;
    if (temp[temp.size() - 1] != QChar('/')) temp.append("/");  // force to path style

    QFileInfo p(temp);
    if (!p.isDir()) {
        QDir().mkpath(p.absolutePath());
    }

    return p.isDir();
}

QString FileOperation::PathJoin(const QString &p1, const QString &p2) const
{
    QString ret = QString("%1/%2").arg(QDir().cleanPath(p1)).arg(QDir().cleanPath(p2));
    return QDir().cleanPath(ret);
}

bool FileOperation::FileExistance(const QString &file) const
{
    QFileInfo f(file);
    return f.isFile();
}

QString FileOperation::AbsCleanFilePath(const QString &file) const
{
    QFileInfo f(file);
    return f.absoluteFilePath();
}

bool FileOperation::FileCopy(const QString &file, const QString &path) const
{
    QFileInfo f(file);
    if (!f.isFile()) return false;
    if (!ForcePathExistance(path)) return false;

    QString new_file_path = PathJoin(path, f.fileName());
    if (FileExistance(new_file_path))
        if (!FileDelete(new_file_path)) return false;

    return QFile::copy(file, new_file_path);
}

bool FileOperation::FileCut(const QString &file, const QString &path) const
{
    if (!FileCopy(file, path)) return false;
    return FileDelete(file);
}

bool FileOperation::FileDelete(const QString &file) const
{
    QFileInfo f(file);
    if (f.isDir()) return false;
    if (!f.isFile()) return true;

    return QFile::remove(f.absoluteFilePath());
}
