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
    int m_fileDescriptor;
signals:
    void failedUART();
public slots:
    void onSendSignal(int message, int value);
    void onStopSignal();
    void terminateConnection();
};

#endif // UART_H
