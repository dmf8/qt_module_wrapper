#include "camera_process.h"
#include "camera_step.h"
#include <iostream>

CameraProcess::CameraProcess()
    : cam_name_("")
    , cam_step_(new CameraStep)
{

}

CameraProcess::~CameraProcess()
{
    delete cam_step_;
}

void CameraProcess::SetCameraName(const char *name)
{
    cam_name_ = name;
}

bool CameraProcess::ShotPrepare(int &img_size, int *err)
{
    //open
    if (!cam_step_->OpenCamera(cam_name_.data())) {
        if (err) *err = cam_step_->GetErrno();
        std::cout<<"open camera error"<<std::endl;
        return false;
    }

    //request buffer
    if (!cam_step_->RequestBuffer(img_size)) {
        if (err) *err = cam_step_->GetErrno();
        std::cout<<"camera buffer error"<<std::endl;
        return false;
    }

    //stream on
    if (!cam_step_->StreamOn()) {
        if (err) *err = cam_step_->GetErrno();
        std::cout<<"stream error"<<std::endl;
        return false;
    }

    //in queue
    if (!cam_step_->AllInQueue()) {
        if (err) *err = cam_step_->GetErrno();
        std::cout<<"in queue error"<<std::endl;
        return false;
    }

    return true;
}

bool CameraProcess::ShotBuffered(unsigned char *img, int *err)
{
    if (!cam_step_->GetImage(img)) {
        if (err) *err = cam_step_->GetErrno();
        std::cout<<"shot error"<<std::endl;
        return false;
    }

    return true;
}

bool CameraProcess::ShotCurrent(unsigned char *img, int *err)
{
    if (!cam_step_->RefreshBuffer()) {
        if (err) *err = cam_step_->GetErrno();
        std::cout<<"buffer error"<<std::endl;
        return false;
    }

    return ShotBuffered(img, err);
}

bool CameraProcess::ShotFinish(int *err)
{
    //stream off
    if (!cam_step_->StreamOff()) {
        if (err) *err = cam_step_->GetErrno();
        std::cout<<"stream error"<<std::endl;
        return false;
    }

    //unmap
    if (!cam_step_->BufferUnmap()) {
        if (err) *err = cam_step_->GetErrno();
        std::cout<<"unmap error"<<std::endl;
        return false;
    }

    //close
    if (!cam_step_->CloseCamera()) {
        if (err) *err = cam_step_->GetErrno();
        std::cout<<"close camera error"<<std::endl;
        return false;
    }
    return true;
}

