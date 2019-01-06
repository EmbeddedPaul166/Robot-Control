#include <stdlib.h>
#include "tristateregulator.h"

TristateRegulator::TristateRegulator() :
m_error()
{
    //do nothing...
}

void TristateRegulator::calculate(int &middlePointXCoordinate, int &currentXCoordinate, int &zoneThreshold, STEERING_SIGNAL &action)
{
    m_error = currentXCoordinate - middlePointXCoordinate ;
    m_upperThreshold = zoneThreshold/2;
    m_lowerThreshold = -zoneThreshold/2;
    if (m_error <= m_upperThreshold && m_error >= m_lowerThreshold) //move forward
    {
        action = STEERING_SIGNAL::MOVE_FORWARD;
    }
    else if (m_error > m_upperThreshold) //arc right
    {
        action = STEERING_SIGNAL::ARC_RIGHT;
    }
    else if (m_error < m_lowerThreshold) //arc left
    {
        action = STEERING_SIGNAL::ARC_LEFT;
    }
}
