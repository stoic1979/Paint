#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "document.h"

#include <QActionGroup>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void save();

    void penColor();
    void penWidth();

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    Document *doc;

    QMenu *fileMenu;
    QMenu *brushMenu;
    QMenu *effectsMenu;

    QAction *openAct;
    QAction *saveAsAct;
    QAction *exitAct;

    QAction *penColorAct;
    QAction *penWidthAct;

    QActionGroup *brushActionGroup;
    QAction *ellipseAct;
    QAction *eraserAct;
    QAction *rectAct;
    QAction *scribbleAct;

    QAction *flipHorizAct;
    QAction *flipVerticAct;
    QAction *rotateAct;
};

#endif // MAINWINDOW_H
