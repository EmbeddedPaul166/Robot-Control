#include "objectdetector.h"

ObjectDetector::ObjectDetector() :
    m_greyFrame(),
    m_objectTracker(cv::TrackerKCF::create()),
    m_isObjectDetected(false),
    m_ptrTrackingRectangleBox(),
    m_circles()
{
    //do nothing...
}

ObjectDetector::~ObjectDetector()
{
    if (m_ptrTrackingRectangleBox != nullptr)
    {
        delete m_ptrTrackingRectangleBox;
    }
}

void ObjectDetector::detectCircle(cv::Mat &frame)
{
    if (!frame.empty())
    {
        if (!m_isObjectDetected)
        {
            m_objectTracker = cv::TrackerKCF::create();
            cv::cvtColor(frame, m_greyFrame, cv::COLOR_BGR2GRAY);
            cv::GaussianBlur(m_greyFrame, m_greyFrame, cv::Size(9, 9), 2, 2);
            cv::HoughCircles(m_greyFrame, m_circles, cv::HOUGH_GRADIENT, 1, m_greyFrame.rows/8, 200, 40, 0, 0);
            if (!m_circles.empty())
            {
                for( size_t i = 0; i < m_circles.size(); i++ )
                {
                    cv::Point center(cvRound(m_circles[i][0]), cvRound(m_circles[i][1]));
                    int radius = cvRound(m_circles[i][2]);
                    m_ptrTrackingRectangleBox = new cv::Rect2d(center.x - radius, center.y - radius, radius*2, radius*2);
                    m_circles.clear();
                    m_isObjectDetected = true;
                    m_objectTracker->init(frame, *m_ptrTrackingRectangleBox);
                }
            }
        }
        else if (m_objectTracker->update(frame, *m_ptrTrackingRectangleBox) && m_isObjectDetected)
        {
            cv::rectangle(frame, *m_ptrTrackingRectangleBox, cv::Scalar(0,0,255), 3, 8, 0);
        }
        if (!m_objectTracker->update(frame, *m_ptrTrackingRectangleBox) && m_isObjectDetected)
        {
            m_isObjectDetected = false;
            m_objectTracker.release();
        }
    }
}
