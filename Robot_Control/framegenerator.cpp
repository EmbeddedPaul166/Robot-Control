#include "framegenerator.h"
#include "view.h"
#include "globals.h"


FrameGenerator::FrameGenerator(QObject *parent) :
    QThread(parent),
    m_state(false),
    m_automaticMode(false),
    m_frame(),
    m_img(),
    m_objectDetector(),
    m_center(),
    m_imageArea()
{
    //do nothing...
}

void FrameGenerator::run()
{
    cv::VideoCapture video(0);
    while(m_state && video.isOpened())
    {
        in.acquire();
        video.read(m_frame);
        m_objectDetector.detectCircle(m_frame);
        cv::cvtColor(m_frame, m_frame, cv::COLOR_BGR2RGB);
        m_img = QImage(m_frame.data, m_frame.cols, m_frame.rows, static_cast<int>(m_frame.step), QImage::Format_RGB888);

        if (m_objectDetector.isObjectDetected() && m_automaticMode)
        {
            m_center = m_objectDetector.getCenterCoordinates();
            int x = m_center.x;
            int areaSize = m_frame.cols/9;
            m_imageArea = x/areaSize;
            if (m_imageArea > 8) m_imageArea = 8;
            emit streamAutomaticMode(m_img, m_imageArea);
        }
        else
        {
            emit stream(m_img);
        }

        out.release();
    }
    emit clear();
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
