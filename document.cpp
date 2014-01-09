/* Paint
 * Copyright (C) 2014 Krzysztof Konopko <krzysztof.konopko@konagma.pl>
 */

#include "document.h"

#include "command.h"
#include "floodfill.h"

#include <qevent.h>
#include <QPainter>

#include <algorithm>

namespace Paint {

Document::Document(QUndoStack *undoStack, QWidget *parent) :
    QWidget(parent),
    undoStack(undoStack),
    penWidth(1),
    penColor(Qt::blue)
{
}

bool Document::isModified() const
{
    return !undoStack->isClean();
}

void Document::flip(bool horiz, bool vert)
{
    undoStack->push(new FlipCommand(this, &image, horiz, vert));
}

std::vector<QPoint> Document::floodFill(const QPoint &pos, const QRgb &color)
{
    return Paint::floodFill(&image, pos, color);
}

void Document::rotate(qreal deg)
{
    undoStack->push(new RotateCommand(this, &image, deg));
}

bool Document::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName)) {
        return false;
    }

    const QSize newSize = loadedImage.size().expandedTo(size());

    image = loadedImage;
    ResizeCommand(this, &image, newSize).redo();
    undoStack->clear();

    return true;
}

bool Document::saveImage(const QString &fileName, const char *fileFormat)
{
    if (image.save(fileName, fileFormat)) {
        undoStack->clear();
        return true;
    } else {
        return false;
    }
}

void Document::setPenColor(const QColor &newColor)
{
    penColor = newColor;
}

void Document::setPenWidth(int newWidth)
{
    penWidth = newWidth;
}

void Document::setShapeFactory(shape_factory_t f)
{
    factory = f;
}

void Document::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && factory) {
        currentShape = factory(event->pos(), penWidth, penColor);
    }
}

void Document::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && currentShape) {

        const QRect prevRect = currentShape->rect();
        currentShape->update(event->pos());

        update(currentShape->rect().united(prevRect));
    }
}

void Document::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && currentShape) {
        undoStack->push(new ShapeCommand(this, &image,
                                         std::move(currentShape)));
    }
}

void Document::paintEvent(QPaintEvent *event)
{
    const QRect paintRect = event->rect();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawImage(paintRect, image, paintRect);

    if (currentShape) {
        currentShape->draw(painter);
    }
}

void Document::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        const int newWidth = qMax(width() + 128, image.width());
        const int newHeight = qMax(height() + 128, image.height());

        const QSize newSize(newWidth, newHeight);

        if (isModified()) {
            undoStack->push(new ResizeCommand(this, &image, newSize));
        } else {
            ResizeCommand(this, &image, newSize).redo();
        }
    }

    QWidget::resizeEvent(event);
}

} // Paint
