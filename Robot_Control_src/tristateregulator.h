#ifndef TRISTATEREGULATOR_H
#define TRISTATEREGULATOR_H

enum class STEERING_SIGNAL
{
    MOVE_FORWARD,
    ARC_RIGHT,
    ARC_LEFT
};

class TristateRegulator
{
public:
    TristateRegulator();
    void calculate(int &middlePointXCoordinate, int &currentXCoordinate, int &zoneThreshold, STEERING_SIGNAL &action);
private:
    int m_error;
    int m_upperThreshold;
    int m_lowerThreshold;
};

#endif // TRISTATEREGULATOR_H
