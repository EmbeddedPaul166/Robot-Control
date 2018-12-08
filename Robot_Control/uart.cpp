#include <string>
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


void UART::onSendSignal(int message, int value, int arcStrengthPercentage)
{
    std::string valueInString = std::to_string(value);
    std::string arctStrengthPercentageInString = std::to_string(arcStrengthPercentage);
    if (message == 1)
    {
        if (message >= 100)
        {
            /*serialPutchar (m_fileDescriptor, 'a');
            serialPutchar (m_fileDescriptor, valueInString[0]);
            serialPutchar (m_fileDescriptor, valueInString[1]);
            serialPutchar (m_fileDescriptor, valueInString[2]);*/
        }
        else
        {
            /*serialPutchar (m_fileDescriptor, 'a');
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, valueInString[0]);
            serialPutchar (m_fileDescriptor, valueInString[1]);*/
        }

    }
    else if (message == 2)
    {
        if (message >= 100)
        {
            /*serialPutchar (m_fileDescriptor, 'b');
            serialPutchar (m_fileDescriptor, valueInString[0]);
            serialPutchar (m_fileDescriptor, valueInString[1]);
            serialPutchar (m_fileDescriptor, valueInString[2]);*/
        }
        else
        {
            /*serialPutchar (m_fileDescriptor, 'a');
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, valueInString[0]);
            serialPutchar (m_fileDescriptor, valueInString[1]);*/
        }

    }
    else if (message == 3)
    {
        if (message >= 100)
        {
            /*serialPutchar(m_fileDescriptor, 'c');
            serialPutchar (m_fileDescriptor, valueInString[0]);
            serialPutchar (m_fileDescriptor, valueInString[1]);
            serialPutchar (m_fileDescriptor, valueInString[2]);*/
        }
        else
        {
            /*serialPutchar (m_fileDescriptor, 'a');
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, valueInString[0]);
            serialPutchar (m_fileDescriptor, valueInString[1]);*/
        }

    }
    else if (message == 4)
    {
        if (message >= 100)
        {
            /*serialPutchar(m_fileDescriptor, 'd');
            serialPutchar (m_fileDescriptor, valueInString[0]);
            serialPutchar (m_fileDescriptor, valueInString[1]);
            serialPutchar (m_fileDescriptor, valueInString[2])
            serialPutchar (m_fileDescriptor, arctStrengthPercentageInString[0]);
            serialPutchar (m_fileDescriptor, arctStrengthPercentageInString[1]);*/
        }
        else
        {
            /*serialPutchar(m_fileDescriptor, 'd');
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, valueInString[0]);
            serialPutchar (m_fileDescriptor, valueInString[1])
            serialPutchar (m_fileDescriptor, arctStrengthPercentageInString[0]);
            serialPutchar (m_fileDescriptor, arctStrengthPercentageInString[1]);*/
        }

    }
    else if (message == 5)
    {
        if (message >= 100)
        {
            /*serialPutchar(m_fileDescriptor, 'e');
            serialPutchar (m_fileDescriptor, valueInString[0]);
            serialPutchar (m_fileDescriptor, valueInString[1]);
            serialPutchar (m_fileDescriptor, valueInString[2]);
            serialPutchar (m_fileDescriptor, arctStrengthPercentageInString[0]);
            serialPutchar (m_fileDescriptor, arctStrengthPercentageInString[1]);*/
        }
        else
        {
            /*serialPutchar(m_fileDescriptor, 'd');
            serialPutchar (m_fileDescriptor, '0');
            serialPutchar (m_fileDescriptor, valueInString[0]);
            serialPutchar (m_fileDescriptor, valueInString[1])
            serialPutchar (m_fileDescriptor, arctStrengthPercentageInString[0]);
            serialPutchar (m_fileDescriptor, arctStrengthPercentageInString[1]);*/
        }

    }
}

void UART::onInitiateAutomaticMode()
{
    //serialPutchar(m_fileDescriptor, 'f');
}

void UART::onExitAutomaticMode()
{
    //serialPutchar(m_fileDescriptor, 'f');
}

void UART::onSendSignalAutomaticMode(int rightWheelSpeed, int leftWheelSpeed)
{
    std::string rightWheelSpeedInString = std::to_string(rightWheelSpeed);
    std::string leftWheelSpeedInString = std::to_string(leftWheelSpeed);
    if (rightWheelSpeed >= 100)
    {
        /*serialPutchar (m_fileDescriptor, rightWheelSpeedInString[0]);
        serialPutchar (m_fileDescriptor, rightWheelSpeedInString[1]);
        serialPutchar (m_fileDescriptor, rightWheelSpeedInString[2]);*/
    }
    else
    {
        /*serialPutchar (m_fileDescriptor, '0');
        serialPutchar (m_fileDescriptor, rightWheelSpeedInString[0]);
        serialPutchar (m_fileDescriptor, rightWheelSpeedInString[1]);*/
    }
    if (leftWheelSpeed >= 100)
    {
        /*serialPutchar (m_fileDescriptor, leftWheelSpeedInString[0]);
        serialPutchar (m_fileDescriptor, leftWheelSpeedInString[1]);
        serialPutchar (m_fileDescriptor, leftWheelSpeedInString[2]);*/
    }
    else
    {
        /*serialPutchar (m_fileDescriptor, '0');
        serialPutchar (m_fileDescriptor, leftWheelSpeedInString[0]);
        serialPutchar (m_fileDescriptor, leftWheelSpeedInString[1]);*/
    }


}

void UART::onStopSignal()
{
    //serialPutchar(m_fileDescriptor, 'g')
}

void UART::terminateConnection()
{
    //serialClose(m_fileDescriptor);
}
