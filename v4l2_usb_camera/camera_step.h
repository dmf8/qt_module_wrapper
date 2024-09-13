#ifndef CAMERA_STEP_H
#define CAMERA_STEP_H

#include <string>
#include <vector>

struct v4l2_format;
struct v4l2_buffer;

class CameraStep
{
public:
    CameraStep();
    ~CameraStep();

    bool Reset();
    //open/close
    bool OpenCamera(const char *name);
    bool CloseCamera();
    //properties
    unsigned int CameraCapability();
    std::vector<unsigned int> SupportedFormats();
    std::vector<std::pair<unsigned int, unsigned int>> SupportedSize(unsigned int fmt);
    bool SetSize(unsigned int width = 0, unsigned int height = 0);
    bool GetSize(unsigned int &width, unsigned int &height);
    //shot prepare
    bool RequestBuffer(int &length); //export length of each buffer
    bool RequestBuffer2(); //export length of each buffer
    bool MmapBuffers(const std::vector<std::pair<unsigned int, unsigned int>> &bufs);
    bool MmapBuffers2(int &length);
    bool BufferUnmap();
    bool StreamOn();
    bool StreamOff();
    bool AllInQueue();
    //shot
    bool GetImage(unsigned char *img = nullptr);
    bool RefreshBuffer();
    int GetErrno() const;
    //shot finish
    void StopShot();

//private:
    bool DeviceValid() const;
    bool CaptureFormat(v4l2_format &fmt);
    std::vector<std::pair<unsigned int, unsigned int>> QueryBuffers(); //return kernel buffer info <offset, length>


    bool InQueue(int buf_index);
    bool OutQueue(int &buf_index);

//private:
    int fd_; //record a valid fd, or -1 on exceptions
    int errno_; //record errno while io error happens
    int buf_size_; //default buf size is 4
//    int read_index_;
    int buf_length_;
    std::vector<void *>bufs2_;
    std::vector<v4l2_buffer> bufs_;
};

#endif // CAMERA_STEP_H
