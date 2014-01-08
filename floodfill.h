#ifndef FLOODFILL_H
#define FLOODFILL_H

#include <QImage>

#include <vector>

std::vector<QPoint>
floodFill(QImage *image, const QPoint &pos, const QRgb &newColor);

#endif // FLOODFILL_H
