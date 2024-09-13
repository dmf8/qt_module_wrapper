#include "camera.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <QCoreApplication>
#include <QDebug>
#include <QImage>

Camera::Camera() :
    dev_name_("/dev/video0"),
    fd_(-1),
    buf_size_(4)
{
    buf_.resize(buf_size_);
    map_info_.resize(buf_size_);
    maps_.resize(buf_size_);
    for (int i = 0; i < buf_size_; ++i) {
        buf_[i] = new v4l2_buffer;
    }
}

Camera::~Camera()
{
    for (int i = 0; i < buf_size_; ++i) {
        if (nullptr != buf_[i]) {
            delete buf_[i];
            buf_[i] = nullptr;
        }
    }
}

bool Camera::OpenCamera()
{
    int fd = open(dev_name_, O_RDWR);
    if (-1 < fd) {
        fd_ = fd;
        return true;
    } else {
        return false;
    }
}

bool Camera::CloseCamera()
{
    int ret = close(fd_);
    if (-1 < ret)
        fd_ = -1;

    return -1 != ret;
}

bool Camera::ReadPrepare()
{
    if (-1 == fd_)
        return false;

    if (!RequestBuffer()) {
        qDebug()<<"request buffer error";
        return false;
    }

    //mmap
    int buf_length, buf_offset;
    for (int i = 0; i < buf_size_; ++i) {
        bool ret = BufferInfo(i, buf_length, buf_offset);
        if (!ret) {
            qDebug()<<"buf info error "<<i;
            return false;
        }

        ret = BufferMap(i, buf_length, buf_offset);
        if (!ret) {
            qDebug()<<"buf map error "<<i;
            return false;
        }
    }

    buf_length_ = buf_length;

    if (!StreamOn()) {
        qDebug()<<"stream on error";
        return false;
    }

    return true;
}

bool Camera::ReadFinish()
{
    if (!StreamOff()) {
        qDebug()<<"stream off error";
        return false;
    }

    for (int i = 0; i < buf_size_; ++i) {
        if (!BufferUnmap(i)) {
            qDebug()<<"unmap error "<<i;
            return false;
        }
    }

    return true;
}

bool Camera::GetRealTimeFrame(const QString &file)
{
    if (!AllInQueue()) {
        qDebug()<<"all in queue error";
        return false;
    }

    if (!AllOutQueue()) {
        qDebug()<<"all out queue error";
        return false;
    }

    int index = 0;

    if (!InQueue(index)) {
        qDebug()<<"frame in queue error";
        return false;
    }

    if (!OutQueue()) {
        qDebug()<<"frame out queue error";
        return false;
    }

    QImage img = ReadImage(index);

    return img.save(file);
}

QImage Camera::ReadImage(int index)
{
    QImage img;
    img.loadFromData((uchar*)maps_[index], buf_length_);
    qDebug()<<"image size "<<img.size();

    return img;
}

bool Camera::RequestBuffer()
{
    if (-1 == fd_)
        return false;

    struct v4l2_requestbuffers reqbufs;
    reqbufs.count = buf_size_;
    reqbufs.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbufs.memory = V4L2_MEMORY_MMAP;
    int ret = ioctl(fd_, VIDIOC_REQBUFS, &reqbufs);
    if(ret < 0){
        perror("require memory failed");
        return false;
    }else{
        printf("require memory success\n");
        return true;
    }
}

bool Camera::BufferInfo(int buf_index, int &buf_length, int &buf_offset)
{
    if (buf_index < 0 || buf_index >= buf_size_)
        return false;
    if (-1 == fd_)
        return false;

    //query struct
    v4l2_buffer buf;
    buf.index = buf_index;
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int ret = ioctl(fd_, VIDIOC_QUERYBUF, &buf);
    if (-1 != ret) {
        buf_length = buf.length;
        buf_offset = buf.m.offset;
        return true;
    } else
        return false;
}

bool Camera::BufferMap(int buf_index, int buf_length, int buf_offset)
{
    if (buf_index < 0 || buf_index >= buf_size_)
        return false;
    if (-1 == fd_)
        return false;

    void * ret = mmap(NULL,
                      buf_length,
                      PROT_READ|PROT_WRITE,
                      MAP_SHARED,
                      fd_,
                      buf_offset);
    if (MAP_FAILED != ret) {
        maps_[buf_index] = ret;
        return true;
    } else
        return false;
}

bool Camera::BufferUnmap(int buf_index)
{
    if (buf_index < 0 || buf_index >= buf_size_)
        return false;
    if (-1 == fd_)
        return false;

    int ret = munmap(maps_[buf_index], buf_length_);
    return 0 == ret;
}

bool Camera::StreamOn()
{
    if (-1 == fd_)
        return false;

    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    return -1 != ioctl(fd_, VIDIOC_STREAMON, &type);
}

bool Camera::StreamOff()
{
    if (-1 == fd_)
        return false;

    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    return -1 != ioctl(fd_, VIDIOC_STREAMOFF, &type);
}

bool Camera::InQueue(int buf_index)
{
    if (buf_index < 0 || buf_index >= buf_size_)
        return false;
    if (-1 == fd_)
        return false;

    v4l2_buffer buf;
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = buf_index;
    return -1 != ioctl(fd_, VIDIOC_QBUF, &buf);
}

bool Camera::OutQueue()
{
    if (-1 == fd_)
        return false;

    v4l2_buffer buf;
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int ret = ioctl(fd_, VIDIOC_DQBUF, &buf);
    qDebug()<<"dq ret "<<ret;
    return -1 != ret;
}

bool Camera::AllInQueue()
{
    if (-1 == fd_)
        return false;

    for (int i = 0; i < buf_size_; ++i) {
        bool ret = InQueue(i);
        if (!ret) {
            qDebug()<<"buf in queue error "<<i;
            return false;
        }
    }
    return true;
}

bool Camera::AllOutQueue()
{
    if (-1 == fd_)
        return false;

    for (int i = 0; i < buf_size_; ++i) {
        bool ret = OutQueue();
        if (!ret) {
            qDebug()<<"buf out queue error";
            return false;
        }
    }
    return true;
}
