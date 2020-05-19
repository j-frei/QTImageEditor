#include "brush.h"

Brush::Brush(QColor col=Qt::GlobalColor::black) {
    color=col;
    blocksize=QSize(1,1);
}


Brush::~Brush() {

}

QColor Brush::getCurrentColor() {
    return color;
}

void Brush::setCurrentColor(QColor col) {
    color=col;
}

QSize Brush::getBlockSize() {
    return blocksize;
}

void Brush::setSize(QSize size) {
    blocksize=size;
}
