#include "controller.h"

Controller::Controller() :
    m_pFrameGenerator(nullptr),
    m_pView(nullptr)
{

}



Controller::~Controller()
{
    //nothing...
}

void Controller::setup(View *pView, FrameGenerator *pFrameGenerator)
{
    this->m_pView = pView;
    this->m_pFrameGenerator = pFrameGenerator;
}

void Controller::initiateAccessingCameraVision()
{
    m_pFrameGenerator->calibrateCamera();
    std::thread frameGeneratorThread(&FrameGenerator::accessAndConvertCameraView, FrameGenerator());
    frameGeneratorThread.join();
}

void Controller::viewCallback(QImage image, void (View::*pUpdateCameraView)(QImage))
{
    (m_pView->*pUpdateCameraView)(image); //CALLBACK PROBLEM!!!
}

void Controller::orderCameraViewUpdate(QImage image)
{
    //void (View::*ptr)(QImage);
    //ptr = &View::updateCameraView;
    viewCallback(image, &View::initiateCameraViewUpdate);
}
