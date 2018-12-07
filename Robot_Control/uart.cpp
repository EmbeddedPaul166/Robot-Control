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

void UART::codeSignal3Digit(int value, int &ones, int &tenths, int &hundredths)
{
    std::string message = std::to_string(value);
    ones = message[0] - 48;
    tenths = message[1] - 48;
    hundredths = message[2] - 48;
}

void UART::codeSignal2Digit(int value, int &tens, int &ones)
{
    std::string message = std::to_string(value);
    tens = message[0] - 48;
    ones = message[1] - 48;
}

void UART::onSendSignal(int message, int value, int arcStrengthPercentage)
{
    int onesOfValue;
    int tenthsOfValue;
    int hundredthsOfValue;
    codeSignal3Digit(value, onesOfValue, tenthsOfValue, hundredthsOfValue);
    int tensOfArcStrengthPercentage;
    int onesOfArcStrengthPercentage;
    codeSignal2Digit(arcStrengthPercentage, tensOfArcStrengthPercentage, onesOfArcStrengthPercentage);
    if (message == 1)
    {
        /*serialPutchar (m_fileDescriptor, 'a');
        serialPutchar (m_fileDescriptor, ones);
        serialPutchar (m_fileDescriptor, tenths);
        serialPutchar (m_fileDescriptor, hundredths);*/
    }
    else if (message == 2)
    {
        /*serialPutchar (m_fileDescriptor, 'b');
        serialPutchar (m_fileDescriptor, ones);
        serialPutchar (m_fileDescriptor, tenths);
        serialPutchar (m_fileDescriptor, hundredths);*/
    }
    else if (message == 3)
    {
        /*serialPutchar(m_fileDescriptor, 'c');
        serialPutchar (m_fileDescriptor, ones);
        serialPutchar (m_fileDescriptor, tenths);
        serialPutchar (m_fileDescriptor, hundredths);*/
    }
    else if (message == 4)
    {
        /*serialPutchar(m_fileDescriptor, 'd');
        serialPutchar (m_fileDescriptor, ones);
        serialPutchar (m_fileDescriptor, tenths);
        serialPutchar (m_fileDescriptor, hundredths)
        serialPutchar (m_fileDescriptor, tensOfArcStrengthPercentage);
        serialPutchar (m_fileDescriptor, onesOfArcStrengthPercentage);*/
    }
    else if (message == 5)
    {
        /*serialPutchar(m_fileDescriptor, 'e');
        serialPutchar (m_fileDescriptor, ones);
        serialPutchar (m_fileDescriptor, tenths);
        serialPutchar (m_fileDescriptor, hundredths);
        serialPutchar (m_fileDescriptor, tensOfArcStrengthPercentage);
        serialPutchar (m_fileDescriptor, onesOfArcStrengthPercentage);*/
    }
    else if (message == 6)
    {
        //serialPutchar(m_fileDescriptor, 'f');
    }
}

void UART::onSendSignalAutomaticMode(int rightWheelSpeed, int leftWheelSpeed)
{
    int onesOfRightWheelSpeed;
    int tenthsOfRightWheelSpeed;
    int hundredthsOfRightWheelSpeed;
    codeSignal3Digit(rightWheelSpeed, onesOfRightWheelSpeed, tenthsOfRightWheelSpeed, hundredthsOfRightWheelSpeed);
    int onesOfLeftWheelSpeed;
    int tenthsOfLeftWheelSpeed;
    int hundredthsOfLeftWheelSpeed;
    codeSignal3Digit(leftWheelSpeed, onesOfLeftWheelSpeed, tenthsOfLeftWheelSpeed, hundredthsOfLeftWheelSpeed);
    /*serialPutchar (m_fileDescriptor, onesOfRightWheelSpeed);
    serialPutchar (m_fileDescriptor, tenthsOfRightWheelSpeed);
    serialPutchar (m_fileDescriptor, hundredthsOfRightWheelSpeed);
    serialPutchar (m_fileDescriptor, onesOfLeftWheelSpeed);
    serialPutchar (m_fileDescriptor, tenthsOfLeftWheelSpeed);
    serialPutchar (m_fileDescriptor, hundredthsOfLeftWheelSpeed);*/
}

void UART::onStopSignal()
{
    //serialPutchar(m_fileDescriptor, 'g')
}

void UART::terminateConnection()
{
    //serialClose(m_fileDescriptor);
}
