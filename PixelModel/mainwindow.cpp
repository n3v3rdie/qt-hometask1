#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "pixelmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new PixelModel(this))
{
    ui->setupUi(this);
    this->setWindowTitle("PixelModel");
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbSelectImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.xpm *.jpg)"));
    ui->labelImagePath->setText(fileName);
    model->setImage(QImage(fileName));
}
