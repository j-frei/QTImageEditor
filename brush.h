#ifndef QTAS6_BRUSH_H
#define QTAS6_BRUSH_H

#include <QtGui/qcolor.h>
#include <QtGui/qimage.h>

class Brush {

public:
    Brush(QColor col);
    ~Brush();
    QColor getCurrentColor();
    void setCurrentColor(QColor col);
    QSize getBlockSize();
    void setSize(QSize);

private:
    QColor color;
    QSize blocksize;
};


#endif //QTAS6_BRUSH_H
