#include "code/hdr/MainWindow.h"

MainWindow::MainWindow() {

	m_menuBar = new MainWindowMenu(this);
	setMenuBar(m_menuBar);

	m_statusBar = new StatusBar(this);
	setStatusBar(m_statusBar);
	m_statusBar->displayMessage("Bienvenue dans Dendy Draw by Dendy Softainement (Daniel Huc)");

	// Création de la barre d'outils
	QToolBar *toolBar = addToolBar("Outils");
	toolBar->setMovable(false);
	toolBar->setIconSize(QSize(24, 24));

	toolBar->addAction(m_menuBar->action_New);
	toolBar->addAction(m_menuBar->action_Open);
	toolBar->addSeparator();
	toolBar->addAction(m_menuBar->action_Save);
	toolBar->addSeparator();
	toolBar->addAction(m_menuBar->action_Previous);
	toolBar->addAction(m_menuBar->action_Next);
	toolBar->addSeparator();

	// Création des docks
	QDockWidget *dock = new QDockWidget("Palette", this);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	QDockWidget *dock2 = new QDockWidget("GameObjects", this);
	addDockWidget(Qt::RightDockWidgetArea, dock2);

	QWidget *contenuDock = new QWidget;
	dock->setWidget(contenuDock);

	QPushButton *crayon = new QPushButton("Crayon");
	QPushButton *pinceau = new QPushButton("Pinceau");
	QPushButton *feutre = new QPushButton("Feutre");
	QLabel *labelEpaisseur = new QLabel("Epaisseur :");
	QSpinBox *epaisseur = new QSpinBox;

	QVBoxLayout *dockLayout = new QVBoxLayout;
	dockLayout->addWidget(crayon);
	dockLayout->addWidget(pinceau);
	dockLayout->addWidget(feutre);
	dockLayout->addWidget(labelEpaisseur);
	dockLayout->addWidget(epaisseur);

	contenuDock->setLayout(dockLayout);

	// Création de la zone centrale
	m_multipleDocumentInterface = new QMdiArea();
	m_multipleDocumentInterface->setViewMode(QMdiArea::TabbedView);
	m_multipleDocumentInterface->setTabsClosable(true);
	m_multipleDocumentInterface->setTabsMovable(true);
	
	setCentralWidget(m_multipleDocumentInterface);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	// Connexion des signaux
	connect(m_menuBar->action_Quit, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect(m_menuBar->action_New, SIGNAL(triggered()), this, SLOT(slot_new(void)));
	connect(m_menuBar->action_Open, SIGNAL(triggered()), this, SLOT(slot_open(void)));
	connect(m_menuBar->action_Save, SIGNAL(triggered()), this, SLOT(slot_save(void)));
	connect(m_menuBar->action_SaveAs, SIGNAL(triggered()), this, SLOT(slot_save(void)));
}

void MainWindow::slot_new() {
	
	m_newFiles_counter++;

	EditorView* editorView = new EditorView(m_multipleDocumentInterface);
	editorView->setName("NewFile" + QString::number(m_newFiles_counter));

	QMdiSubWindow* subWindowToAdd = m_multipleDocumentInterface->addSubWindow(editorView, Qt::SubWindow);
	subWindowToAdd->setWindowTitle(editorView->getName());
	subWindowToAdd->setOption(QMdiSubWindow::RubberBandResize, true);
	subWindowToAdd->setOption(QMdiSubWindow::SubWindowOption::AllowOutsideAreaHorizontally, false);
	subWindowToAdd->setOption(QMdiSubWindow::SubWindowOption::AllowOutsideAreaVertically, false);
	subWindowToAdd->setAttribute(Qt::WA_DeleteOnClose);
	subWindowToAdd->showMaximized();

	m_openedMaps[editorView->getName()] = subWindowToAdd;

	connect(subWindowToAdd, SIGNAL(destroyed(QObject*)), this, SLOT(slot_closeTab(QObject*)));
}

void MainWindow::slot_open() {
	QStringList files = QFileDialog::getOpenFileNames(
		this,
		"Ouvrir ...",
		nullptr,
		"Niveaux (*.pxlvl)",
		nullptr,
		QFileDialog::DontUseNativeDialog);
	
	QMdiSubWindow* subWindow1 = m_multipleDocumentInterface->addSubWindow(new EditorView(), Qt::SubWindow);
	subWindow1->setOption(QMdiSubWindow::RubberBandResize, true);
	subWindow1->setOption(QMdiSubWindow::SubWindowOption::AllowOutsideAreaHorizontally, false);
	subWindow1->setOption(QMdiSubWindow::SubWindowOption::AllowOutsideAreaVertically, false);
	subWindow1->setAttribute(Qt::WA_DeleteOnClose);
	subWindow1->showMaximized();
}

void MainWindow::slot_save() {
	QString fileName = QFileDialog::getSaveFileName(
		this, 
		"Enregistrer sous ...",
		nullptr,
		"Niveaux (*.pxlvl)",
		nullptr,
		QFileDialog::DontUseNativeDialog);
}

void MainWindow::slot_closeTab(QObject* destroyedTab) {
	EditorView* editorViewToClose = (EditorView*)(((QMdiSubWindow*)destroyedTab)->widget());

	QList<QMdiSubWindow*> tabs = m_multipleDocumentInterface->subWindowList();

	std::cout << tabs.size() << std::endl;

	//std::string tabName = (editorViewToClose->getName()).toStdString();
	//std::cout << tabName << std::endl;
}
