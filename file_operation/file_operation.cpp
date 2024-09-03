#include "file_operation.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>

FileOperation::FileOperation()
{
}

bool FileOperation::ForcePathExistance(const QString &path)
{
    QString temp = path;
    if (temp[temp.size() - 1] != QChar('/')) temp.append("/");

    QFileInfo p(temp);
    if (!p.isDir()) {
        //        qDebug() << __FUNCTION__ << p.absolutePath() << "not found";
        QDir().mkpath(p.absolutePath());
    }

    return p.isDir();
}
