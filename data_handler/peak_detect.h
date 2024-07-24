#ifndef PEAK_DETECT_H
#define PEAK_DETECT_H

#include <QList>
#include <QPointF>

#include "data_handler_global.h"

typedef QPair<int, QPointF> IdPoint;
typedef QVector<IdPoint> PointSeq;

struct DATA_HANDLER_EXPORT PeakInfo {
    double width;
    double height;
    IdPoint peak;
    IdPoint bottom;

    void DebugOutput() const;
};

typedef QVector<QPair<int, PeakInfo>> PeakInfoSeq;

struct DATA_HANDLER_EXPORT PeakFilter {
    double min_width;
    double min_height;
    double min_value;
    double min_ratio;
    int min_count;
    bool reverse_peak;

    PeakFilter(double w = 5, double h = 15, double v = 0, double r = 1, int c = 0, bool rp = false);
};

class DATA_HANDLER_EXPORT PeakDetect
{
public:
    PeakDetect();
    PeakInfoSeq Detect(const QVector<QPointF>& data, const PeakFilter& filter) const;
    void Test();
    void testData();

private:
    PointSeq LocalPeaks(const QVector<QPointF>& data) const;
    PeakInfoSeq LocalPeakInfo(const QVector<QPointF>& data, const PointSeq& peaks) const;
    IdPoint PeakBottom(const QVector<QPointF>& data, const IdPoint& p) const;
    double PeakWidth(const QVector<QPointF>& data, const IdPoint& p, const IdPoint& b) const;
    double PeakHeight(const IdPoint& p, const IdPoint& b) const;
    PeakInfoSeq FiltPeaks(const PeakInfoSeq& peaks, const PeakFilter& filter) const;
};

#endif  // PEAK_DETECT_H
