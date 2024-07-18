#ifndef WORK_H
#define WORK_H

#include <QObject>
#include <QString>

class Work : public QObject
{
    Q_OBJECT
public:
    explicit Work(QObject *parent = nullptr);

signals:

public slots:
    void OnStartGen(const QString &root_path_url,
                    const QString &module_file_url);
    void Test();

private:
    void CreatePri(const QString &pro_file);
    void ModifyPro(const QString &pro_file);
    void AppendList(const QString &pro_file, const QString &root_pro);
};

#endif  // WORK_H
