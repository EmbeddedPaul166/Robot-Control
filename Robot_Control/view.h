#ifndef VIEW_H
#define VIEW_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QImage>
#include <QMainWindow>

class FrameGenerator;
class UART;

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    ~View();
    void setup(FrameGenerator* pframe, UART* pUART);

private:
    Ui::View *ui;
    int m_width;
    int m_height;
    double m_maximumSpeed;
    bool isAutomaticModeOn;
    void closeEvent (QCloseEvent *event);
    void showEvent(QShowEvent *event);
signals:
    void startTransmission();
    void stop();
    void sendSignal(int message, int value, int otherWheelSpeedPercentegeDuringArcing);
    void initiateAutomaticMode();
    void exitAutomaticMode();
    void sendSignalAutomaticMode(int rightWheelSpeed, int leftWheelSpeed);
    void stopSignal();
public slots:
    void onStream(QImage img);
    void onButtonPressed();
    void onButtonClicked();
    void onButtonReleased();
    void onSliderChange(int sliderValue);
    void onFailedUART();

};

#endif // VIEW_H
