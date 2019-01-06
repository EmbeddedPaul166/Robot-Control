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
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    Ui::View *ui;
    int m_width;
    int m_height;
    double m_maximumSpeed;
    bool isAutomaticModeOn;
    bool m_isKeyPressed;
    void closeEvent (QCloseEvent *event);
    void showEvent(QShowEvent *event);
signals:
    void startTransmission();
    void stop();
    void sendSignal(int message, int rightWheelSpeed, int leftWheelSpeed);
    void stopSignal();
    void sendInfoAboutAutomaticMode();
    void keyPressed(QString keyName);
    void keyReleased();
    void initiateUART();
public slots:
    void onStream(QImage img);
    void onStopInstruction();
    void onSendInstructionInAutomaticMode(int imageArea);
    void onButtonPressed();
    void onButtonClicked();
    void onButtonReleased();
    void onKeyPressed(QString keyName);
    void onKeyReleased();
    void onSliderChange(int sliderValue);
    void onFailedUART();

};

#endif // VIEW_H
