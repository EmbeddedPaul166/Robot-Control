#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

class Controller;

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr);
    ~View();

    void setup(Controller *pController);
    void initiateCameraViewUpdate(QImage image);
private:
    Ui::View *ui;
    int m_width;
    int m_height;
    QImage m_image;
    Controller *m_pController;
signals:
    void updateCameraView();
public slots:
    void onUpdateCameraView();

};

#endif // VIEW_H
