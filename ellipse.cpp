#include "ellipse.h"

Ellipse::Ellipse(const QPoint &topLeft, int penWidth, const QColor &penColor) :
    Shape(penWidth, penColor)
{
    r.setTopLeft(topLeft);
    r.setBottomRight(topLeft);
}

void Ellipse::doDraw(QPainter &painter)
{
    if (!r.isNull()) {
        painter.drawEllipse(r.normalized());
    }
}

QRect Ellipse::rect() const
{
    return r;
}

void Ellipse::update(const QPoint &lastPoint)
{
    r.setBottomRight(lastPoint);
}
