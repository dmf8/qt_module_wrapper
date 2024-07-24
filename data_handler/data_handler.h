#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "data_handler_global.h"

#include <QPointF>
#include <QVector>

class DATA_HANDLER_EXPORT DataHandler
{
public:
    DataHandler();


    QVector<QPointF> AverageFilter(const QVector<QPointF>&data, int half_window);
    QVector<QPointF> DeriveCenter(const QVector<QPointF>& data);
    QVector<QPointF> DeriveBackward(const QVector<QPointF>& data);
    QVector<QPointF> DeriveForward(const QVector<QPointF>& data);
    QVector<QPointF> ReverseY(const QVector<QPointF>& data);

private:
    double GetAverage(const QVector<QPointF> &data, int start, int len) const;
    QVector<QPointF> DeriveSpecialCase(const QVector<QPointF>& data);

};

#endif // DATA_HANDLER_H
