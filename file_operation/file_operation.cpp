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
    if (temp.size()) {
        if (temp[temp.size() - 1] != QChar('/')) temp.append("/");  // force to path style
    } else
        temp.append("./");

    QFileInfo p(temp);
    qDebug() << p.absolutePath();
    if (!p.isDir()) {
        QDir().mkpath(p.absolutePath());  // must be in path style, ie. end up with /
    }

    return p.isDir();
}

QString FileOperation::PathJoin(const QString &p1, const QString &p2) const
{
    QString ret = QString("%1/%2").arg(QDir().cleanPath(p1)).arg(QDir().cleanPath(p2));
    return QDir().cleanPath(ret);
}

bool FileOperation::FolderCopy(const QString &src_folder, const QString &dest_base_path) const
{
    if (!PathExists(src_folder)) return false;
    QString folder_name = EndName(src_folder);
    QString new_folder = PathJoin(dest_base_path, folder_name);
    if (QFileInfo(src_folder).absoluteFilePath() == QFileInfo(new_folder).absoluteFilePath()) return true;
    if (!ForcePathExistance(new_folder)) return false;

    QDir src_dir(src_folder);
    QFileInfoList file_list = src_dir.entryInfoList(QDir::Files);
    bool ret = true;
    for (const auto &file : file_list) {
        ret |= FileCopy(file.absoluteFilePath(), new_folder);
    }

    QFileInfoList dir_list = src_dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const auto &path : dir_list) {
        QString new_src = path.absoluteFilePath();
        ret |= FolderCopy(new_src, new_folder);
    }
    return ret;
}

bool FileOperation::FolderCut(const QString &src_folder, const QString &new_name) const
{
    if (!PathExists(src_folder)) return false;

    QString src_regular = GetRegularAbsoluteName(src_folder);
    QString new_regular = GetRegularAbsoluteName(new_name);
    if (src_regular == new_regular) return true;

    return QDir().rename(src_regular, new_regular);
}

bool FileOperation::FolderDelete(const QString &folder) const
{
    if (!PathExists(folder)) return true;
    QDir dir(folder);
    return dir.removeRecursively();
}

bool FileOperation::FolderRename(const QString &folder, const QString &new_name) const
{
    if (!PathExists(folder)) return false;

    QString base_path = Path(folder);
    QString new_name_temp;
    if (QDir(new_name).isAbsolute())
        new_name_temp = new_name;
    else
        new_name_temp = PathJoin(base_path, new_name);
    return FolderCut(folder, new_name_temp);
}

bool FileOperation::PathExists(const QString &path) const
{
    QFileInfo f(path);
    return f.isDir();
}

bool FileOperation::FileExists(const QString &file) const
{
    QFileInfo f(file);
    return f.isFile();
}

QString FileOperation::AbsCleanPath(const QString &item) const
{
    QFileInfo f(item);
    return f.absoluteFilePath();
}

QString FileOperation::EndName(const QString &item) const
{
    QString temp = GetRegularAbsoluteName(item);
    return QFileInfo(temp).fileName();
}

QString FileOperation::Path(const QString &item) const
{
    QString temp = GetRegularAbsoluteName(item);
    return QFileInfo(temp).absolutePath();
}

QString FileOperation::GetRegularAbsoluteName(const QString &item) const
{
    QString temp;
    if (item == "")
        temp = QFileInfo(".").absoluteFilePath();
    else
        temp = QFileInfo(item).absoluteFilePath();
    while (temp.size() && temp[temp.size() - 1] == QChar('/')) {
        temp = temp.left(temp.size() - 1);
    }

    return temp;
}

QString FileOperation::GetRegularAbsolutePathStyle(const QString &item) const
{
    return GetRegularAbsoluteName(item).append("/");
}

bool FileOperation::FileCopy(const QString &file, const QString &path) const
{
    QFileInfo f(file);
    if (!f.isFile()) return false;
    if (!ForcePathExistance(path)) return false;

    QString new_file_path = PathJoin(path, f.fileName());
    if (FileExists(new_file_path))
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
