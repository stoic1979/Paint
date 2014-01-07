#include "rectangle.h"

Rectangle::Rectangle(const QPoint &topLeft)
{
    r.setTopLeft(topLeft);
    r.setBottomRight(topLeft);
}

void Rectangle::draw(QPainter &painter)
{
    if (!r.isNull()) {
        painter.drawRect(r.normalized());
    }
}

QRect Rectangle::rect() const
{
    return r;
}

void Rectangle::update(const QPoint &lastPoint)
{
    r.setBottomRight(lastPoint);
}
