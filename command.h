#ifndef COMMAND_H
#define COMMAND_H

#include "shape.h"

#include <QImage>
#include <QWidget>
#include <QUndoCommand>

#include <memory>
#include <vector>

class ShapeCommand : public QUndoCommand
{
public:
    explicit ShapeCommand(QWidget *doc, QImage *image,
                          std::unique_ptr<Shape> &&s);

    virtual void undo() override;
    virtual void redo() override;

private:
    QWidget *doc;
    QImage *image;

    QImage undoImage;
    std::unique_ptr<Shape> shape;
};

#endif // COMMAND_H
