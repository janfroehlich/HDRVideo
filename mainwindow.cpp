#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <QTextStream>
#include <QFileDialog>
#include <QTime>
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*Method that converts cv::Mat to QImage and displays it on a label
 *@param    &img    pointer to cv::Mat
 *@param    f       index of target label (0 -> left, 1 -> right)
 */
void MainWindow::show_cvimg(cv::Mat &img, int f)
{
    // change color channel ordering from BGR to RGB
    cv::Mat img_new;
    cv::cvtColor(img,img_new,CV_BGR2RGB);
    ui->label_loaded->setNum(img_new.depth());
    //double shift = qPow(2,4);
    //cv::convertScaleAbs(img_new,img_new,0.25,shift);
    // convert cv::Mat to QImage and resize the image to fit the lable
    QImage qimg= QImage((const unsigned char*)(img_new.data),img_new.cols,img_new.rows,QImage::Format_RGB888);
    qimg = qimg.scaledToWidth(500);
    // display QImage on label
    if (f == 0)
    {
        ui->img_under->setPixmap(QPixmap::fromImage(qimg));
        ui->img_under->resize(ui->img_under->pixmap()->size());
    }
    else if (f == 1)
    {
        ui->img_over->setPixmap(QPixmap::fromImage(qimg));
        ui->img_over->resize(ui->img_over->pixmap()->size());
    }
}

void MainWindow::on_button_open_under_clicked()
{
    under_list = QFileDialog::getOpenFileNames(this,tr("Open underexposed Images"), ".",tr("Image Files (*.exr)"));
    image= cv::imread(under_list[0].toLatin1().data());
    //image = cvLoadImage(under_list[0].toLatin1().data(),2);
    show_cvimg(image,0);
}

void MainWindow::on_button_open_over_clicked()
{
    over_list = QFileDialog::getOpenFileNames(this,tr("Open overexposed Images"), ".",tr("Image Files (*.exr)"));

    image= cv::imread(over_list[0].toLatin1().data());
    //image = cvLoadImage(over_list[0].toLatin1().data(),2);
    show_cvimg(image,1);
}

void MainWindow::on_button_calc_offset_clicked()
{
    cv::Mat under_img = cv::imread(under_list[0].toLatin1().data());
    cv::Mat over_img  = cv::imread(under_list[0].toLatin1().data());

    std::vector< cv::KeyPoint > keypoints_under;
    std::vector< cv::KeyPoint > keypoints_over;

    cv::SurfFeatureDetector surfer(2500.);
    surfer.detect(under_img,keypoints_under);
    surfer.detect(over_img,keypoints_over);

    cv::drawKeypoints(under_img,keypoints_under,under_img,cv::Scalar(255,0,0),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::drawKeypoints(over_img,keypoints_over,over_img,cv::Scalar(255,0,0),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    show_cvimg(under_img,0);
    show_cvimg(over_img,0);
}
