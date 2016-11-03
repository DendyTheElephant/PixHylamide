#include "MainWindowMenu.h"



MainWindowMenu::MainWindowMenu(QWidget* parent) {

	m_widthBeforeMaximization = window()->width();
	m_heightBeforeMaximization = window()->height();

	setParent(parent);

	m_fileMenu = addMenu("&Fichier");

	action_Open = m_fileMenu->addAction("&Ouvrir");
	action_Open->setShortcut(QKeySequence("Ctrl+O"));
	action_Open->setIcon(QIcon("ressources/GUI/icons/15_Photo.ico"));

	action_Save = m_fileMenu->addAction("&Enregistrer");
	action_Save->setShortcut(QKeySequence("Ctrl+S"));
	action_Save->setIcon(QIcon("ressources/GUI/icons/04_Save.ico"));
	action_Save->setEnabled(false);

	action_SaveAs = m_fileMenu->addAction("&Enregistrer sous ...");
	action_SaveAs->setEnabled(false);

	m_fileMenu->addSeparator();

	action_Quit = m_fileMenu->addAction("&Quitter");
	action_Quit->setIcon(QIcon("ressources/GUI/quit.png"));
	action_Quit->setShortcut(QKeySequence("Ctrl+Q"));


	m_editionMenu = addMenu("&Edition");

	action_SelectAll = m_editionMenu->addAction("&Tout selectionner");
	action_SelectAll->setShortcut(QKeySequence("Ctrl+A"));

	m_editionMenu->addSeparator();

	action_Previous = m_editionMenu->addAction("&Precedent");
	action_Previous->setShortcut(QKeySequence("Ctrl+Z"));
	action_Previous->setIcon(QIcon("ressources/GUI/icons/19_Left_Arrow.ico"));

	action_Next = m_editionMenu->addAction("&Suivant");
	action_Next->setShortcut(QKeySequence("Alt+Z"));
	action_Next->setIcon(QIcon("ressources/GUI/icons/20_Right_Arrow.ico"));

	m_displayMenu = addMenu("&Affichage");

	QWidget* windowButtons = new QWidget();
	windowButtons->setStyleSheet("padding: 0px -2px 0px -2px;");
	QHBoxLayout* windowButtonsLayout = new QHBoxLayout();
	QPushButton* quitButton = new QPushButton();
	quitButton->setIcon(QIcon("ressources/GUI/close.png"));
	quitButton->setStyleSheet("border: none; background: transparent; icon-size: 18px;");
	QPushButton* reduceButton = new QPushButton();
	reduceButton->setIcon(QIcon("ressources/GUI/green.png"));
	reduceButton->setStyleSheet("border: none; background: transparent; icon-size: 18px;");
	QPushButton* maximizeButton = new QPushButton();
	maximizeButton->setIcon(QIcon("ressources/GUI/yellow.png"));
	maximizeButton->setStyleSheet("border: none; background: transparent; icon-size: 18px;");

	windowButtonsLayout->addWidget(reduceButton);
	windowButtonsLayout->addWidget(maximizeButton);
	windowButtonsLayout->addWidget(quitButton);
	windowButtonsLayout->setContentsMargins(0, 0, 0, 0);

	windowButtons->setLayout(windowButtonsLayout);

	setCornerWidget(windowButtons, Qt::TopRightCorner);
	setStyleSheet("background-color: #262626;");
	//setMaximumHeight(24);

	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(reduceButton, SIGNAL(clicked()), this, SLOT(slot_reduce()));
	connect(maximizeButton, SIGNAL(clicked()), this, SLOT(slot_maximize()));
}

bool MainWindowMenu::isOnGrabZone(QMouseEvent *event) {
	return ((event->windowPos()).x() > MENU_SIZE);
}

void MainWindowMenu::maximize() {
	if (m_isMaximized) {
		QRect screenGeometry = QApplication::desktop()->screenGeometry();
		window()->resize(m_widthBeforeMaximization, m_heightBeforeMaximization);
		//window()->move(screenGeometry.center());
		window()->setGeometry(
			QStyle::alignedRect(
			Qt::LeftToRight,
			Qt::AlignCenter,
			window()->size(),
			qApp->desktop()->availableGeometry()));
		m_isMaximized = false;
	}
	else {
		QRect screenGeometry = QApplication::desktop()->availableGeometry();
		m_widthBeforeMaximization = window()->width();
		m_heightBeforeMaximization = window()->height();
		window()->resize(screenGeometry.width(), screenGeometry.height());
		window()->move(0, 0);
		m_isMaximized = true;
	}
}

void MainWindowMenu::mouseDoubleClickEvent(QMouseEvent *event) {
	if (isOnGrabZone(event)) {
		maximize();
	}
	else {
		// Propoagation of the events to the base class!
		QMenuBar::mouseDoubleClickEvent(event);
	}
}

void MainWindowMenu::mousePressEvent(QMouseEvent *event) {
	if (isOnGrabZone(event) && event->button() == Qt::LeftButton) {
		m_diff = event->pos();
		setCursor(QCursor(Qt::SizeAllCursor));
		if (!m_isMaximized)  {
			m_widthBeforeMaximization = window()->width();
			m_heightBeforeMaximization = window()->height();
		}
		m_isGrabbed = true;
	}
	else {
		// Propoagation of the events to the base class!
		QMenuBar::mousePressEvent(event);
	}
}

void MainWindowMenu::mouseReleaseEvent(QMouseEvent *event) {
	if (m_isGrabbed) {
		Q_UNUSED(event);
		setCursor(QCursor(Qt::ArrowCursor));
		m_isGrabbed = false;
	}
	else {
		// Propoagation of the events to the base class!
		QMenuBar::mouseReleaseEvent(event);
	}
}

void MainWindowMenu::mouseMoveEvent(QMouseEvent *event) {
	if (m_isGrabbed) {
		QPoint p = event->globalPos();
		QRect screenGeometry = QApplication::desktop()->availableGeometry();
		if (p.x() == 0) {
			window()->resize(screenGeometry.width()/2, screenGeometry.height());
			window()->move(0, 0);
			m_isMaximized = true;
		}
		else if (p.x() == screenGeometry.width()-1) {
			window()->resize(screenGeometry.width() / 2, screenGeometry.height());
			window()->move(screenGeometry.width() / 2, 0);
			m_isMaximized = true;
		}
		else if (p.y() == 0) {
			window()->resize(screenGeometry.width(), screenGeometry.height());
			window()->move(0, 0);
			m_isMaximized = true;
		}
		else {
			window()->move(p - m_diff);
			if (m_isMaximized) {
				window()->resize(m_widthBeforeMaximization, m_heightBeforeMaximization);
				m_isMaximized = false;
			}
		}		
	}
	else if (isOnGrabZone(event)) {
		// If menu focus lost, close the menus:
		m_fileMenu->close();
		m_editionMenu->close();
		m_displayMenu->close();
	} 
	else {
		// Propoagation of the events to the base class!
		QMenuBar::mouseMoveEvent(event);
	}
}