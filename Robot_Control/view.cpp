#include "view.h"
#include "framegenerator.h"
#include "uart.h"
#include "globals.h"
#include "ui_view.h"


View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View),
    m_width(0),
    m_height(0),
    m_maximumSpeed(2),
    isAutomaticModeOn(false)

{
    ui->setupUi(this);
}

View::~View()
{
    delete ui;
}

void View::setup(FrameGenerator* pframe, UART *pUART)
{
    connect(this, SIGNAL(startTransmission()), pframe, SLOT(onStartTransmission()));
    connect(pframe, SIGNAL(stream(QImage)), this, SLOT(onStream(QImage)));
    connect(this, SIGNAL(stop()),pframe, SLOT(onStop()));
    connect(this, SIGNAL(sendSignal(int, int, int)),pUART, SLOT(onSendSignal(int, int, int)));
    connect(this, SIGNAL(sendSignalAutomaticMode(int, int)),pUART, SLOT(onSendSignalAutomaticMode(int, int)));
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
    connect(ui->automaticModeButton, SIGNAL(clicked()),this , SLOT(onTurnAutomaticModeButtonClick()));
}

void View::showEvent(QShowEvent *event)
{
    //QTimer::singleShot(100, this, SLOT(showFullScreen()));
    this->setWindowState(Qt::WindowFullScreen);
    emit startTransmission();
}

void View::closeEvent(QCloseEvent *event)
{
    emit stop();
}


void View::onStream(QImage img)
{
    out.acquire();
    m_width = ui->cameraOutputLabel->width();
    m_height = ui->cameraOutputLabel->height();
    ui->cameraOutputLabel->setPixmap(QPixmap::fromImage(img.scaled(m_width, m_height,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
    in.release();
}

void View::onButtonPressed()
{
    int speedSliderValue = ui->speedSlider->value();
    int arcStrengthPercentageValue = ui->arcStrengthSlider->value();
    int calculatedSpeed = speedSliderValue*static_cast<int>(m_maximumSpeed);
    if (sender() == ui->moveForwardButton)
    {
        emit sendSignal(1, calculatedSpeed, arcStrengthPercentageValue);
    }
    else if (sender() == ui->turnRightButton)
    {
        emit sendSignal(2, calculatedSpeed, arcStrengthPercentageValue);
    }
    else if (sender() == ui->turnLeftButton)
    {
        emit sendSignal(3, calculatedSpeed, arcStrengthPercentageValue);
    }
    else if (sender() == ui->arcRightButton)
    {
        emit sendSignal(4, calculatedSpeed, arcStrengthPercentageValue);
    }
    else if (sender() == ui->arcLeftButton)
    {
        emit sendSignal(5, calculatedSpeed, arcStrengthPercentageValue);
    }
}

void View::onButtonClicked()
{
    if (sender() == ui->automaticModeButton)
    {
        //something...
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

void View::onTurnAutomaticModeButtonClick()
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
    }
    else if (!isAutomaticModeOn)
    {
        ui->moveForwardButton->setEnabled(true);
        ui->turnRightButton->setEnabled(true);
        ui->turnLeftButton->setEnabled(true);
        ui->arcRightButton->setEnabled(true);
        ui->arcLeftButton->setEnabled(true);
        ui->automaticModeButton->setText("Turn on automatic mode");
    }
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
    ui->speedDisplayLabel->setText("ERROR: UART CONNECTION NOT ESTABLISHED");
}

