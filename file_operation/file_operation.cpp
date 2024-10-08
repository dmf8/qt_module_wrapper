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
    QString reg_name = AbsoluteRegularPath(new_file);
    QString split_folder = FolderWithin(reg_name);
    QString split_name = EndName(reg_name);

    PathOperation po;
    if (!po.ForcePathExistance(split_folder)) return false;
    if (!Exists(file)) return false;
    if (IsSame(file, reg_name)) {
        qDebug() << __FUNCTION__ << "same";
        return true;
    }

    if (!Delete(reg_name)) return false;
    return QFile::copy(file, reg_name);
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
    // check
    if (!Exists(file)) return false;
    if (IsSame(file, new_file)) {
        return true;  // never delete self
    } else {
        // copy and delete
        if (!CopyAs(file, new_file)) return false;
        return Delete(file);
    }
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
