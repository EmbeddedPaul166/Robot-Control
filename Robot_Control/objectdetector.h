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
private:
    cv::Mat m_greyFrame;
    cv::Ptr<cv::Tracker> m_objectTracker;
    bool m_isObjectDetected;
    cv::Rect2d * m_ptrTrackingRectangleBox;
    std::vector<cv::Vec3f> m_circles;
};

#endif // OBJECTDETECTOR_H
