#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include <QString>

#include "base_operation.h"
#include "file_operation_global.h"

/**
 * @brief The FileOperation class
 folder path may end up with or without /, this should be worried by this class but not user
 */
class FILE_OPERATION_EXPORT FileOperation : public BaseOperation
{
public:
    FileOperation();
    virtual ~FileOperation();

    virtual bool Exists(const QString& file) const override;
    virtual bool CopyToFolder(const QString& file, const QString& path) const override;
    virtual bool CopyAs(const QString& file, const QString& new_file) const override;
    virtual bool CutToFolder(const QString& file, const QString& path) const override;
    virtual bool CutAs(const QString& file, const QString& new_file) const override;
    virtual bool Delete(const QString& file) const override;
    virtual bool Rename(const QString& file, const QString& new_file_name) const override;
};

#endif  // FILE_OPERATION_H
