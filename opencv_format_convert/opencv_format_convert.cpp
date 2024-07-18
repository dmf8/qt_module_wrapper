#include "opencv_format_convert.h"

#include <QDebug>
#include <exception>
#include <opencv2/core/mat.hpp>

struct test : public std::exception {
    const char* what() const noexcept
    {
        return "abc";
    }
};

OpencvFormatConvert::OpencvFormatConvert()
{
}

void OpencvFormatConvert::MatInfoOutput(cv::Mat img)
{
    qDebug() << "size" << img.cols << img.rows;
    qDebug() << "channels" << img.channels();
    qDebug() << "depth" << img.depth();
}

QImage OpencvFormatConvert::Mat2QImage(cv::Mat img) noexcept(false)
{
    switch (img.channels()) {
        case 1:

            break;
        case 3:

            break;
        case 4:

            break;
        default:
            break;
    }
    throw test();
}
