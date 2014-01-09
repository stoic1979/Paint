/* Paint
 * Copyright (C) 2014 Krzysztof Konopko <krzysztof.konopko@konagma.pl>
 */

#ifndef FLOODFILL_H
#define FLOODFILL_H

#include <QImage>

#include <vector>

namespace Paint {

std::vector<QPoint>
floodFill(QImage *image, const QPoint &pos, const QRgb &newColor);

} // namespace Paint

#endif // FLOODFILL_H
