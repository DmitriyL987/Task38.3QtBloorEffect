#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}
//-----------------

MainWindow::~MainWindow()
{
    delete ui;
}
//------------------

void MainWindow::init(){
    label = ui->label;
    slider = ui->horizontalSlider;
    slider->setMinimum(0);
    slider->setMaximum(100);
    menu = ui->menuMenu;
    stat = new QLabel("Ready");
    ui->statusbar->addWidget(stat);
}
//--------------

QPixmap* MainWindow::blurImage(){
    if(!qImageLoaded || image->isNull()) return nullptr;
    image->fill(Qt::transparent);
    QPainter paint(image);
    scene->render(&paint, QRectF(),QRectF(0, 0, image->width(), image->height()));
    stat->setText("Edit image " + fName + "." + fEx);
    return image;
}
//--------------

void MainWindow::openFile(){
    if(blur == nullptr) {
        blur = new QGraphicsBlurEffect;
        blur->setBlurRadius(0.0);
    }
    if(item == nullptr)item = new QGraphicsPixmapItem;
    if (image == nullptr) image = new QPixmap;
    QString oldFileName(fileFullName);
    fileFullName = QFileDialog::getOpenFileName(0, tr("open image"),
                   "E:/Code/QTCreator", tr("Image Files (*.png *.jpg *.bmp)"));
    if(fileFullName.isNull()) {
        fileFullName = oldFileName;
        return;
    }
    qImageLoaded = image->load(fileFullName,"*.JPG", Qt::AutoColor);//*.png тоже загружает!

    if(qImageLoaded){
        QFileInfo infoFile(fileFullName);
        fName = infoFile.baseName();
        fEx = infoFile.suffix();
        dir_Name = infoFile.path();
            //qDebug() << dir_Name;
            //qDebug() << fName;
            //qDebug() << fEx;
        item->setPixmap(*image);
        item->setGraphicsEffect(blur);
        if(scene == nullptr) scene = new QGraphicsScene;
        scene->addItem(item);
        label->setPixmap(*image);
       stat->setText("Loaded " + fName + "." + fEx);
    } else {
        //label->setText("Error! Failed open file.");
        stat->setText("Error! Failed open file.");
    }
}
//-----------------------------

void MainWindow::saveFile(){
    if(qImageLoaded && image != nullptr)
    {
        bool res = false;
        QString se(dir_Name + "/blur_" + fName + "." + fEx);
        //*image = label->pixmap();
        res = image->save(se);
        if (res) stat->setText("Saving successfully. Path: " + se);
        else stat->setText("Failed save file.");
    } else {
        stat->setText("Nothing to save");
    }
}
//------------------------------

void MainWindow::closeFile(){
    scene->clear();
    label->clear();
    if(item) item = nullptr;
    if(image != nullptr)
    {
        qImageLoaded = false;
        slider->setValue(0);
        delete image;
        image = nullptr;
        fileFullName = "";
        blur = nullptr;
        stat->setText("The file is closed");
    } else stat->setText("Failed close file!");
}
//---------------------------

void MainWindow::saveAs(){
    if(qImageLoaded && image != nullptr)
    {
        bool res = false;
        QString directory = QFileDialog::getSaveFileName(this,tr("Save as"), dir_Name,
                                       tr("Images (*.png *.xpm *.jpg)"));
        if(directory.isNull()) return;
        QString se(directory);
        res = image->save(se);
        if (res) stat->setText("Saving successfully. Path: " + se);
        else stat->setText("Failed save file.");
    } else {
        stat->setText("Nothing to save");
    }
}
//---------------------------

void MainWindow::valueChange()
{
    if(qImageLoaded && !image->isNull() && blur) {
        qreal value = slider->value();
        radiusEff = value/10;
        blur->setBlurRadius(radiusEff);
        label->setPixmap(*blurImage());
    } else {
        radiusEff = 0.0;
        slider->setValue(0);
    }
}

