#ifndef FRAMEGEN_H
#define FRAMEGEN_H


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QObject>
#include <QtCore>
#include <QImage>

class View;

class FrameGenerator : public QThread
{
    Q_OBJECT
public:
    explicit FrameGenerator(QObject *parent = nullptr);
private:
    void run();
    bool m_state;
    cv::Mat m_frame;
    QImage m_img;
signals:
    void stream(QImage img);
    void clear();
public slots:
    void onStartTransmission();
    void onStop();

};

#endif // FRAMEGEN_H
