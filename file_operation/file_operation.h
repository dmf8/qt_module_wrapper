#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include <QString>

#include "file_operation_global.h"

class FILE_OPERATION_EXPORT FileOperation
{
public:
    FileOperation();

    // path
    bool ForcePathExistance(const QString& path);
};

#endif  // FILE_OPERATION_H
