#include "command.h"

#include "document.h"

Command::Command(Document *d, std::unique_ptr<Shape> &&s) :
    doc(d), shape(std::move(s))
{
}

void Command::undo()
{
    doc->popShape();
}

void Command::redo()
{
    doc->pushShape(shape.get());
}
