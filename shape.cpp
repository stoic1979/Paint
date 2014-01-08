#include "shape.h"

Shape::Shape(int penWidth, const QColor& penColor) :
    penWidth(penWidth), penColor(penColor)
{
}

Shape::~Shape()
{
}

void Shape::draw(QPainter &painter)
{
    const QPen prevPen = painter.pen();

    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));
    doDraw(painter);
    painter.setPen(prevPen);
}

QRect Shape::rect() const
{
    const int rad = penWidth / 2 + 2;
    return doRect().adjusted(-rad, -rad, +rad, +rad);
}

void Shape::update(const QPoint &toPoint)
{
    doUpdate(toPoint);
}
