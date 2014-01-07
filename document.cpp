#include "document.h"

#include "ellipse.h"
#include "rectangle.h"
#include "scribble.h"

#include <qevent.h>
#include <QPainter>

Document::Document(QWidget *parent) :
    QWidget(parent),
    modified(false),
    penWidth(1),
    penColor(Qt::blue)
{
}

bool Document::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    //resizeImage(&loadedImage, newSize);
    modified = false;
    update();
    return true;
}

bool Document::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage image(size(), QImage::Format_RGB32);

    render(&image);
    if (image.save(fileName, fileFormat)) {
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

void Document::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        switch (shapes.size() % 3) {
        case 0:
            currentShape.reset(new Ellipse(event->pos(), penWidth, penColor));
            break;

        case 1:
            currentShape.reset(new Scribble(event->pos(), penWidth, penColor));
            break;

        default:
            currentShape.reset(new Rectangle(event->pos(), penWidth, penColor));
            break;
        }
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
        shapes.emplace_back(std::move(currentShape));

        modified = true;
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
