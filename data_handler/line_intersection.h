#ifndef LINE_INTERSECTION_H
#define LINE_INTERSECTION_H

#include <QPointF>
#include "data_handler_global.h"


class DATA_HANDLER_EXPORT LineIntersection
{
public:
    LineIntersection();

    bool SolveY(const QPointF&p1,const QPointF&p2,double x,double &y) const;
    bool SolveX(const QPointF&p1,const QPointF&p2,double y,double &x) const;
};

#endif // LINE_INTERSECTION_H
