#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPoint>
#include <QRect>

class Shape
{
public:

    Shape(int penWidth, const QColor& penColor);

    virtual ~Shape();

    void draw(QPainter &painter);

    virtual QRect rect() const = 0;

    virtual void update(const QPoint &lastPoint) = 0;

protected:
    virtual void doDraw(QPainter &painter) = 0;

private:
    int penWidth;
    QColor penColor;
};

#endif // SHAPE_H
