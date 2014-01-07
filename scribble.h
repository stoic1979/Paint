#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "shape.h"

#include <QPolygon>

class Scribble : public Shape
{
public:
    explicit Scribble(const QPoint &topLeft, int penWidth, const QColor& penColor);

    virtual QRect rect() const override;

    virtual void update(const QPoint &lastPoint) override;

protected:
    virtual void doDraw(QPainter &painter) override;

private:
    QPolygon poly;
};

#endif // SCRIBBLE_H
