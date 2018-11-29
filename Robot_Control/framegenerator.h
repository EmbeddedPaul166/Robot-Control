#ifndef FRAMEGENERATOR_H
#define FRAMEGENERATOR_H

#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class Controller;

class FrameGenerator
{
public:
    FrameGenerator();
    virtual ~FrameGenerator();

    void setup(Controller *pController);
    void calibrateCamera();
    void accessAndConvertCameraView();

private:
    bool m_state;
    bool m_isCameraCalibrated;
    cv::Mat m_frame;
    QImage m_image;
    Controller *m_pController;
};

#endif // FRAMEGENERATOR_H
