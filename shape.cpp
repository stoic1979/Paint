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
    return doRect();
}

void Shape::update(const QPoint &toPoint)
{
    doUpdate(toPoint);
}
