#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

#include <QRect>

class Rectangle : public Shape
{
public:
    explicit Rectangle(const QPoint &topLeft, int penWidth, const QColor& penColor);

    virtual QRect rect() const override;

    virtual void update(const QPoint &lastPoint) override;

protected:
    virtual void doDraw(QPainter &painter) override;

private:
    QRect r;
};

#endif // RECTANGLE_H
