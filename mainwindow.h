#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QTextStream>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void show_cvimg(cv::Mat &img, int);

    void on_button_open_under_clicked();

    void on_button_open_over_clicked();

    void on_button_calc_offset_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat image; // the image variable
    QStringList under_list, over_list;
};

#endif // MAINWINDOW_H
