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
    m_maximumSpeed(2)

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
    connect(this, SIGNAL(sendSignal(int, int)),pUART, SLOT(onSendSignal(int, int)));
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
    int calculatedSpeed = speedSliderValue*static_cast<int>(m_maximumSpeed);
    if (sender() == ui->moveForwardButton)
    {
        emit sendSignal(1, calculatedSpeed);
    }
    else if (sender() == ui->turnRightButton)
    {
        emit sendSignal(2, calculatedSpeed);
    }
    else if (sender() == ui->turnLeftButton)
    {
        emit sendSignal(3, calculatedSpeed);
    }
    else if (sender() == ui->arcRightButton)
    {
        emit sendSignal(4, calculatedSpeed);
    }
    else if (sender() == ui->arcLeftButton)
    {
        emit sendSignal(5, calculatedSpeed);
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

void View::onSliderChange(int sliderValue)
{
    double calculatedSpeed = static_cast<int>(sliderValue)*m_maximumSpeed*0.01;
    ui->speedDisplayLabel->setText(QString::number(calculatedSpeed));
}

void View::onFailedUART()
{
    ui->speedDisplayLabel->setText("ERROR: UART CONNECTION NOT ESTABLISHED");
}

