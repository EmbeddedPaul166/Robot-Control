#ifndef VIEW_H
#define VIEW_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QImage>
#include <QMainWindow>

class FrameGenerator;

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    ~View();
    void setup(FrameGenerator* pframe);

private:
    Ui::View *ui;
    int m_width;
    int m_height;
    void closeEvent (QCloseEvent *event);
    void showEvent(QShowEvent *event);
signals:
    void startTransmission();
    void stop();
public slots:
    void onStream(QImage img);

};

#endif // VIEW_H
