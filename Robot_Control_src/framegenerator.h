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
#include <QTimer>

#include "objectdetector.h"
#include "tristateregulator.h"

class View;

class FrameGenerator : public QThread
{
    Q_OBJECT
public:
    explicit FrameGenerator(QObject *parent = nullptr);
private:
    void run();
    void convertToQtSupportedImageFormat();
    void streamFrame();
    void calculateActionAndSendAppropriateSignal();
    void calculateObjectLocation();
    bool m_state;
    bool m_automaticMode;
    cv::Mat m_frame;
    cv::Mat m_undistortedFrame;
    cv::Matx33d m_cameraMatrix;
    cv::Mat m_distortionCoefficients;
    cv::Mat m_distortionMapOne;
    cv::Mat m_distortionMapTwo;
    QImage m_img;
    QTimer m_timer;
    ObjectDetector m_objectDetector;
    TristateRegulator m_tristateRegulator;
    STEERING_SIGNAL m_action;
    double m_imageArea;
    int m_imageAreaRoundedUp;
    int m_previousImageAreaRoundedUp;
    int m_xCoordinate;
    int m_imageAreaSize;
    int m_middlePointXCoordinate;
signals:
    void stream(QImage img);
    void sendInstructionInAutomaticMode(int imageArea, QString steeringSignal);
    void stopInstruction();
    void stopTimer();
    void startTimerSingleShot();
public slots:
    void onStartTransmission();
    void onStop();
    void onSendInfoAboutAutomaticMode();
    void sendStopInstruction();
    void onStartTimerSingleShot();
    void onStopTimer();
};

#endif // FRAMEGEN_H
