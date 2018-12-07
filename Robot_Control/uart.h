#ifndef UART_H
#define UART_H

//#include <wiringSerial.h>

#include <QObject>

class UART : public QObject
{
    Q_OBJECT
public:
    explicit UART(QObject *parent = nullptr);
private:
    void initiateUART();
    void codeSignal3Digit(int value, int &ones, int &tenths, int &hundredths);
    void codeSignal2Digit(int value, int &tens, int &ones);
    int m_fileDescriptor;
signals:
    void failedUART();
public slots:
    void onSendSignal(int message, int value, int arcStrengthPercentage);
    void onSendSignalAutomaticMode(int rightWheelSpeed, int leftWheelSpeed);
    void onStopSignal();
    void terminateConnection();
};

#endif // UART_H
