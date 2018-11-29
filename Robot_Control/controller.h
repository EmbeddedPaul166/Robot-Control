#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <thread>
#include <mutex>

#include <QImage>

#include "framegenerator.h"
#include "view.h"


class Controller
{
public:
    Controller();
    virtual ~Controller();

    void setup(View *pView, FrameGenerator *pFrameGenerator);
    void initiateAccessingCameraVision();
    void orderCameraViewUpdate(QImage image);
private:
    void viewCallback(QImage image, void (View::*pUpdateCameraView)(QImage));
    FrameGenerator *m_pFrameGenerator;
    View *m_pView;
};

#endif // CONTROLLER_H
