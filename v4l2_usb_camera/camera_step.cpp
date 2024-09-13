#include "camera_step.h"
#include <fcntl.h>
#include <unistd.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <cassert>

#include <iostream>
#include <string.h>
#include <stdio.h>

CameraStep::CameraStep()
    : fd_(-1)
    , errno_(0)
    , buf_size_(4)
    , buf_length_(0)
    , bufs2_({})
    , bufs_({})
{
    bufs_.resize(buf_size_);
    bufs2_.resize(buf_size_, nullptr);
}

CameraStep::~CameraStep()
{
    BufferUnmap();
    CloseCamera();
}

bool CameraStep::Reset()
{

}

bool CameraStep::OpenCamera(const char *name)
{
    int fd = open(name, O_RDWR);
    if (-1 < fd) {
        fd_ = fd;
        return true;
    } else {
        errno_ = errno;
        return false;
    }
}

bool CameraStep::CloseCamera()
{
    if (fd_ == -1) return true;
    int ret = close(fd_);
    if (0 == ret)
        fd_ = -1;

    return 0 == ret;
}

unsigned int CameraStep::CameraCapability()
{
    if (fd_ < 0)
        return 0;

    v4l2_capability cap;
    if (ioctl(fd_, VIDIOC_QUERYCAP, &cap) == -1) {
        errno_ = errno;
        return 0;
    }

    return cap.capabilities;
}

std::vector<unsigned int> CameraStep::SupportedFormats()
{
    if (fd_ < 0)
        return {};

    v4l2_fmtdesc fmt;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.index = 0;
    std::vector<unsigned int> ret = {};
    while (ioctl(fd_, VIDIOC_ENUM_FMT, &fmt) != -1) {
        ret.push_back(fmt.pixelformat);
        fmt.index++;
    }
    return ret;
}

std::vector<std::pair<unsigned int, unsigned int> > CameraStep::SupportedSize(unsigned int fmt)
{
    if (fd_ < 0)
        return {};

    v4l2_frmsizeenum size;
    size.pixel_format = fmt;
    size.index = 0;
    std::vector<std::pair<unsigned int, unsigned int> > ret = {};
    while (ioctl(fd_, VIDIOC_ENUM_FRAMESIZES, &size) != -1) {
        ret.push_back(std::make_pair(size.discrete.width, size.discrete.height));
        size.index++;
    }
    return ret;
}

bool CameraStep::SetSize(unsigned int width, unsigned int height)
{
    if (fd_ < 0) return false;
    if (width == 0 && height == 0) return false;

    v4l2_format fmt;
    if (!CaptureFormat(fmt)) return false;
    if (width > 0) fmt.fmt.pix.width = width;
    if (height > 0) fmt.fmt.pix.height = height;
    if (ioctl(fd_, VIDIOC_S_FMT, &fmt) == -1) {
        errno_ = errno;
        return false;
    }
    return true;
}

bool CameraStep::GetSize(unsigned int &width, unsigned int &height)
{
    if (fd_ < 0)
        return false;

    v4l2_format fmt;
    if (!CaptureFormat(fmt)) return false;
    width = fmt.fmt.pix.width;
    height = fmt.fmt.pix.height;
    return true;
}

bool CameraStep::RequestBuffer(int &length)
{
    if (fd_ < 0) return false;
    v4l2_requestbuffers reqbufs;
    reqbufs.count = buf_size_;
    reqbufs.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbufs.memory = V4L2_MEMORY_MMAP;
    if (ioctl(fd_, VIDIOC_REQBUFS, &reqbufs) == -1) {
        errno_ = errno;
        return false;
    }

    std::vector<std::pair<unsigned int, unsigned int>> bufs = QueryBuffers();
    if (bufs.size() < buf_size_) return false;
    length = bufs[0].second;
    return MmapBuffers(bufs);
}

bool CameraStep::RequestBuffer2()
{
    if (fd_ < 0) return false;
    v4l2_requestbuffers reqbufs;
    reqbufs.count = buf_size_;
    reqbufs.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbufs.memory = V4L2_MEMORY_MMAP;
    if (ioctl(fd_, VIDIOC_REQBUFS, &reqbufs) == -1) {
        errno_ = errno;
        return false;
    }

    return true;
}

