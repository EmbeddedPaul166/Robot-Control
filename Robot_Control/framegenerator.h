#ifndef FRAMEGEN_H
#define FRAMEGEN_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/tracking.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include <QObject>
#include <QtCore>
#include <QImage>

#include "objectdetector.h"

class View;

class FrameGenerator : public QThread
{
    Q_OBJECT
public:
    explicit FrameGenerator(QObject *parent = nullptr);
private:
    void run();
    void convertToQtSupportedImageFormat();
    void streamVideo();
    void sendInstruction();
    bool m_state;
    bool m_automaticMode;
    cv::Mat m_frame;
    cv::Mat m_flippedFrame;
    cv::Mat m_undistortedFlippedFrame;
    cv::Matx33d m_cameraMatrix;
    cv::Mat m_distortionCoefficients;
    QImage m_img;
    ObjectDetector m_objectDetector;
    int m_imageArea;
    int m_xCoordinate;
    int m_imageAreaSize;
signals:
    void stream(QImage img);
    void sendInstructionInAutomaticMode(int imageArea);
    void clear();
    void stopInstruction();
public slots:
    void onStartTransmission();
    void onStop();
    void onSendInfoAboutAutomaticMode();

};

#endif // FRAMEGEN_H
