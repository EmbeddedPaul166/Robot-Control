#include "framegenerator.h"
#include "view.h"
#include "globals.h"


FrameGenerator::FrameGenerator(QObject *parent) :
    QThread(parent),
    m_state(false),
    m_automaticMode(false),
    m_frame(),
    m_flippedFrame(),
    m_undistortedFlippedFrame(),
    m_cameraMatrix({1066.072199882264158, 0.0,                  264.3642126308093339,
                    0.0,                  1065.226505783904031, 242.7143108318139753,
                    0.0,                  0.0,                  1.0}),
    m_distortionCoefficients({-0.3831924018486001504, -0.4380056186732124712, -0.001564684054709905873, 0.001345324841678506361, 4.018577502467049811}),
    m_img(),
    m_objectDetector(),
    m_imageArea(),
    m_xCoordinate(),
    m_imageAreaSize()
{
    //do nothing...
}

void FrameGenerator::run()
{
    cv::VideoCapture video(0); //open camera by index 0

    while(m_state && video.isOpened())
    {
        in.acquire(); //aqcuire semaphore

        video.read(m_frame); //read single frame from the camera

        cv::flip(m_frame, m_flippedFrame, -1); //invert the frame

        cv::undistort(m_flippedFrame, m_undistortedFlippedFrame, m_cameraMatrix, m_distortionCoefficients); //remove distortion from the flipped frame

        m_objectDetector.detectOrTrackCircle(m_undistortedFlippedFrame); //detect circle and initiate tracking or update tracker

        convertToQtSupportedImageFormat(); //convert from BGR to RGB and convert cv::Mat to QImage type

        streamVideo(); //send a frame to update View

        out.release(); //release semaphore

        if (m_objectDetector.isObjectDetected() && m_automaticMode)
        {
            sendInstruction(); //calculate in which area detected object is and send appropriate instruction code
        }
        else if (!m_objectDetector.isObjectDetected() && m_automaticMode)
        {
            emit stopInstruction();
        }
    }
    emit clear(); //clear visible frames on shutdown
}

void FrameGenerator::convertToQtSupportedImageFormat()
{
    cv::cvtColor(m_undistortedFlippedFrame, m_undistortedFlippedFrame, cv::COLOR_BGR2RGB);

    m_img = QImage(m_undistortedFlippedFrame.data, m_undistortedFlippedFrame.cols, m_undistortedFlippedFrame.rows, static_cast<int>(m_frame.step), QImage::Format_RGB888);
}

void FrameGenerator::streamVideo()
{
    emit stream(m_img);
}

void FrameGenerator::sendInstruction()
{
    m_xCoordinate = m_objectDetector.getCenterCoordinates().x; //get x coordinate of the middle of the tracked area

    m_imageAreaSize = m_undistortedFlippedFrame.cols/9; //get total x coordinate length of the frame and divide it to 9 areas

    m_imageArea = m_xCoordinate/m_imageAreaSize; //check in which area from 0 to 8 the middle of the tracked area resides in

    if (m_imageArea > 8) m_imageArea = 8;

    emit sendInstructionInAutomaticMode(m_imageArea); //send appropriate instruction code from 0 to 8
}

void FrameGenerator::onStartTransmission()
{
    if(!isRunning())
    {
        m_state = true;
        start();
    }
    else
    {
        m_state = false;
    }
}

void FrameGenerator::onStop()
{
    m_state = false;
    wait();
}

void FrameGenerator::onSendInfoAboutAutomaticMode()
{
    m_automaticMode = !m_automaticMode;
}
