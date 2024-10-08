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
    virtual bool IsParent(const QString& parent, const QString& child) const;

    virtual bool CopyToFolder(const QString& src_path, const QString& dst_folder) const override;
    virtual bool CopyAs(const QString& src_path, const QString& dst_path) const override;  // no nest
    virtual bool CutToFolder(const QString& src_path, const QString& dst_folder) const override;
    virtual bool CutAs(const QString& src_path, const QString& dst_path) const override;
    virtual bool Delete(const QString& path) const override;
    virtual bool Rename(const QString& path, const QString& new_name) const override;
};

#endif  // PATH_OPERATION_H
