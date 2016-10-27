#include "code/hdr/MainWindow.h"

MainWindow::MainWindow() {

	// Création des menus
	QMenu *fileMenu = menuBar()->addMenu("&Fichier");

	QAction *actionNew = fileMenu->addAction("&Nouveau");
	actionNew->setShortcut(QKeySequence("Ctrl+N"));
	actionNew->setIcon(QIcon("ressources/GUI/icons/30_Office.ico"));

	fileMenu->addSeparator();

	QAction *actionOpen = fileMenu->addAction("&Ouvrir");
	actionOpen->setShortcut(QKeySequence("Ctrl+O"));
	actionOpen->setIcon(QIcon("ressources/GUI/icons/15_Photo.ico"));

	QAction *actionSave = fileMenu->addAction("&Enregistrer");
	actionSave->setShortcut(QKeySequence("Ctrl+S"));
	actionSave->setIcon(QIcon("ressources/GUI/icons/04_Save.ico"));

	QAction *actionSaveAs = fileMenu->addAction("&Enregistrer sous ...");

	fileMenu->addSeparator();

	QAction *actionQuit = fileMenu->addAction("&Quitter");
	actionQuit->setShortcut(QKeySequence("Ctrl+Q"));


	QMenu *editMenu = menuBar()->addMenu("&Edition");

	QAction *actionSelectAll = editMenu->addAction("&Tout selectionner");
	actionSelectAll->setShortcut(QKeySequence("Ctrl+A"));

	editMenu->addSeparator();

	QAction *actionPrevious = editMenu->addAction("&Precedent");
	actionPrevious->setShortcut(QKeySequence("Ctrl+Z"));
	actionPrevious->setIcon(QIcon("ressources/GUI/icons/19_Left_Arrow.ico"));

	QAction *actionNext = editMenu->addAction("&Suivant");
	actionNext->setShortcut(QKeySequence("Alt+Z"));
	actionNext->setIcon(QIcon("ressources/GUI/icons/20_Right_Arrow.ico"));

	QMenu *displayMenu = menuBar()->addMenu("&Affichage");

	QPushButton* quitButton = new QPushButton("X");
	//quitButton->setIcon(QIcon("ressources/GUI/icons/14_Delete.ico"));
	quitButton->setStyleSheet("border-radius: 0; background-color: #972626;");

	menuBar()->setCornerWidget(quitButton, Qt::TopRightCorner);
	menuBar()->setStyleSheet("background-color: #262626;");

	// Création de la barre d'outils
	QToolBar *toolBar = addToolBar("Fichier");
	toolBar->setMovable(false);
	toolBar->setIconSize(QSize(24, 24));

	toolBar->addAction(actionNew);
	toolBar->addAction(actionOpen);
	toolBar->addSeparator();
	toolBar->addAction(actionSave);
	toolBar->addSeparator();
	toolBar->addAction(actionPrevious);
	toolBar->addAction(actionNext);
	toolBar->addSeparator();

	// Création des docks
	QDockWidget *dock = new QDockWidget("Palette", this);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

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

	EditorView* openGL1 = new EditorView();
		
	QScrollArea* scrollArea1 = new QScrollArea();
	scrollArea1->setBackgroundRole(QPalette::Dark);
	scrollArea1->setWidget(openGL1);
	scrollArea1->setAlignment(Qt::AlignCenter);
	scrollArea1->setWidgetResizable(false);
	scrollArea1->setVisible(true);

	QMdiSubWindow* subWindow1 = m_multipleDocumentInterface->addSubWindow(scrollArea1, Qt::SubWindow);
	subWindow1->setOption(QMdiSubWindow::RubberBandResize, true);
	subWindow1->setOption(QMdiSubWindow::SubWindowOption::AllowOutsideAreaHorizontally, false);
	subWindow1->setOption(QMdiSubWindow::SubWindowOption::AllowOutsideAreaVertically, false);
	subWindow1->setAttribute(Qt::WA_DeleteOnClose);
	subWindow1->showMaximized();

	setCentralWidget(m_multipleDocumentInterface);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	// Connexion des signaux
	connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(actionNew, SIGNAL(triggered()), this, SLOT(slot_new(void)));
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(slot_open(void)));
	connect(actionSave, SIGNAL(triggered()), this, SLOT(slot_save(void)));
	connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(slot_save(void)));
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



void MainWindow::mousePressEvent(QMouseEvent *event) {
	m_diff = event->pos();
	setCursor(QCursor(Qt::SizeAllCursor));
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
	Q_UNUSED(event);
	setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	QPoint p = event->globalPos();
	window()->move(p - m_diff);
}

