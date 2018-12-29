#ifndef OBJECTDETECTOR_H
#define OBJECTDETECTOR_H

#include <opencv2/objdetect/objdetect.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/tracking.hpp"

class ObjectDetector
{
public:
    ObjectDetector();
    ~ObjectDetector();
    void detectCircle(cv::Mat &frame);
    cv::Point getCenterCoordinates();
    bool isObjectDetected();
private:
    cv::Mat m_greyFrame;
    cv::Ptr<cv::Tracker> m_objectTracker;
    bool m_isObjectDetected;
    cv::Rect2d * m_ptrTrackingRectangleBox;
    cv::Point m_center;
    std::vector<cv::Vec3f> m_circles;
    int m_height;
    int m_width;
};

#endif // OBJECTDETECTOR_H
