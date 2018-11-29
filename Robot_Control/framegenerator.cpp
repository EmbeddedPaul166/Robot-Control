#include "framegenerator.h"
#include "controller.h"
#include "globals.h"

FrameGenerator::FrameGenerator() :
    m_state(true),
    m_isCameraCalibrated(false),
    m_frame(),
    m_image(),
    m_pController(nullptr)
{

}

FrameGenerator::~FrameGenerator()
{
    //nothing...
}


void FrameGenerator::setup(Controller *pController)
{
    this->m_pController = pController;
}

void FrameGenerator::calibrateCamera()
{
    //camera calibration code...
    m_isCameraCalibrated = true;
}

void FrameGenerator::accessAndConvertCameraView()
{
    cv::VideoCapture video(0);
    while(m_state && video.isOpened())
    {
        frameMutex.lock();
        video.read(m_frame);
        cv::cvtColor(m_frame, m_frame, CV_BGR2RGB);
        m_image = QImage(m_frame.data, m_frame.cols, m_frame.rows, static_cast<int>(m_frame.step), QImage::Format_RGB888);
        m_pController->orderCameraViewUpdate(m_image);
        frameMutex.unlock();
    }
}
