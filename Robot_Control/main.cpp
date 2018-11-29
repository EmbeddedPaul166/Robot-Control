#include "view.h"
#include "framegenerator.h"
#include "uart.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FrameGenerator frameGenerator;
    View view;
    UART serial;
    view.setup(&frameGenerator, &serial);
    view.show();
    return a.exec();
}
