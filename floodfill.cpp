#include "floodfill.h"

#include <vector>

struct fillpixelinfo
{
   int y, xl, xr, dy;
};

#define PUSH(py, pxl, pxr, pdy) \
{ \
    struct fillpixelinfo p;\
    if (((py) + (pdy) >= 0) && ((py) + (pdy) < image.height()))\
    {\
        p.y = (py);\
        p.xl = (pxl);\
        p.xr = (pxr);\
        p.dy = (pdy);\
        stack.push_back(p); \
    }\
}

#define POP(py, pxl, pxr, pdy) \
{\
    struct fillpixelinfo p = stack.back();\
    stack.pop_back();\
    (py) = p.y + p.dy;\
    (pxl) = p.xl;\
    (pxr) = p.xr;\
    (pdy) = p.dy;\
}

std::vector<QPoint>
floodFill(QImage *img, const QPoint &pos, const QRgb &newColor)
{
   QImage image = img->copy();
   std::vector<QPoint> modified;

   int x = pos.x(), y = pos.y();
   const QRgb oldColor = image.pixel(x, y);

   std::vector<fillpixelinfo> stack;

   int l, x1, x2, dy;

   if ((x >= 0) && (x < image.width()) && (y >= 0) && (y < image.height()))
   {
       if (oldColor == newColor)
       {
           return modified;
       }
       PUSH(y, x, x, 1);
       PUSH(y + 1, x, x, -1);
       while (!stack.empty())
       {
           POP(y, x1, x2, dy);
           for (x = x1; (x >= 0) && image.pixel(x, y) == oldColor; x--)
           {
               image.setPixel(x, y, newColor);
               modified.emplace_back(x, y);
           }
           if (x >= x1)
           {
               goto skip;
           }
           l = x + 1;
           if (l < x1)
           {
               PUSH(y, l, x1 - 1, -dy);
           }
           x = x1 + 1;
           do
           {
               for (; (x < image.width()) && image.pixel(x, y) == oldColor; x++)
               {
                   image.setPixel(x, y, newColor);
                   modified.emplace_back(x, y);
               }
               PUSH(y, l, x - 1, dy);
               if (x > x2 + 1)
               {
                   PUSH(y, x2 + 1, x - 1, -dy);
               }
skip:
               for (x++; x <= x2 && image.pixel(x, y) != oldColor; x++)
               {
                   /* empty */ ;
               }
               l = x;
           } while (x <= x2);
       }
   }

   return modified;
}
