#include "view.h"
#include "framegenerator.h"
#include "globals.h"
#include "ui_view.h"


View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View),
    m_width(0),
    m_height(0)

{
    ui->setupUi(this);
}

View::~View()
{
    delete ui;
}

void View::setup(FrameGenerator* pframe)
{
    connect(this, SIGNAL(startTransmission()), pframe, SLOT(onStartTransmission()));
    connect(pframe, SIGNAL(stream(QImage)), this, SLOT(onStream(QImage)));
    connect(this, SIGNAL(stop()),pframe, SLOT(onStop()));
}

void View::showEvent(QShowEvent *event)
{
    QTimer::singleShot(100, this, SLOT(showFullScreen()));
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

