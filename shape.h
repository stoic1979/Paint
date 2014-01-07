#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPoint>
#include <QRect>

class Shape
{
public:

    virtual ~Shape();

    virtual void draw(QPainter &painter) = 0;

    virtual QRect rect() const = 0;

    virtual void update(const QPoint &lastPoint) = 0;
};

#endif // SHAPE_H
