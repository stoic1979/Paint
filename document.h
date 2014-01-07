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

    void flip(bool horiz, bool vert);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void resizeImage(QImage *image, const QSize &newSize);

    QImage image;
    bool modified;

    int penWidth;
    QColor penColor;

    std::unique_ptr<Shape> currentShape;
    std::list<std::unique_ptr<Shape>> shapes;
};

#endif // DOCUMENT_H
