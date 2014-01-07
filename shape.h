#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QRect>

#include <memory>

class Shape
{
public:
    Shape(int penWidth, const QColor& penColor);

    virtual ~Shape();

    void draw(QPainter &painter);

    QRect rect() const;

    void update(const QPoint &toPoint);

protected:
    virtual void doDraw(QPainter &painter) = 0;

    virtual QRect doRect() const = 0;

    virtual void doUpdate(const QPoint &toPoint) = 0;

private:
    int penWidth;
    QColor penColor;
};

std::unique_ptr<Shape> createEllipse(const QPoint &topLeft,
                                     int penWidth,
                                     const QColor& penColor);

std::unique_ptr<Shape> createRectangle(const QPoint &topLeft,
                                       int penWidth,
                                       const QColor& penColor);

std::unique_ptr<Shape> createScribble(const QPoint &topLeft,
                                      int penWidth,
                                      const QColor& penColor);

#endif // SHAPE_H
