#pragma once

#include <QtWidgets>

class StatusBar : public QStatusBar {
	Q_OBJECT

private:
	QLabel* m_label;
	QProgressBar* m_progress;
	QSizeGrip* m_grip;

public:
	StatusBar(QWidget* parent = 0);
	void displayMessage(QString msg);
};
