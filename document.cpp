#include "document.h"

#include "ellipse.h"
#include "rectangle.h"
#include "scribble.h"

#include <qevent.h>
#include <QPainter>

Document::Document(QWidget *parent) :
    QWidget(parent)
{
}

void Document::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        switch (shapes.size() % 3) {
        case 0:
            currentShape.reset(new Ellipse(event->pos()));
            break;

        case 1:
            currentShape.reset(new Scribble(event->pos()));
            break;

        default:
            currentShape.reset(new Rectangle(event->pos()));
            break;
        }
    }
}

void Document::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && currentShape) {

        const QRect prevRect = currentShape->rect();
        currentShape->update(event->pos());

        update(currentShape->rect().united(prevRect).adjusted(-2, -2, +2, +2));
    }
}

void Document::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && currentShape) {
        shapes.emplace_back(std::move(currentShape));


    }
}

void Document::paintEvent(QPaintEvent *event)
{
    const QRegion paintRegion = event->region();

    QPainter painter(this);

    for (auto& s : shapes) {
        if (paintRegion.intersects(s->rect())) {
            s->draw(painter);
        }
    }

    if (currentShape) {
        currentShape->draw(painter);
    }
}
