#include "mainwindow.h"

#include "document.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(new Document);
}

MainWindow::~MainWindow()
{

}