bool CameraStep::StreamOn()
{
    if (fd_ < 0) return false;

    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd_, VIDIOC_STREAMON, &type) < 0) {
        errno_ = errno;
        return false;
    }
    return true;
}

bool CameraStep::StreamOff()
{
    if (fd_ < 0) return true;

    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ioctl(fd_, VIDIOC_STREAMOFF, &type);
    return true;
}

bool CameraStep::AllInQueue()
{
    if (fd_ < 0) return false;
    for (int i = 0; i < buf_size_; ++i) {
        if (!InQueue(i)) return false;
    }
    return true;
}

bool CameraStep::GetImage(unsigned char *img)
{
    if (fd_ < 0) return false;
    int index;
    if (!OutQueue(index)) return false;
    assert(index >= 0);
    assert(index < bufs2_.size());

    if (img) memcpy(img, bufs2_[index], buf_length_);
//    *img = (unsigned char *)bufs2_[index];
    return InQueue(index);
}

bool CameraStep::RefreshBuffer()
{
    for (int i = 0; i < buf_size_; ++i)
        if (!GetImage()) return false;

    return true;
}

bool CameraStep::BufferUnmap()
{
    for (int i = 0; i < bufs2_.size(); ++i) {
        if (bufs2_[i]) {
            if (munmap(bufs2_[i], buf_length_) == -1)
                perror("");
            bufs2_[i] = nullptr;
        }
    }
    buf_length_ = 0;
    return true;
}

bool CameraStep::MmapBuffers(const std::vector<std::pair<unsigned int, unsigned int> > &bufs)
{
    if (fd_ < 0) return false;
    for (int i = 0; i < bufs.size(); ++i) {
        void *p = mmap(NULL, bufs[i].second, PROT_READ|PROT_WRITE, MAP_SHARED, fd_, bufs[i].first);
        if (p == (void *)-1) {
            errno_ = errno;
            return false;
        }
        bufs2_[i] = p;
    }
    return true;
}

bool CameraStep::MmapBuffers2(int &length)
{
    if (fd_ < 0) return false;

    std::vector<std::pair<unsigned int, unsigned int>> bufs = QueryBuffers();
    if (bufs.size() < buf_size_) return false;
    length = bufs[0].second;

    for (int i = 0; i < bufs.size(); ++i) {
        void *p = mmap(NULL, bufs[i].second, PROT_READ|PROT_WRITE, MAP_SHARED, fd_, bufs[i].first);
        if (p == (void *)-1) {
            errno_ = errno;
            return false;
        }
        bufs2_[i] = p;
    }
    return true;
}

bool CameraStep::InQueue(int buf_index)
{
    if (fd_ < 0) return false;
    assert(buf_index >= 0);
    assert(buf_index < buf_size_);
    v4l2_buffer buf;
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = buf_index;
    if (ioctl(fd_, VIDIOC_QBUF, &buf) < 0) {
        errno_ = errno;
        return false;
    }
    return true;
}

bool CameraStep::OutQueue(int &buf_index)
{
    if (fd_ < 0) return false;

    v4l2_buffer buf;
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd_, VIDIOC_DQBUF, &buf) < 0) {
        errno_ = errno;
        return false;
    }
    buf_index = buf.index;
    return true;
}

std::vector<std::pair<unsigned int, unsigned int> > CameraStep::QueryBuffers()
{
    if (fd_ < 0) return {};

    std::vector<std::pair<unsigned int, unsigned int> > ret = {};
    for (int i = 0; i < buf_size_; ++i) {
        v4l2_buffer buf;
        buf.index = i;
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (ioctl(fd_, VIDIOC_QUERYBUF, &buf) == -1) {
            errno_ = errno;
            return {};
        }
        buf_length_ = buf.length;
        ret.push_back(std::make_pair(buf.m.offset, buf.length));
        bufs_[i] = buf;
    }

    return ret;
}

bool CameraStep::CaptureFormat(v4l2_format &fmt)
{
    if (fd_ < 0)
        return false;

    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    return ioctl(fd_, VIDIOC_G_FMT, &fmt) != -1;
}

int CameraStep::GetErrno() const
{
    return errno;
}

void CameraStep::StopShot()
{
    BufferUnmap();
    CloseCamera();
}

bool CameraStep::DeviceValid() const
{
    return fd_ > -1;
}
