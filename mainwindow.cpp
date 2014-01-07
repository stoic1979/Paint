#include "mainwindow.h"

#include "document.h"
#include "shape.h"

#include <QtWidgets>

#include <functional>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    doc = new Document;
    doc->setShapeFactory(createRectangle);
    setCentralWidget(doc);

    createActions();
    createMenus();

    setWindowTitle(tr("Paint"));
    resize(500, 500);
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::open()
{
    if (maybeSave()) {
        const QString fileName =
            QFileDialog::getOpenFileName(this, tr("Open File"),
                                         QDir::currentPath());
        if (!fileName.isEmpty()) {
            doc->openImage(fileName);
        }
    }
}

void MainWindow::save()
{
    saveFile("bmp");
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(doc->getPenColor());
    if (newColor.isValid()) {
        doc->setPenColor(newColor);
    }
}

void MainWindow::penWidth()
{
    bool ok;
    const int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                              tr("Select pen width:"),
                                              doc->getPenWidth(),
                                              1, 50, 1, &ok);
    if (ok) {
        doc->setPenWidth(newWidth);
    }
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAsAct = new QAction("&Save As...", this);
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(save()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    flipHorizAct = new QAction(tr("Flip Horizontally"), this);
    connect(flipHorizAct, &QAction::triggered,
            std::bind(&Document::flip, doc, true, false));

    flipVerticAct = new QAction(tr("Flip Vertically"), this);
    connect(flipVerticAct, &QAction::triggered,
            std::bind(&Document::flip, doc, false, true));
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);

    effectsMenu = new QMenu(tr("&Effects"), this);
    effectsMenu->addAction(flipHorizAct);
    effectsMenu->addAction(flipVerticAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(effectsMenu);
}

bool MainWindow::maybeSave()
{
    if (doc->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Paint"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
              | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("bmp");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return doc->saveImage(fileName, fileFormat.constData());
    }
}
