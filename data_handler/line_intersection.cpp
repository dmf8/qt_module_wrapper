#include "line_intersection.h"

LineIntersection::LineIntersection()
{

}

bool LineIntersection::SolveY(const QPointF &p1, const QPointF &p2, double x, double &y) const
{
    if (p1==p2)
    {
        if (p1.x()!=x)
            return false;
        y=p1.y();
        return true;
    }

    QPointF left,right;
    if (p1.x()<p2.x())
    {
        left=p1;
        right=p2;
    }else{
        left=p2;
        right=p1;
    }

    if (x<left.x()||x>right.x())
        return false;

    if (x==left.x())
        y=left.y();
    else
        y=(x-left.x())/(right.x()-left.x())*(right.y()-left.y())+left.y();
    return true;
}

bool LineIntersection::SolveX(const QPointF &p1, const QPointF &p2, double y, double &x) const
{
    if (p1==p2)
    {
        if (p1.y()!=y)
            return false;
        x=p1.x();
        return true;
    }

    QPointF bottom,top;
    if (p1.y()<p2.y())
    {
        bottom=p1;
        top=p2;
    }else{
        bottom=p2;
        top=p1;
    }

    if (y<bottom.y()||y>top.y())
        return false;

    if (y==bottom.y())
        x=bottom.x();
    else
        x=(y-bottom.y())/(top.y()-bottom.y())*(top.x()-bottom.x())+bottom.x();
    return true;
}
