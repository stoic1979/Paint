/* Paint
 * Copyright (C) 2014 Krzysztof Konopko <krzysztof.konopko@konagma.pl>
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "shape.h"

#include <QImage>
#include <QWidget>
#include <QUndoCommand>

#include <memory>
#include <vector>

namespace Paint {

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

class FlipCommand : public QUndoCommand
{
public:
    explicit FlipCommand(QWidget *doc, QImage *image,
                         bool horizontal, bool vertical);

    virtual void undo() override;
    virtual void redo() override;

private:
    QWidget *doc;
    QImage *image;

    bool horizontal, vertical;
};

class ResizeCommand : public QUndoCommand
{
public:
    explicit ResizeCommand(QWidget *doc, QImage *image, const QSize &size);

    virtual int id() const override;
    virtual bool mergeWith(const QUndoCommand *command) override;

    virtual void undo() override;
    virtual void redo() override;

private:
    QWidget *doc;
    QImage *image;

    QSize oldSize, newSize;
};

class RotateCommand : public QUndoCommand
{
public:
    explicit RotateCommand(QWidget *doc, QImage *image, qreal deg);

    virtual void undo() override;
    virtual void redo() override;

private:
    void rotate(qreal deg);

    QWidget *doc;
    QImage *image;

    qreal deg;
};

} // namespace Paint

#endif // COMMAND_H
