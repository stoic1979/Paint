#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QRect>
#include <QWidget>

#include <functional>
#include <list>

class Document : public QWidget
{
    Q_OBJECT
public:
    explicit Document(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    static
    void drawEllipse(QPainter &p, const QRect& r);

    static
    void drawRect(QPainter &p, const QRect& r);

    QRect rect;
    std::function<void(QPainter&, const QRect&)> drawShape;

    std::list<std::function<void(QPainter&)>> shapes;
};

#endif // DOCUMENT_H
