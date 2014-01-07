#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

#include <QRect>

class Rectangle : public Shape
{
public:
    explicit Rectangle(const QPoint &topLeft);

    virtual void draw(QPainter &painter) override;

    virtual QRect rect() const override;

    virtual void update(const QPoint &lastPoint) override;

private:
    QRect r;
};

#endif // RECTANGLE_H
