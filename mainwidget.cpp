#include <iostream>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qcolordialog.h>
#include "mainwidget.h"

MainWidget::MainWidget(QWidget* parent  /* = nullptr*/)
: QWidget(parent), m_btnLoad(nullptr), m_btnSave(nullptr), m_btnZoomIn(nullptr), m_btnZoomOut{nullptr},m_lb_state{nullptr},filepath{""},m_sld_blocksize{nullptr}
{
	setup();
}

void MainWidget::setup() {
	QGridLayout* gridLayout = new QGridLayout();
	QVBoxLayout* toolLayout = new QVBoxLayout();
	gridLayout->addLayout(toolLayout,0,0);

	m_btnLoad = new QPushButton("load image");
	toolLayout->addWidget(m_btnLoad);
	m_btnSave = new QPushButton("save image/override");
	toolLayout->addWidget(m_btnSave);
	m_btnZoomIn = new QPushButton("zoom in");
	toolLayout->addWidget(m_btnZoomIn);
	m_btnZoomOut = new QPushButton("zoom out");
	toolLayout->addWidget(m_btnZoomOut);
	m_btnColorSelect = new QPushButton("change color");
	toolLayout->addWidget(m_btnColorSelect);

	w_image = new ImageWidget();
	gridLayout->addWidget(w_image,0,1);

	m_lb_blocksize = new QLabel("Brushsize:");
	toolLayout->addWidget(m_lb_blocksize);
	m_sld_blocksize = new QSlider(Qt::Horizontal);
	toolLayout->addWidget(m_sld_blocksize);
	m_sld_blocksize->setMaximum(50);
	m_sld_blocksize->setMinimum(1);

	m_lb_state = new QLabel("No image loaded.");
	gridLayout->addWidget(m_lb_state,1,0,1,2);

	setLayout(gridLayout);

	connect(
			m_btnLoad, SIGNAL(clicked()),this,SLOT(onBtnLoadClicked())
	);
	connect(
			m_btnZoomIn, SIGNAL(clicked()),this,SLOT(onBtnZoomInClicked())
	);
	connect(
			m_btnZoomOut, SIGNAL(clicked()),this,SLOT(onBtnZoomOutClicked())
	);
	connect(
			m_btnSave, SIGNAL(clicked()),this,SLOT(onBtnSaveClicked())
	);
	connect(
			m_btnColorSelect, SIGNAL(clicked()),this,SLOT(onBtnColorSelectClicked())
	);
	connect(
			m_sld_blocksize, SIGNAL(valueChanged(int)),this,SLOT(onSliderValueChanged(int))
	);
}


void MainWidget::onBtnLoadClicked() {
	QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "*.*", tr("Files (*.*)"));
	if (file != "") {
		QImage image = QImage(file);
		w_image->setImage(image);
		m_lb_state->setText(QString("Image loaded from: ").append(file));
		filepath=file;
	}
}

void MainWidget::onBtnZoomInClicked() {
	w_image->zoomIn();
}

void MainWidget::onBtnZoomOutClicked() {
	w_image->zoomOut();
}

void MainWidget::onBtnSaveClicked(){
	if(w_image->isLoaded() && filepath!=""){
		w_image->getImage()->save(filepath);
	}
}

void MainWidget::onBtnColorSelectClicked() {
	QColor color = QColorDialog::getColor(w_image->getBrush()->getCurrentColor());
	w_image->getBrush()->setCurrentColor(color);
}

MainWidget::~MainWidget() {
}


void MainWidget::onSliderValueChanged(int value) {
	w_image->getBrush()->setSize(QSize(value,value));
}
