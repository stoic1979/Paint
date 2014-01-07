#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

#include <QRect>

class Ellipse : public Shape
{
public:
    explicit Ellipse(const QPoint &topLeft, int penWidth, const QColor& penColor);

    virtual QRect rect() const override;

    virtual void update(const QPoint &lastPoint) override;

protected:
    virtual void doDraw(QPainter &painter) override;

private:
    QRect r;
};

#endif // ELLIPSE_H
