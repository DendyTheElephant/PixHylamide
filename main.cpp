#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	MainWindow mainWindow;

	QFile File("ressources/GUI/QTDark.stylesheet");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());

	mainWindow.setStyleSheet(StyleSheet);

	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	int x = (screenGeometry.width()/2 - mainWindow.width());
	int y = (screenGeometry.height()/2 - mainWindow.height());
	mainWindow.move(x, y);
	mainWindow.show();

	return app.exec();
}
