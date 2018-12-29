#ifndef FRAMEGEN_H
#define FRAMEGEN_H


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/tracking.hpp>
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
    bool m_state;
    bool m_automaticMode;
    cv::Mat m_frame;
    QImage m_img;
    ObjectDetector m_objectDetector;
    cv::Point m_center;
    int m_imageArea;
signals:
    void stream(QImage img);
    void streamAutomaticMode(QImage img, int imageArea);
    void clear();
public slots:
    void onStartTransmission();
    void onStop();
    void onSendInfoAboutAutomaticMode();

};

#endif // FRAMEGEN_H
