#include <string>
#include "uart.h"


UART::UART(QObject *parent) :
QObject(parent),
m_fileDescriptor()
{
    //do nothing...
}

void UART::initiateUART()
{
    m_fileDescriptor = serialOpen("/dev/ttyAMA0", 115200);
    if (m_fileDescriptor < 0)
    {
        emit failedUART();
    }
}


void UART::onSendSignal(int message, int rightWheelSpeedTimesOneHundred, int leftWheelSpeedTimesOneHundred)
{
    std::string rightWheelSpeedTimesOneHundredInString = std::to_string(rightWheelSpeedTimesOneHundred);
    std::string leftWheelSpeedTimesOneHundredInString = std::to_string(leftWheelSpeedTimesOneHundred);
    if (message == 1)
    {
        if (rightWheelSpeedTimesOneHundred >= 1000 && leftWheelSpeedTimesOneHundred >= 1000)
        {
            serialPutchar (m_fileDescriptor, 'a');
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[3]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[3]);
        }
        else if (rightWheelSpeedTimesOneHundred < 1000 && leftWheelSpeedTimesOneHundred >= 1000)
        {
            serialPutchar (m_fileDescriptor, 'a');
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[3]);
        }
        else if (rightWheelSpeedTimesOneHundred >= 1000 && leftWheelSpeedTimesOneHundred < 1000)
        {
            serialPutchar (m_fileDescriptor, 'a');
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[3]);
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[2]);
        }
        else if (rightWheelSpeedTimesOneHundred < 1000 && leftWheelSpeedTimesOneHundred < 1000)
        {
            serialPutchar (m_fileDescriptor, 'a');
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[2]);
        }

    }
    else if (message == 2)
    {
        if (rightWheelSpeedTimesOneHundred >= 1000)
        {
            serialPutchar (m_fileDescriptor, 'b');
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[3]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[3]);
        }
        else
        {
            serialPutchar (m_fileDescriptor, 'a');
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[2]);
        }

    }
    else if (message == 3)
    {
        if (rightWheelSpeedTimesOneHundred >= 1000)
        {
            serialPutchar(m_fileDescriptor, 'c');
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[3]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[3]);
        }
        else
        {
            serialPutchar (m_fileDescriptor, 'a');
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, rightWheelSpeedTimesOneHundredInString[2]);
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[0]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[1]);
            serialPutchar (m_fileDescriptor, leftWheelSpeedTimesOneHundredInString[2]);
        }

    }
}





void UART::onStopSignal()
{
    serialPutchar(m_fileDescriptor, 'g')
}

void UART::onTerminateConnection()
{
    serialClose(m_fileDescriptor);
}
