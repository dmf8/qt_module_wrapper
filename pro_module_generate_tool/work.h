#ifndef WORK_H
#define WORK_H

#include <QObject>

class Work : public QObject
{
    Q_OBJECT
public:
    explicit Work(QObject *parent = nullptr);

signals:

};

#endif // WORK_H
