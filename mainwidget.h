#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qslider.h>
#include "imagewidget.h"
#include "brush.h"

class MainWidget : public QWidget {
	Q_OBJECT;

public:
	MainWidget(QWidget* parent = nullptr);
	~MainWidget();

private slots:
	void onBtnLoadClicked();
	void onBtnZoomInClicked();
	void onBtnZoomOutClicked();
	void onBtnSaveClicked();
	void onBtnColorSelectClicked();
	void onSliderValueChanged(int value);

private:
	void setup();
	QPushButton* m_btnLoad;
	QPushButton* m_btnSave;
	QPushButton* m_btnZoomIn;
	QPushButton* m_btnZoomOut;
	QPushButton* m_btnColorSelect;
	ImageWidget* w_image;
	QLabel* m_lb_state;
	QLabel* m_lb_blocksize;
	QSlider* m_sld_blocksize;
	QString filepath;
};
