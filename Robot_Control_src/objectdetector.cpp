#include "objectdetector.h"

ObjectDetector::ObjectDetector() :
    m_grayFrame(),
    m_isObjectDetected(false),
    m_isObjectTooLarge(false),
    m_ptrTrackingRectangleBox(),
    m_center(),
    m_circles(),
    m_height(),
    m_width(),
    m_radius(),
    m_sideLength()
{
    //do nothing...
}

ObjectDetector::~ObjectDetector() //clean up remaining pointers
{
    if (m_ptrTrackingRectangleBox != nullptr) delete m_ptrTrackingRectangleBox;

    if (m_center != nullptr) delete m_center;

}

void ObjectDetector::detectCircle(cv::Mat &frame)
{
    if (!frame.empty())
    {
        detectCircles(frame); //detect circles

        if (!m_circles.empty()) //check if any circles have been detected
        {
            initiateNewTrackingRectangleBox(frame);

            m_circles.clear(); //clear circles output array before next detection to avoid errors

            m_isObjectDetected = true; //set detection flag to true
        }
        else if (m_circles.empty())
        {
            m_isObjectDetected = false; //set detection flag to false
        }
    }
}

cv::Point ObjectDetector::getCenterCoordinates()
{
    return *m_center;
}

bool ObjectDetector::isObjectDetected()
{
    return m_isObjectDetected;
}

void ObjectDetector::detectCircles(cv::Mat &frame)
{
    cv::cvtColor(frame, m_grayFrame, cv::COLOR_BGR2GRAY); //convert frame to gray scale

    cv::GaussianBlur(m_grayFrame, m_grayFrame, cv::Size(9, 9), 2, 2); //blur the gray frame using Gaussian filter

    cv::HoughCircles(m_grayFrame, m_circles, cv::HOUGH_GRADIENT, 1, m_grayFrame.rows/8, 200, 40, 0, 0); //find circles in a gray scale image using Hough transform

}

void ObjectDetector::initiateNewTrackingRectangleBox(cv::Mat &frame)
{
    m_center = new cv::Point(cvRound(m_circles[0][0]), cvRound(m_circles[0][1])); //get x and y coordinates of the first circle detected

    m_radius = cvRound(m_circles[0][2]); //get radius of the first circle detected

    m_sideLength = m_radius*2;

    m_width = m_center->x - m_radius; //calculate x coordinate of the upper left corner of the rectangle

    m_height = m_center->y - m_radius; //calculate y coordinate of the upper left corner of the rectangle

    m_ptrTrackingRectangleBox = new cv::Rect2d(m_width, m_height, m_sideLength, m_sideLength); //initiate new rectangle on the detected area

    cv::rectangle(frame, *m_ptrTrackingRectangleBox, cv::Scalar(0,0,255), 3, 8, 0); //draw rectangle on the detected circle
}
