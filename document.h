#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "shape.h"

#include <QWidget>

#include <list>
#include <memory>

class Document : public QWidget
{
    Q_OBJECT
public:
    explicit Document(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    std::unique_ptr<Shape> current;
    std::list<std::unique_ptr<Shape>> shapes;
};

#endif // DOCUMENT_H
