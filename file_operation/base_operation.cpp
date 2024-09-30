#include "base_operation.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

BaseOperation::BaseOperation()
{
}

BaseOperation::~BaseOperation()
{
}

bool BaseOperation::IsRelative(const QString &item) const
{
    QFileInfo info(item);
    return info.isRelative();
}

bool BaseOperation::IsAbsolute(const QString &item) const
{
    QFileInfo info(item);
    return info.isAbsolute();
}

bool BaseOperation::Exists(const QString &item) const
{
    QFileInfo info(AbsoluteRegularPath(item));
    return info.exists();
}

bool BaseOperation::IsSame(const QString &p1, const QString &p2) const
{
    return AbsoluteRegularPath(p1) == AbsoluteRegularPath(p2);
}

bool BaseOperation::Delete(const QString &item) const
{
    return false;
}

bool BaseOperation::CopyToFolder(const QString &item, const QString &path) const
{
    return false;
}

bool BaseOperation::CopyAs(const QString &item, const QString &new_item) const
{
    return false;
}

bool BaseOperation::CutToFolder(const QString &item, const QString &path) const
{
    return false;
}

bool BaseOperation::CutAs(const QString &item, const QString &path) const
{
    return false;
}

bool BaseOperation::Rename(const QString &item, const QString &new_name) const
{
    return false;
}

QString BaseOperation::CheckEmpty(const QString &item) const
{
    QString reg = item;
    if ("" == reg)  //
        reg = ".";
    return reg;
}

QString BaseOperation::CurrentPath() const
{
    return QCoreApplication::applicationDirPath();
}

QString BaseOperation::AbsoluteRegularPath(const QString &item) const
{
    QString reg = CheckEmpty(item);
    QFileInfo info(reg);
    QString info_abs = info.absoluteFilePath();
    info_abs = QDir::cleanPath(info_abs);     // remove / at end
    if (info_abs.contains("..")) return "/";  // special case like /..
    return info_abs;
}

QString BaseOperation::EndName(const QString &item) const
{
    if ("" == item) return "";
    QString end = QFileInfo(AbsoluteRegularPath(item)).fileName();
    if (".." == end) return "";  // special path like /..
    return end;
}

QString BaseOperation::FolderWithin(const QString &item) const
{
    QString abs_path = QFileInfo(AbsoluteRegularPath(item)).absolutePath();
    return AbsoluteRegularPath(abs_path);
}
