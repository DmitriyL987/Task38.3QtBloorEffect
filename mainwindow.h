#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <QFileDialog>
#include <QMenuBar>
#include <QtGui/QtGui>
#include <QImage>
#include <QPainter>
#include <QFileInfo>
#include <QGraphicsScene>
#include <QGraphicsEffect>
#include <QGraphicsPixmapItem>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();

private:
    int valSlider = 0;
    bool qImageLoaded = false;
    Ui::MainWindow *ui;
    QSlider *slider;
    QString fileFullName;
    QString fName;
    QString fEx;
    QString dir_Name;
    QLabel *label;
    QLabel *stat;
    QFileDialog *dialog;
    QMenu *menu;
    QGraphicsScene *scene = nullptr;
    QGraphicsPixmapItem *item = nullptr;
    QGraphicsBlurEffect *blur = nullptr;
    QPixmap *image = nullptr;
    qreal radiusEff = 0.0;

//---- function ----
    QPixmap* blurImage();

public slots:
    void valueChange();
    void openFile();
    void saveFile();
    void closeFile();
    void saveAs();
};
#endif // MAINWINDOW_H
