#ifndef CAMERA_H
#define CAMERA_H

#include "camera_global.h"

#include <QString>
#include <QVector>

struct v4l2_buffer;
class QImage;

class CAMERA_EXPORT Camera
{
public:
    Camera();
    ~Camera();

    bool OpenCamera();

    bool CloseCamera();

    bool ReadPrepare();
    bool ReadFinish();

    bool GetRealTimeFrame(const QString& file);

private:
    bool RequestBuffer();
    bool BufferInfo(int buf_index, int& buf_length, int& buf_offset);
    bool BufferMap(int buf_index, int buf_length, int buf_offset);
    bool BufferUnmap(int buf_index);
    bool StreamOn();
    bool StreamOff();
    bool InQueue(int buf_index);
    bool OutQueue();
    bool AllInQueue();
    bool AllOutQueue();
    QImage ReadImage(int index);

private:
    const char* dev_name_;
    int fd_;
    int buf_size_;
    int buf_length_;
    QVector<v4l2_buffer*> buf_;
    QVector<QPair<void*, int>> map_info_;
    QVector<void*> maps_;
};

#endif // CAMERA_H
