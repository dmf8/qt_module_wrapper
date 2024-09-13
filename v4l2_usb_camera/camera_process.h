#ifndef CAMERA_PROCESS_H
#define CAMERA_PROCESS_H

#include <string>

class CameraStep;
class CameraProcess
{
public:
    CameraProcess();
    ~CameraProcess();

    void SetCameraName(const char *name);
    bool ShotPrepare(int &img_size, int *err = nullptr);
    bool ShotBuffered(unsigned char *img, int *err = nullptr);
    bool ShotCurrent(unsigned char *img, int *err = nullptr);
    bool ShotFinish(int *err = nullptr);

private:
    std::string cam_name_;
    CameraStep *cam_step_;
};

#endif // CAMERA_PROCESS_H
