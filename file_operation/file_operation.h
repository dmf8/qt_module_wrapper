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

    // path
    bool ForcePathExistance(const QString& path) const;
    //    QString PathJoin(const QString& p1, const QString& p2) const;  // without / at end even if p2 is a path
    bool FolderCopy(const QString& src_folder, const QString& dest_base_path) const;
    bool FolderCut(const QString& src_folder, const QString& new_name) const;
    bool FolderRename(const QString& folder,
                      const QString& new_name) const;  // new name is relative to old name but not current path
    bool FolderDelete(const QString& folder) const;
    bool PathExists(const QString& path) const;

    // file or path
    QString AbsCleanPath(const QString& item) const;  // path end up with /
    //    QString EndName(const QString& item) const;       // file or folder name
    QString Path(const QString& item) const;  // remove EndName

private:
    QString GetRegularAbsoluteName(const QString& item) const;  // /: ""; other: "xx", without / at end
    QString GetRegularAbsolutePathStyle(const QString& item) const;
};

#endif  // FILE_OPERATION_H
