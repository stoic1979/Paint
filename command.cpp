#include "command.h"

#include "document.h"

ShapeCommand::ShapeCommand(QWidget *doc, QImage *image,
                           std::unique_ptr<Shape> &&s) :
    doc(doc), image(image),
    undoImage(image->copy(s->rect())), shape(std::move(s))
{
}

void ShapeCommand::undo()
{
    const QRect rect = shape->rect();

    QPainter painter(image);
    painter.drawImage(rect, undoImage);

    doc->update(rect);
}

void ShapeCommand::redo()
{
    QPainter painter(image);
    shape->draw(painter);

    doc->update(shape->rect());
}
