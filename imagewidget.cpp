#include <QtWidgets/qwidget.h>
#include <QtGui/qpainter.h>
#include <QtGui/qevent.h>
#include <iostream>
#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent  /* = nullptr*/)
        : QWidget(parent), m_image(nullptr), brush{Brush(nullptr)} {
    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);
    zoomPoint=QPoint(200,0);
    zoomSize=1;
    mouseMovePoint=QPoint(0,0);
    buttonUsed=Qt::MouseButton::LeftButton;
    image_loaded=false;

}

ImageWidget::~ImageWidget() {
    delete m_image;
}

int ImageWidget::heightForWidth(int width) const { return width; }

QSize ImageWidget::sizeHint() const { return QSize(500, 500); }

void ImageWidget::paintEvent(QPaintEvent *pe) {
    QPainter p(this);
    if(image_loaded)
        p.drawImage(QPoint(0,0),getZoomedImage());
}

void ImageWidget::setImage(QImage& img) {
    QImage t_image = QImage(img);
    m_image = new QImage(t_image.convertToFormat(QImage::Format_RGB32 ));
    image_loaded=true;
    update();
}

void ImageWidget::mousePressEvent(QMouseEvent *event) {
    event->accept();
    if (image_loaded) {
        mouseMovePoint = event->pos();
        buttonUsed = event->button();
    }
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event) {
    event->accept();
    if(image_loaded) {

        const QPoint tmp_Point = mouseMovePoint - event->pos();
        mouseMovePoint = event->pos();

        switch (buttonUsed) {
            case Qt::MouseButton::LeftButton:
                drawAt(mouseMovePoint);
                update();
                break;

            case Qt::MouseButton::RightButton:
                zoomPoint += tmp_Point;
                update();
                break;
        }
    }
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event) {
    event->accept();
    if (image_loaded) {
        if (buttonUsed == event->button()) {
            const QPoint tmp_Point = mouseMovePoint - event->pos();
            mouseMovePoint = event->pos();

            switch (buttonUsed) {
                case Qt::MouseButton::LeftButton:
                    drawAt(mouseMovePoint);
                    update();
                    break;

                case Qt::MouseButton::RightButton:
                    zoomPoint += tmp_Point;
                    update();
                    break;
            }
            mouseMovePoint = QPoint(0, 0);
        }
    }
}

QImage ImageWidget::getZoomedImage() {
    QImage p = m_image->scaled(m_image->size()*zoomSize);
    QPoint zoomedPoint = zoomPoint*zoomSize;
    return p.copy(QRect(zoomedPoint,sizeHint()));
}

void ImageWidget::zoomIn() {
    zoomSize*=1.25;
    update();
}


void ImageWidget::zoomOut() {
    zoomSize/=1.25;
    update();
}


bool ImageWidget::isLoaded() {
    return image_loaded;
}

void ImageWidget::drawAt(QPoint posZoomed){
    QPoint truePoint = zoomPoint+(posZoomed / zoomSize);

    for(int col=truePoint.x();col<truePoint.x()+brush.getBlockSize().height();col++){
        for(int row=truePoint.y();row<truePoint.y()+brush.getBlockSize().width();row++) {
            if (row >= 0 && col >= 0 && row < m_image->height() && col < m_image->width()) {
                m_image->setPixel(col, row, brush.getCurrentColor().rgb());
            }
        }
    }
}

Brush*  ImageWidget::getBrush() {
    return &brush;
}

QImage *ImageWidget::getImage() {
    return m_image;
}
