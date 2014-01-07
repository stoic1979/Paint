#include "document.h"

#include <qevent.h>
#include <QPainter>

Document::Document(QWidget *parent) :
    QWidget(parent),
    modified(false),
    penWidth(1),
    penColor(Qt::blue)
{
}

void Document::flip(bool horiz, bool vert)
{
    image = image.mirrored(horiz, vert);
    modified = true;

    update();
}

bool Document::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName)) {
        return false;
    }

    QSize newSize = loadedImage.size().expandedTo(size());

    resizeImage(&loadedImage, newSize);
    modified = false;

    update();

    return true;
}

bool Document::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
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

        const int rad = (penWidth / 2) + 2;
        update(currentShape->rect()
               .united(prevRect)
               .adjusted(-rad, -rad, +rad, +rad));

        modified = true;
    }
}

void Document::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && currentShape) {
        QPainter painter(&image);
        currentShape->draw(painter);

        shapes.emplace_back(std::move(currentShape));

        modified = true;
    }
}

void Document::paintEvent(QPaintEvent *event)
{
    const QRect paintRect = event->rect();

    QPainter painter(this);

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

        resizeImage(&image, QSize(newWidth, newHeight));

        update();
    }

    QWidget::resizeEvent(event);
}

void Document::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize) {
        return;
    }

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
