#include "document.h"

#include "ellipse.h"
#include "rectangle.h"
#include "scribble.h"

#include <qevent.h>
#include <QPainter>

#include <algorithm>

Document::Document(QWidget *parent) :
    QWidget(parent)
{
}

void Document::mousePressEvent(QMouseEvent *event)
{
    event->accept();

    current.reset(new Scribble(event->pos()));
}

void Document::mouseReleaseEvent(QMouseEvent *event)
{
    using namespace std::placeholders;

    event->accept();

    shapes.emplace_back(std::move(current));
}

void Document::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    const QRect prevRect = current->rect();
    current->update(event->pos());

    update(current->rect().united(prevRect).adjusted(-2, -2, +2, +2));
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

    if (current) {
        current->draw(painter);
    }
}
