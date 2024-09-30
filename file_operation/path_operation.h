#ifndef PATH_OPERATION_H
#define PATH_OPERATION_H

#include "base_operation.h"
#include "file_operation_global.h"

class FILE_OPERATION_EXPORT PathOperation : public BaseOperation
{
public:
    PathOperation();
    virtual ~PathOperation();

    virtual bool Exists(const QString& path) const override;
    virtual QString PathJoin(const QString& p1, const QString& p2) const;
    virtual bool ForcePathExistance(const QString& path) const;
};

#endif  // PATH_OPERATION_H
