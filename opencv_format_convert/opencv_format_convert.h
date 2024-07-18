#ifndef OPENCV_FORMAT_CONVERT_H
#define OPENCV_FORMAT_CONVERT_H

#include <QImage>

#include "opencv_format_convert_global.h"

namespace cv
{
class Mat;
}

class OPENCV_FORMAT_CONVERT_EXPORT OpencvFormatConvert
{
public:
    OpencvFormatConvert();

    static void MatInfoOutput(cv::Mat img);
    static QImage Mat2QImage(cv::Mat img) noexcept(false);
};

#endif  // OPENCV_FORMAT_CONVERT_H
