#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qslider.h>
#include "brush.h"


class ImageWidget : public QWidget {
public:
    ImageWidget(QWidget* parent = nullptr);
    ~ImageWidget();

    int heightForWidth (int width) const override;
    QSize sizeHint() const override;
    void setImage(QImage& img);
    void zoomIn();
    void zoomOut();
    bool isLoaded();
    Brush* getBrush();
    QImage* getImage();

//public slots:


//signals:

protected:
    void paintEvent(QPaintEvent* pe) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QImage getZoomedImage();
    void drawAt(QPoint pos);

    QImage* m_image;
    QPoint zoomPoint;
    float  zoomSize;
    QPoint mouseMovePoint;
    Qt::MouseButton buttonUsed;
    bool image_loaded;
    Brush brush;

};
