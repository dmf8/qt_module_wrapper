#include "data_handler.h"


DataHandler::DataHandler()
{
    qDebug(__FUNCTION__);
}

QVector<QPointF> DataHandler::AverageFilter(const QVector<QPointF> &data, int half_window)
{
    if (!data.size())
        throw 0;

    // get helper list
    QVector<QPointF> temp = data;
    int count = data.size();
    for (int i = 0; i < half_window; ++i) {
        temp.prepend(QPointF(data[0].x() - i - 1, data[0].y()));
        temp.append(QPointF(data[count - 1].x() + i + 1, data[count - 1].y()));
    }
    // filt
    QVector<QPointF> l;
    int len = half_window * 2 + 1;
    for (int i = 0; i < count; ++i) {
        double mean = GetAverage(temp, i, len);
        l.append(QPointF(data[i].x(), mean));
    }

    return l;
}

QVector<QPointF> DataHandler::DeriveCenter(const QVector<QPointF> &data)
{
    if (0==data.size()||1==data.size())
        return DeriveSpecialCase(data);

    // general case
    QVector<QPointF> l;
    // ??check same temperature

    // derive
    for (int i = 0; i < data.size(); ++i) {
        double t, tb,tf;
        double fb,ff;
        double d;
        t = data[i].x();
        tb=i==0?data[i].x():data[i-1].x();
        fb=i==0?data[i].y():data[i-1].y();
        tf=i==data.size()-1?data[i].x():data[i+1].x();
        ff=i==data.size()-1?data[i].y():data[i+1].y();

        if (tf == tb)
            d = 0;
        else
            d = (ff - fb) / (tf - tb);
        l.append(QPointF(t, d));
    }

    return l;
}

QVector<QPointF> DataHandler::DeriveBackward(const QVector<QPointF> &data)
{
    if (0==data.size()||1==data.size())
        return DeriveSpecialCase(data);

    // general case
    QVector<QPointF> l;
    // ??check same temperature

    // derive
    for (int i = 1; i < data.size(); ++i) {
        double t, tb;
        double f, fb;
        double d;
        t = data[i].x();
        f = data[i].y();

        tb = data[i - 1].x();
        fb = data[i - 1].y();

        if (t == tb)
            d = 0;
        else
            d = (f - fb) / (t - tb);
        l.append(QPointF(t, d));
    }

    // first point
    l.prepend(QPointF(data[0].x(),l.first().y()));

    return l;
}

QVector<QPointF> DataHandler::DeriveForward(const QVector<QPointF> &data)
{
    if (0==data.size()||1==data.size())
        return DeriveSpecialCase(data);

    // general case
    QVector<QPointF> l;
    // ??check same temperature

    // derive
    for (int i = 0; i < data.size(); ++i) {
        double t, tf;
        double f, ff;
        double d;
        t = data[i].x();
        f = data[i].y();

        // last point
        if (i == data.size() - 1) {
            l.append(QPointF(t, l.last().y()));
            continue;
        }
        // general case
        tf = data[i + 1].x();
        ff = data[i + 1].y();

        if (t == tf)
            d = 0;
        else
            d = (ff - f) / (tf - t);
        l.append(QPointF(t, d));
    }
    return l;
}

QVector<QPointF> DataHandler::ReverseY(const QVector<QPointF> &data)
{
    QVector<QPointF> d=data;
    for (int i=0;i<d.size();++i)
        d[i].setY(-d[i].y());
    return d;
}

double DataHandler::GetAverage(const QVector<QPointF> &data, int start, int len) const
{
    double sum = 0;
    for (int i = 0; i < len; ++i) {
        sum += data[start + i].y();
    }
    return sum / len;
}

QVector<QPointF> DataHandler::DeriveSpecialCase(const QVector<QPointF> &data)
{
    // no point
    if (data.size() == 0)
        return {};
    // 1 point
    else if (data.size() == 1)
        return {QPointF(data[0].x(),0)};
    else
        return {};
}
