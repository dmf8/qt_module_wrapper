#ifndef BASE_OPERATION_H
#define BASE_OPERATION_H

#include "file_operation_global.h"

class FILE_OPERATION_EXPORT BaseOperation
{
public:
    BaseOperation();
    virtual ~BaseOperation();

    // query
    virtual QString CurrentPath() const;
    virtual QString AbsoluteRegularPath(const QString& item) const; /*
                                                                     * "/" or other absolute path without "/" at end
                                                                     * no "." and ".."
                                                                     */
    virtual QString EndName(const QString& item) const;
    virtual QString FolderWithin(const QString& item) const;

    // check
    virtual bool IsRelative(const QString& item) const;
    virtual bool IsAbsolute(const QString& item) const;
    virtual bool Exists(const QString& item) const;
    virtual bool IsSame(const QString& p1, const QString& p2) const;

    // operation
    virtual bool Delete(const QString& item) const;  // return true if file does not exist or is deleted
    virtual bool CopyToFolder(const QString& item, const QString& path) const;
    virtual bool CopyAs(const QString& item, const QString& new_item) const;
    virtual bool CutToFolder(const QString& item, const QString& path) const;
    virtual bool CutAs(const QString& item, const QString& path) const;
    virtual bool Rename(const QString& item, const QString& new_name) const;

protected:
    virtual QString CheckEmpty(const QString& item) const;  //""->"."
};

#endif  // BASE_OPERATION_H
