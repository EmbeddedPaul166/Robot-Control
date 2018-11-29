#include "view.h"
#include "framegenerator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FrameGenerator frameGenerator;
    View view;
    view.setup(&frameGenerator);
    view.show();
    return a.exec();
}
