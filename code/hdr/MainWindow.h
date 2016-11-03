#pragma once

#include <QtWidgets>
#include <iostream>

#include "EditorView.h"
#include "MainWindowMenu.h"
#include "StatusBar.h"

class MainWindow : public QMainWindow {
	Q_OBJECT
private:
	MainWindowMenu* m_menuBar;
	StatusBar* m_statusBar;
	std::map<QString,QMdiSubWindow*> m_openedMaps;
	QMdiArea* m_multipleDocumentInterface{ nullptr };

public slots:
	void slot_open();
	void slot_save();
	void slot_closeTab(QObject* destroyedTab);
public:
	explicit MainWindow(QWidget* parent = 0);
};
