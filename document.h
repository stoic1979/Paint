#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "shape.h"

#include <QUndoStack>
#include <QWidget>

#include <functional>
#include <list>
#include <memory>

class Document : public QWidget
{
    Q_OBJECT
public:
    typedef std::function<
        std::unique_ptr<Shape>(
            const QPoint&, int, const QColor&)> shape_factory_t;

    explicit Document(QUndoStack *undoStack, QWidget *parent = 0);

    void pushShape(Shape *shape);
    void popShape();

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    void setShapeFactory(shape_factory_t f);

    bool isModified() const { return modified; }
    QColor getPenColor() const { return penColor; }
    int getPenWidth() const { return penWidth; }

    void flip(bool horiz, bool vert);
    void rotate(qreal deg);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void resizeImage(QImage *image, const QSize &newSize);

    QImage image;
    QUndoStack *undoStack;

    bool modified;

    int penWidth;
    QColor penColor;

    shape_factory_t factory;

    std::unique_ptr<Shape> currentShape;
    std::list<Shape*> shapes;
};

#endif // DOCUMENT_H
