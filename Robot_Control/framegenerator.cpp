#include "framegenerator.h"
#include "view.h"
#include "globals.h"

FrameGenerator::FrameGenerator(QObject *parent) :
    QThread(parent),
    m_state(false)
{

}

void FrameGenerator::run()
{
    cv::VideoCapture video(0);
    while(m_state && video.isOpened())
    {
        in.acquire();
        video.read(m_frame);
        m_circles.clear();
        m_objectDetector.detectCircle(m_frame, m_circles);
        if (!m_circles.empty())
        {
            for( size_t i = 0; i < m_circles.size(); i++ )
            {
               cv::Point center(cvRound(m_circles[i][0]), cvRound(m_circles[i][1]));
               int radius = cvRound(m_circles[i][2]);
               //cv::circle(m_frame, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
               cv::circle(m_frame, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
            }
        }
        cv::cvtColor(m_frame, m_frame, CV_BGR2RGB);
        m_img = QImage(m_frame.data, m_frame.cols, m_frame.rows, static_cast<int>(m_frame.step), QImage::Format_RGB888);
        emit stream(m_img);
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
