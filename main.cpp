#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	QFrame* frame = new QFrame();
	MainWindow* mainWindow = new MainWindow();

	QFile File("ressources/GUI/QTDark.stylesheet");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());

	mainWindow->setStyleSheet(StyleSheet);
	mainWindow->setWindowIcon(QIcon("ressources/GUI/profil.png"));

	frame->setGeometry(
		QStyle::alignedRect(
		Qt::LeftToRight,
		Qt::AlignCenter,
		mainWindow->size(),
		qApp->desktop()->availableGeometry()));

	frame->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	frame->setStyleSheet(".QFrame{background-color: #262626; border: 1px solid #565656; border-radius: 1px;}");
	frame->setLayout(new QHBoxLayout());
	frame->layout()->addWidget(mainWindow);
	frame->show();	

	return app.exec();
}
