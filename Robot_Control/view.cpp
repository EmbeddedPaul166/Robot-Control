#include <QKeyEvent>
#include <math.h>
#include "view.h"
#include "framegenerator.h"
#include "uart.h"
#include "ui_view.h"


View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View),
    m_width(0),
    m_height(0),
    m_maximumSpeed(36), //Edit to change max speed value!!! Also remember to change the initial value on the speedSliderLabel and change minimum value on the slider!!!
    isAutomaticModeOn(false),
    m_isKeyPressed(false)
{
    ui->setupUi(this);
}

View::~View()
{
    delete ui;
}

void View::setup(FrameGenerator* pframe, UART *pUART) //declare signal and slot connections
{
    connect(this, SIGNAL(startTransmission()), pframe, SLOT(onStartTransmission()));
    connect(pframe, SIGNAL(stream(QImage)), this, SLOT(onStream(QImage)), Qt::DirectConnection);
    connect(pframe, SIGNAL(sendInstructionInAutomaticMode(int, QString)), this, SLOT(onSendInstructionInAutomaticMode(int, QString)));
    connect(pframe, SIGNAL(stopInstruction()), this, SLOT(onStopInstruction()));
    connect(this, SIGNAL(sendInfoAboutAutomaticMode()),pframe, SLOT(onSendInfoAboutAutomaticMode()));
    connect(this, SIGNAL(stop()),pframe, SLOT(onStop()), Qt::DirectConnection);
    connect(this, SIGNAL(sendSignal(int, int, int)), pUART, SLOT(onSendSignal(int, int, int)));
    connect(pUART , SIGNAL(failedUART()),this , SLOT(onFailedUART()));
    connect(this, SIGNAL(stopSignal()),pUART, SLOT(onStopSignal()));
    connect(ui->moveForwardButton, SIGNAL(pressed()),this , SLOT(onButtonPressed()));
    connect(ui->turnRightButton, SIGNAL(pressed()),this , SLOT(onButtonPressed()));
    connect(ui->turnLeftButton, SIGNAL(pressed()),this , SLOT(onButtonPressed()));
    connect(ui->arcRightButton, SIGNAL(pressed()),this , SLOT(onButtonPressed()));
    connect(ui->arcLeftButton, SIGNAL(pressed()),this , SLOT(onButtonPressed()));
    connect(ui->automaticModeButton, SIGNAL(clicked()),this , SLOT(onButtonClicked()));
    connect(ui->exitButton, SIGNAL(clicked()),this , SLOT(onButtonClicked()));
    connect(ui->moveForwardButton, SIGNAL(released()),this , SLOT(onButtonReleased()));
    connect(ui->turnRightButton, SIGNAL(released()),this , SLOT(onButtonReleased()));
    connect(ui->turnLeftButton, SIGNAL(released()),this , SLOT(onButtonReleased()));
    connect(ui->arcRightButton, SIGNAL(released()),this , SLOT(onButtonReleased()));
    connect(ui->arcLeftButton, SIGNAL(released()),this , SLOT(onButtonReleased()));
    connect(ui->speedSlider, SIGNAL(valueChanged(int)),this , SLOT(onSliderChange(int)));
    connect(ui->arcStrengthSlider, SIGNAL(valueChanged(int)),this , SLOT(onSliderChange(int)));
    connect(this, SIGNAL(keyPressed(QString)),this , SLOT(onKeyPressed(QString)));
    connect(this, SIGNAL(keyReleased()),this , SLOT(onKeyReleased()));
    connect(this, SIGNAL(initiateUART()), pUART, SLOT(onInitiateUART()));
    connect(pframe, SIGNAL(startTimerSingleShot()), pframe, SLOT(onStartTimerSingleShot()));
    connect(pframe, SIGNAL(stopTimer()), pframe, SLOT(onStopTimer()));
    emit initiateUART(); //comment this to see uart messages in console
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else if(event->key() == Qt::Key_W)
    {
        this->grabKeyboard();
        emit keyPressed("W");
    }
    else if (event->key() == Qt::Key_D)
    {
        this->grabKeyboard();
        emit keyPressed("D");
    }
    else if (event->key() == Qt::Key_A)
    {
        this->grabKeyboard();
        emit keyPressed("A");
    }
    else if (event->key() == Qt::Key_E)
    {
        this->grabKeyboard();
        emit keyPressed("E");
    }
    else if (event->key() == Qt::Key_Q)
    {
        this->grabKeyboard();
        emit keyPressed("Q");
    }
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else if(event->key() == Qt::Key_W)
    {
        this->releaseKeyboard();
        emit keyReleased();
    }
    else if (event->key() == Qt::Key_D)
    {
        this->releaseKeyboard();
        emit keyReleased();
    }
    else if (event->key() == Qt::Key_A)
    {
        this->releaseKeyboard();
        emit keyReleased();
    }
    else if (event->key() == Qt::Key_E)
    {
        this->releaseKeyboard();
        emit keyReleased();
    }
    else if (event->key() == Qt::Key_Q)
    {
        this->releaseKeyboard();
        emit keyReleased();
    }
}

void View::showEvent(QShowEvent *event)
{
    this->setWindowState(Qt::WindowFullScreen);
    emit startTransmission();
}

