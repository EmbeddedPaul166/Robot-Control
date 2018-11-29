#include "uart.h"

UART::UART(QObject *parent) :
QObject(parent),
m_fileDescriptor()
{

}

void UART::initiateUART()
{
    /*m_fileDescriptor = serialOpen("/dev/ttyAMA0", 115200);
    if (m_fileDescriptor < 0)
    {
        emit failedUART();
    }*/
}

void UART::onSendSignal(int message, int value)
{
    if (message == 1)
    {
        /*serialPutchar (m_fileDescriptor, 'A');
        serialPutchar (m_fileDescriptor, value)*/
    }
    else if (message == 2)
    {
        /*serialPutchar (m_fileDescriptor, 'B');
        serialPutchar (m_fileDescriptor, value)*/
    }
    else if (message == 3)
    {
        /*serialPutchar (m_fileDescriptor, 'C');
        serialPutchar (m_fileDescriptor, value)*/
    }
    else if (message == 4)
    {
        /*serialPutchar (m_fileDescriptor, 'D');
        serialPutchar (m_fileDescriptor, value)*/
    }
    else if (message == 5)
    {
        /*serialPutchar (m_fileDescriptor, 'E');
        serialPutchar (m_fileDescriptor, value)*/
    }
    else if (message == 6)
    {
        // automatic mode...
    }

}

void UART::onStopSignal()
{

}

void UART::terminateConnection()
{
    //serialClose(m_fileDescriptor);
}
