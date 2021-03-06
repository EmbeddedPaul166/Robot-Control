#ifndef UART_H
#define UART_H

#include <QObject>
#include <wiringSerial.h>

class UART : public QObject
{
    Q_OBJECT
public:
    explicit UART(QObject *parent = nullptr);
private: 
    int m_fileDescriptor;
signals:
    void failedUART();
public slots:
    void onSendSignal(int message, int rightWheelSpeedTimesOneHundred, int leftWheelSpeedTimesOneHundred);
    void onStopSignal();
    void onTerminateConnection();
    void onInitiateUART();
};

#endif // UART_H
