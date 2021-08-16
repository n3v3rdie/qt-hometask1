#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pixelmodel.h"
#include "colordelegate.h"
#include <QFileDialog>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new PixelModel(this))
{
    ui->setupUi(this);
    this->setWindowTitle("PixelModel");
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new ColorDelegate(ui->tableView));
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
