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

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    bool isModified() const { return modified; }
    QColor getPenColor() const { return penColor; }
    int getPenWidth() const { return penWidth; }

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    bool modified;

    int penWidth;
    QColor penColor;

    std::unique_ptr<Shape> currentShape;
    std::list<std::unique_ptr<Shape>> shapes;
};

#endif // DOCUMENT_H