void View::closeEvent(QCloseEvent *event)
{
    emit stop();
    emit stopSignal();
}


void View::onStream(QImage img)
{
    m_width = ui->cameraOutputLabel->width();

    m_height = ui->cameraOutputLabel->height();

    ui->cameraOutputLabel->setPixmap(QPixmap::fromImage(img.scaled(m_width, m_height,Qt::KeepAspectRatio,Qt::SmoothTransformation))); //draw camera frame
}

void View::onStopInstruction()
{
    emit stopSignal();
}

void View::onSendInstructionInAutomaticMode(int imageArea, QString steeringSignal)
{
    double speedSliderValue = ui->speedSlider->value();
    if (steeringSignal == "Move forward")
    {
        if (imageArea == 5)
        {
            int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
            int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
            emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
        }
    }
    else if (steeringSignal == "Arc left")
    {
        if (imageArea == 1)
        {
            int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
            int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(50)*0.01);
            emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
        }
        else if (imageArea == 2)
        {
            int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
            int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(65)*0.01);
            emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
        }
        else if (imageArea == 3)
        {
            int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
            int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(80)*0.01);
            emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
        }
        else if (imageArea == 4)
        {
            int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
            int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(95)*0.01);
            emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
        }
    }
    else if (steeringSignal == "Arc right")
    {
        if (imageArea == 6)
        {
            int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(95)*0.01);
            int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
            emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
        }
        else if (imageArea == 7)
        {
            int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(80)*0.01);
            int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
            emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
        }
        else if (imageArea == 8)
        {
            int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(65)*0.01);
            int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
            emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
        }
        else if (imageArea == 9)
        {
            int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(50)*0.01);
            int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
            emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
        }
    }
}

void View::onButtonPressed()
{
    double speedSliderValue = ui->speedSlider->value();
    int arcStrengthPercentageValue = ui->arcStrengthSlider->value();
    if (sender() == ui->moveForwardButton)
    {
        int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
    }
    else if (sender() == ui->turnRightButton)
    {
        int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        emit sendSignal(2, rightWheelSpeed, leftWheelSpeed);
    }
    else if (sender() == ui->turnLeftButton)
    {
        int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        emit sendSignal(3, rightWheelSpeed, leftWheelSpeed);
    }
    else if (sender() == ui->arcRightButton)
    {
        int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(arcStrengthPercentageValue)*0.01);
        int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
    }
    else if (sender() == ui->arcLeftButton)
    {
        int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(arcStrengthPercentageValue)*0.01);
        emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
    }
}

void View::onButtonClicked()
{
    if (sender() == ui->automaticModeButton)
    {
        isAutomaticModeOn = !isAutomaticModeOn;
        if (isAutomaticModeOn)
        {
            ui->moveForwardButton->setEnabled(false);
            ui->turnRightButton->setEnabled(false);
            ui->turnLeftButton->setEnabled(false);
            ui->arcRightButton->setEnabled(false);
            ui->arcLeftButton->setEnabled(false);
            ui->automaticModeButton->setText("Turn off automatic mode");
            emit sendInfoAboutAutomaticMode();
        }
        else if (!isAutomaticModeOn)
        {
            ui->moveForwardButton->setEnabled(true);
            ui->turnRightButton->setEnabled(true);
            ui->turnLeftButton->setEnabled(true);
            ui->arcRightButton->setEnabled(true);
            ui->arcLeftButton->setEnabled(true);
            ui->automaticModeButton->setText("Turn on automatic mode");
            emit sendInfoAboutAutomaticMode();
        }
    }
    else if (sender() == ui->exitButton)
    {
        this->close();
    }
}

void View::onButtonReleased()
{
    emit stopSignal();
}

void View::onKeyPressed(QString keyName)
{
    double speedSliderValue = ui->speedSlider->value();
    int arcStrengthPercentageValue = ui->arcStrengthSlider->value();
    if (keyName == "W")
    {
        int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
    }
    else if (keyName == "D")
    {
        int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        emit sendSignal(2, rightWheelSpeed, leftWheelSpeed);
    }
    else if (keyName == "A")
    {
        int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        emit sendSignal(3, rightWheelSpeed, leftWheelSpeed);
    }
    else if (keyName == "E")
    {
        int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(arcStrengthPercentageValue)*0.01);
        int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
    }
    else if (keyName == "Q")
    {
        int rightWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed);
        int leftWheelSpeed = static_cast<int>(speedSliderValue*m_maximumSpeed*static_cast<double>(arcStrengthPercentageValue)*0.01);
        emit sendSignal(1, rightWheelSpeed, leftWheelSpeed);
    }
}

void View::onKeyReleased()
{
    emit stopSignal();
}


void View::onSliderChange(int sliderValue)
{
    if (sender() == ui->speedSlider)
    {
        double calculatedSpeed = static_cast<int>(sliderValue)*m_maximumSpeed*0.01;
        ui->speedDisplayLabel->setText(QString::number(calculatedSpeed));
    }
    else if (sender() == ui->arcStrengthSlider)
    {
        ui->arcStrengthDisplayLabel->setText(QString::number(sliderValue) + "%");
    }

}

void View::onFailedUART()
{
    ui->speedLabel->setText("ERROR: UART CONNECTION NOT ESTABLISHED");
}

