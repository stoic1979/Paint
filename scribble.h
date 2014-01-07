#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "shape.h"

#include <QPolygon>

class Scribble : public Shape
{
public:
    explicit Scribble(const QPoint &topLeft);

    virtual void draw(QPainter &painter) override;

    virtual QRect rect() const override;

    virtual void update(const QPoint &lastPoint) override;

private:
    QPolygon poly;
};

#endif // SCRIBBLE_H
