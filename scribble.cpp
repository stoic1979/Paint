#include "scribble.h"

Scribble::Scribble(const QPoint &topLeft, int penWidth, const QColor &penColor) :
    Shape(penWidth, penColor)
{
    update(topLeft);
}

void Scribble::doDraw(QPainter &painter)
{
    painter.drawPolyline(poly);
}

QRect Scribble::rect() const
{
    return poly.boundingRect();
}

void Scribble::update(const QPoint &lastPoint)
{
    poly << lastPoint;
}
