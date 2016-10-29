#include "StatusBar.h"

StatusBar::StatusBar(QWidget* parent) {

	//setMinimumHeight(21);
	setStyleSheet("background-color: #262626;");

	m_label = new QLabel();
	//m_label->setMinimumWidth(600);

	m_progress = new QProgressBar();
	m_progress->setMaximumWidth(100);
	m_progress->setMinimumWidth(100);

	m_grip = new QSizeGrip(this);

	addWidget(m_label);
	addWidget(m_progress);
}

void StatusBar::displayMessage(QString msg) {
	m_label->setText(msg);
}
