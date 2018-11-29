#include "view.h"
#include "ui_view.h"
#include "controller.h"
#include "globals.h"

View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View),
    m_width(),
    m_height(),
    m_pController(nullptr)
{
    ui->setupUi(this);
    connect(this, SIGNAL(updateCameraView()), this, SLOT(onUpdateCameraView()));
}

View::~View()
{
    delete ui;
}

void View::setup(Controller *pController)
{
    this->m_pController = pController;
}

void View::initiateCameraViewUpdate(QImage image)
{
    m_image = image;
    emit updateCameraView();
}


void View::onUpdateCameraView()
{
    frameMutex.lock();
    m_width = ui->cameraOutputLabel->width();
    m_height = ui->cameraOutputLabel->height();
    ui->cameraOutputLabel->setPixmap(QPixmap::fromImage(m_image.scaled(m_width, m_height,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
    frameMutex.unlock();
}
