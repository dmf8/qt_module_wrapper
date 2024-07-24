#ifndef STATISTICS_H
#define STATISTICS_H

#include <QPointF>
#include <QVector>

#include "data_handler_global.h"

class DATA_HANDLER_EXPORT Statistics
{
public:
    Statistics();

    static double Max(const QVector<double>&data,int *pos=nullptr);
    static int MaxY(const QVector<QPointF>&data);
    static double Min(const QVector<double>&data,int *pos=nullptr);
    static int MinY(const QVector<QPointF>&data);
    static double Sum(const QVector<double>&data);
    static double Average(const QVector<double>&data);
    static double StandardDeviation(const QVector<double>&data);
    static double SampleStandardDeviation(const QVector<double>&data);
};

#endif // STATISTICS_H
