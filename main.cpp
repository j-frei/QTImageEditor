#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>

#include "mainwidget.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	QMainWindow qmw;

	MainWidget* mainWindow = new MainWidget();
	qmw.setCentralWidget(mainWindow);
	qmw.show();
	
	return a.exec();
}
