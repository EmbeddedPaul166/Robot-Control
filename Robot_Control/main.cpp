#include "view.h"
#include "controller.h"
#include "framegenerator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FrameGenerator frameGenerator;
    View view;
    Controller controller;

    controller.setup(&view, &frameGenerator);
    frameGenerator.setup(&controller);
    view.setup(&controller);


    view.show();
    controller.initiateAccessingCameraVision();
    return a.exec();
}
