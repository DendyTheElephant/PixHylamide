#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	MainWindow mainWindow;

	QFile File("ressources/GUI/QTDark.stylesheet");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());

	mainWindow.setStyleSheet(StyleSheet);

	mainWindow.showMaximized();
	return app.exec();
}
