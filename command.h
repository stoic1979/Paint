#ifndef COMMAND_H
#define COMMAND_H

#include "shape.h"

#include <QUndoCommand>

#include <memory>

class Document;

class Command : public QUndoCommand
{
public:
    explicit Command(Document *d, std::unique_ptr<Shape> &&s);

    virtual void undo() override;
    virtual void redo() override;

private:
    Document *doc;
    std::unique_ptr<Shape> shape;
};

#endif // COMMAND_H
