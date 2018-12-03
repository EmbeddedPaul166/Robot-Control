#ifndef OBJECTDETECTOR_H
#define OBJECTDETECTOR_H

#include <opencv2/objdetect/objdetect.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ObjectDetector
{
public:
    ObjectDetector();
    void detectCircle(cv::Mat frame, std::vector<cv::Vec3f> &circles);
private:
    cv::Mat m_greyFrame;
};

#endif // OBJECTDETECTOR_H
