#include "scribble.h"

Scribble::Scribble(const QPoint &topLeft)
{
    update(topLeft);
}

void Scribble::draw(QPainter &painter)
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
