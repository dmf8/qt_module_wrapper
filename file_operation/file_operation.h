#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include <QString>

#include "file_operation_global.h"

class FILE_OPERATION_EXPORT FileOperation
{
public:
    FileOperation();

    // path
    bool ForcePathExistance(const QString& path) const;
    QString PathJoin(const QString& p1, const QString& p2) const;

    // file
    bool FileExistance(const QString& file) const;
    QString AbsCleanFilePath(const QString& file) const;
    bool FileCopy(const QString& file, const QString& path) const;
    bool FileCut(const QString& file, const QString& path) const;
    bool FileDelete(const QString& file) const;
};

#endif  // FILE_OPERATION_H
