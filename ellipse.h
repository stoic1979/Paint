#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

#include <QRect>

class Ellipse : public Shape
{
public:
    explicit Ellipse(const QPoint &topLeft);

    virtual void draw(QPainter &painter) override;

    virtual QRect rect() const override;

    virtual void update(const QPoint &lastPoint) override;

private:
    QRect r;
};

#endif // ELLIPSE_H
