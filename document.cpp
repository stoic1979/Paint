#include "document.h"

#include <qevent.h>
#include <QPainter>

#include <algorithm>

Document::Document(QWidget *parent) :
    QWidget(parent),
    drawShape(&Document::drawEllipse)
{
}

void Document::drawEllipse(QPainter &p, const QRect& r)
{
    p.drawEllipse(r);
}

void Document::drawRect(QPainter &p, const QRect& r)
{
    p.drawRect(r);
}

void Document::mousePressEvent(QMouseEvent *event)
{
    event->accept();

    rect.setTopLeft(event->pos());
}

void Document::mouseReleaseEvent(QMouseEvent *event)
{
    using namespace std::placeholders;

    event->accept();

    shapes.push_back(std::bind(drawShape, _1, rect));
    rect = QRect();

    drawShape = shapes.size() % 2 ?
                    &Document::drawRect :
                    &Document::drawEllipse;
}

void Document::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    rect.setBottomRight(event->pos());
    update();
}

void Document::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    for (auto& f : shapes) {
        f(painter);
    }

    if (!rect.isNull()) {
        drawShape(painter, rect.normalized());
    }
}
