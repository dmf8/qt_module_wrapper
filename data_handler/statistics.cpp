#include "statistics.h"

Statistics::Statistics()
{

}

double Statistics::Max(const QVector<double> &data, int *pos)
{
    if (!data.size()) {
        if (pos) *pos=-1;
        return 0;
    }

    double ret=data[0];
    if (pos) *pos=0;

    for (int i=1;i<data.size();++i)
    {
        if (data[i]>ret) {
            if (pos) *pos=i;
            ret=data[i];
        }
    }
    return ret;
}

int Statistics::MaxY(const QVector<QPointF> &data)
{
    if (!data.size()) return -1;

    double max=data[0].y();
    int ret=0;

    for (int i=1;i<data.size();++i)
    {
        if (data[i].y()>max) {
            ret=i;
            max=data[i].y();
        }
    }
    return ret;
}

double Statistics::Min(const QVector<double> &data, int *pos)
{
    if (!data.size()) {
        if (pos) *pos=-1;
        return 0;
    }

    double ret=data[0];
    if (pos) *pos=0;

    for (int i=1;i<data.size();++i)
    {
        if (data[i]<ret) {
            if (pos) *pos=i;
            ret=data[i];
        }
    }
    return ret;
}

int Statistics::MinY(const QVector<QPointF> &data)
{
    if (!data.size()) return -1;

    double min=data[0].y();
    int ret=0;

    for (int i=1;i<data.size();++i)
    {
        if (data[i].y()<min) {
            ret=i;
            min=data[i].y();
        }
    }
    return ret;
}

double Statistics::Sum(const QVector<double> &data)
{
    double sum=0;
    for (int i=0;i<data.size();++i)
        sum+=data[i];
    return sum;
}

double Statistics::Average(const QVector<double> &data)
{
    if (!data.size()) return 0;

    double sum=Sum(data);
    return sum/data.size();
}

double Statistics::StandardDeviation(const QVector<double> &data)
{
    if (data.size()==0||data.size()==1) return 0;

    double mean=Average(data);
    double sum=0;
    for (int i=0;i<data.size();++i)
    {
        sum+=(data[i]-mean)*(data[i]-mean);
    }
    return sum/data.size();
}

double Statistics::SampleStandardDeviation(const QVector<double> &data)
{
    if (data.size()==0||data.size()==1) return 0;
    double mean=Average(data);
    double sum=0;
    for (int i=0;i<data.size();++i)
    {
        sum+=(data[i]-mean)*(data[i]-mean);
    }
    return sum/(data.size()-1);
}
