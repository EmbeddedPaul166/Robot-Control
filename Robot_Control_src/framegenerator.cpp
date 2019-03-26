#include <math.h>
#include "framegenerator.h"
#include "view.h"


FrameGenerator::FrameGenerator(QObject *parent) :
    QThread(parent),
    m_state(false),
    m_automaticMode(false),
    m_frame(),
    m_undistortedFrame(),
    m_cameraMatrix({1066.072199882264158, 0.0,                  264.3642126308093339,
                    0.0,                  1065.226505783904031, 242.7143108318139753,
                    0.0,                  0.0,                  1.0}),
    m_distortionCoefficients({-0.3831924018486001504, -0.4380056186732124712, -0.001564684054709905873, 0.001345324841678506361, 4.018577502467049811}),
    m_distortionMapOne(),
    m_distortionMapTwo(),
    m_img(),
    m_timer(),
    m_objectDetector(),
    m_tristateRegulator(),
    m_action(),
    m_imageArea(),
    m_xCoordinate(),
    m_imageAreaSize(),
    m_middlePointXCoordinate()
{
    m_timer.setInterval(1000);

    m_timer.setSingleShot(true);

    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(sendStopInstruction()));
}

void FrameGenerator::run()
{
    cv::VideoCapture video(0); //open camera by index 0

    if (video.isOpened())
    {
        video.read(m_frame);

        cv::initUndistortRectifyMap(m_cameraMatrix, m_distortionCoefficients, cv::Mat(), //initialize two distortion maps
                                    m_cameraMatrix, cv::Size(m_frame.cols, m_frame.rows),
                                    CV_32FC2, m_distortionMapOne, m_distortionMapTwo);
    }

    while(m_state && video.isOpened())
    {
        video.read(m_frame); //read single frame from the camera

        cv::remap(m_frame, m_undistortedFrame, m_distortionMapOne, //remove distortion from the frame
                  m_distortionMapTwo, cv::INTER_LINEAR);

        m_objectDetector.detectCircle(m_undistortedFrame); //detect circle

        convertToQtSupportedImageFormat(); //convert from BGR to RGB and convert cv::Mat to QImage type

        streamFrame(); //send a frame to update View

        if (m_objectDetector.isObjectDetected() && m_automaticMode)
        {
            if (m_timer.isActive())
            {
                emit stopTimer();
            }

            calculateActionAndSendAppropriateSignal(); //calculate in which area detected object is and send appropriate instruction code
        }
        else if (!m_objectDetector.isObjectDetected() && m_automaticMode && !m_timer.isActive())
        {
            emit startTimerSingleShot();
        }
    }
}

void FrameGenerator::convertToQtSupportedImageFormat()
{
    cv::cvtColor(m_undistortedFrame, m_undistortedFrame, cv::COLOR_BGR2RGB);

    m_img = QImage(m_undistortedFrame.data, m_undistortedFrame.cols,
                   m_undistortedFrame.rows, static_cast<int>(m_frame.step),
                   QImage::Format_RGB888);
}

void FrameGenerator::streamFrame()
{
    emit stream(m_img);
}

void FrameGenerator::calculateActionAndSendAppropriateSignal()
{
    m_middlePointXCoordinate = m_undistortedFrame.cols/2; //get x coordinate of the middle point in the frame

    m_xCoordinate = m_objectDetector.getCenterCoordinates().x; //get x coordinate of the middle of the tracked area

    m_imageAreaSize = m_undistortedFrame.cols/9; //get total x coordinate length of the frame and divide it to 9 areas

    m_tristateRegulator.calculate(m_middlePointXCoordinate, m_xCoordinate, m_imageAreaSize, m_action); //check which steering signal to use

    if (m_action == STEERING_SIGNAL::MOVE_FORWARD)
    {
        calculateObjectLocation(); //calculate in which area middle of the object resides in

        if (m_previousImageAreaRoundedUp != m_imageAreaRoundedUp)
        {
            emit sendInstructionInAutomaticMode(m_imageAreaRoundedUp, "Move forward"); //send signal
        }
    }
    else if (m_action == STEERING_SIGNAL::ARC_RIGHT)
    {
        calculateObjectLocation(); //calculate in which area middle of the object resides in

        if (m_previousImageAreaRoundedUp != m_imageAreaRoundedUp)
        {
            emit sendInstructionInAutomaticMode(m_imageAreaRoundedUp, "Arc right"); //send signal
        }
    }
    else if (m_action == STEERING_SIGNAL::ARC_LEFT)
    {
        calculateObjectLocation(); //calculate in which area middle of the object resides in

        if (m_previousImageAreaRoundedUp != m_imageAreaRoundedUp)
        {
            emit sendInstructionInAutomaticMode(m_imageAreaRoundedUp, "Arc left"); //send signal
        }
    }
    m_previousImageAreaRoundedUp = m_imageAreaRoundedUp;
}

void FrameGenerator::calculateObjectLocation()
{
    m_imageArea = static_cast<double>(m_xCoordinate)/static_cast<double>(m_imageAreaSize);

    m_imageAreaRoundedUp = static_cast<int>(ceil(m_imageArea));
}

void FrameGenerator::sendStopInstruction()
{
    m_previousImageAreaRoundedUp = 10;
    emit stopInstruction();
}

void FrameGenerator::onStartTimerSingleShot()
{
    m_timer.start();
}

void FrameGenerator::onStopTimer()
{
    m_timer.stop();
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

    quit(); //tell the thread to exit it's run loop

    wait(); //join the thread
}

void FrameGenerator::onSendInfoAboutAutomaticMode()
{
    m_automaticMode = !m_automaticMode;

    m_previousImageAreaRoundedUp = 10;

    m_timer.stop();

    emit stopInstruction();
}
