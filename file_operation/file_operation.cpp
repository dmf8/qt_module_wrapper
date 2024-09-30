#include "file_operation.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>

#include "path_operation.h"

FileOperation::FileOperation()
{
}

FileOperation::~FileOperation()
{
}

bool FileOperation::Exists(const QString &file) const
{
    if (BaseOperation::Exists(file)) {
        QFileInfo info(file);
        return info.isFile();
    } else
        return false;
}

bool FileOperation::CopyToFolder(const QString &file, const QString &path) const
{
    PathOperation po;
    if (!po.ForcePathExistance(path)) return false;
    if (!Exists(file)) return false;
    if (IsSame(FolderWithin(file), path)) {
        qDebug() << __FUNCTION__ << "same";
        return true;
    }

    QString new_file_name = PathOperation().PathJoin(AbsoluteRegularPath(path), EndName(file));
    if (!Delete(new_file_name)) return false;
    return QFile::copy(file, new_file_name);
}

bool FileOperation::CopyAs(const QString &file, const QString &new_file) const
{
    QString split_folder = FolderWithin(new_file);
    QString split_name = EndName(new_file);

    if (!Exists(file)) return false;  // no file
    if (IsSame(file, new_file)) {
        qDebug() << __FUNCTION__ << "same";
        return true;  // same file
    }
    if (!Delete(new_file)) return false;  // clear error

    if (!CopyToFolder(file, split_folder)) return false;
    QString temp_name = PathOperation().PathJoin(  //
        split_folder,                              //
        EndName(file));

    return Rename(temp_name, split_name);
}

bool FileOperation::CutToFolder(const QString &file, const QString &path) const
{
    QString new_name = PathOperation().PathJoin(  //
        AbsoluteRegularPath(path),                //
        EndName(file));
    return CutAs(file, new_name);
}

bool FileOperation::CutAs(const QString &file, const QString &new_file) const
{
    if (IsSame(file, new_file)) return true;
    if (!CopyAs(file, new_file)) return false;
    return Delete(file);
}

bool FileOperation::Delete(const QString &file) const
{
    if (!BaseOperation::Exists(file)) return true;
    if (!Exists(file)) return false;  // item is not file

    return QFile::remove(AbsoluteRegularPath(file));
}

bool FileOperation::Rename(const QString &file, const QString &new_file_name) const
{
    if (!Exists(file)) return false;
    QString new_abs_name = PathOperation().PathJoin(  //
        FolderWithin(file),                           //
        EndName(new_file_name));

    if (AbsoluteRegularPath(file) == AbsoluteRegularPath(new_abs_name)) return true;
    return QFile::rename(AbsoluteRegularPath(file), new_abs_name);
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

// QString FileOperation::PathJoin(const QString &p1, const QString &p2) const
//{
//    QString ret = QString("%1/%2").arg(QDir().cleanPath(p1)).arg(QDir().cleanPath(p2));
//    return QDir().cleanPath(ret);
//}

bool FileOperation::FolderCopy(const QString &src_folder, const QString &dest_base_path) const
{
    //    if (!PathExists(src_folder)) return false;
    //    QString folder_name = EndName(src_folder);
    //    QString new_folder = PathOperation().PathJoin(dest_base_path, folder_name);
    //    if (QFileInfo(src_folder).absoluteFilePath() == QFileInfo(new_folder).absoluteFilePath()) return true;
    //    if (!ForcePathExistance(new_folder)) return false;

    //    QDir src_dir(src_folder);
    //    QFileInfoList file_list = src_dir.entryInfoList(QDir::Files);
    //    bool ret = true;
    //    for (const auto &file : file_list) {
    //        ret |= FileCopyToDestFolder(file.absoluteFilePath(), new_folder);
    //    }

    //    QFileInfoList dir_list = src_dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    //    for (const auto &path : dir_list) {
    //        QString new_src = path.absoluteFilePath();
    //        ret |= FolderCopy(new_src, new_folder);
    //    }
    //    return ret;
    return false;
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
        new_name_temp = PathOperation().PathJoin(base_path, new_name);
    return FolderCut(folder, new_name_temp);
}

bool FileOperation::PathExists(const QString &path) const
{
    QFileInfo f(path);
    return f.isDir();
}

QString FileOperation::AbsCleanPath(const QString &item) const
{
    QFileInfo f(item);
    return f.absoluteFilePath();
}

// QString FileOperation::EndName(const QString &item) const
//{
//    QString temp = GetRegularAbsoluteName(item);
//    return QFileInfo(temp).fileName();
//}

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
