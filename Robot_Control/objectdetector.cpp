#include "objectdetector.h"

ObjectDetector::ObjectDetector()
{
    //nothing...
}

void ObjectDetector::detectCircle(cv::Mat frame, std::vector<cv::Vec3f> &circles)
{
    if (!frame.empty())
    {
        cv::cvtColor(frame, m_greyFrame, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(m_greyFrame, m_greyFrame, cv::Size(9, 9), 2, 2);
        cv::HoughCircles(m_greyFrame, circles, cv::HOUGH_GRADIENT, 1, m_greyFrame.rows/8, 200, 40, 0, 0);
    }
}
