#ifndef VIEW_H
#define VIEW_H

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
    void sendSignal(int message, int rightWheelSpeed, int leftWheelSpeed);
    void stopSignal();
    void sendInfoAboutAutomaticMode();
public slots:
    void onStream(QImage img);
    void onStopInstruction();
    void onSendInstructionInAutomaticMode(int imageArea);
    void onButtonPressed();
    void onButtonClicked();
    void onButtonReleased();
    void onSliderChange(int sliderValue);
    void onFailedUART();

};

#endif // VIEW_H
