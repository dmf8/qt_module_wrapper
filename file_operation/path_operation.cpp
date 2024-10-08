#include "path_operation.h"

#include <QDir>
#include <QFileInfo>

#include "file_operation.h"

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

bool PathOperation::IsParent(const QString &parent, const QString &child) const
{
    QString p = AbsoluteRegularPath(parent);
    QString c = AbsoluteRegularPath(child);
    return c.contains(p) && c.size() > p.size();
}

bool PathOperation::CopyToFolder(const QString &src_path, const QString &dst_folder) const
{
    QString src_end_name = EndName(src_path);
    QString dest_path = AbsoluteRegularPath(dst_folder);
    QString new_folder_abs = PathOperation().PathJoin(dest_path, src_end_name);
    return CopyAs(src_path, new_folder_abs);
}

bool PathOperation::CopyAs(const QString &src_path, const QString &dst_path) const
{
    // check
    if (!Exists(src_path)) return false;
    if (IsSame(src_path, dst_path)) return true;
    if (IsParent(dst_path, src_path)) return false;
    if (IsParent(src_path, dst_path)) return false;

    // clear
    if (Exists(dst_path))
        if (!Delete(dst_path)) return false;

    // new folder
    if (!ForcePathExistance(dst_path)) return false;

    // copy files
    QDir src_dir(src_path);
    QFileInfoList file_list = src_dir.entryInfoList(QDir::Files);
    bool ret = true;
    FileOperation fo;
    for (const auto &file : file_list)
        ret |= fo.CopyToFolder(file.absoluteFilePath(), dst_path);

    // copy sub folders
    QFileInfoList dir_list = src_dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const auto &path : dir_list) {
        QString sub_name = EndName(path.absoluteFilePath());
        QString sub_dst = PathJoin(dst_path, sub_name);
        ret |= CopyAs(path.absoluteFilePath(), sub_dst);
    }
    return ret;
}

bool PathOperation::CutToFolder(const QString &src_path, const QString &dst_folder) const
{
    QString src_end_name = EndName(src_path);
    QString dest_path = AbsoluteRegularPath(dst_folder);
    QString new_folder_abs = PathOperation().PathJoin(dest_path, src_end_name);
    return CutAs(src_path, new_folder_abs);
}

bool PathOperation::CutAs(const QString &src_path, const QString &dst_path) const
{
    if (IsSame(src_path, dst_path))
        return true;
    else {
        if (!CopyAs(src_path, dst_path)) return false;
        return Delete(src_path);
    }
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
