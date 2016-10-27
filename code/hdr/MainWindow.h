#pragma once

#include <QtWidgets>
#include <iostream>

#include "EditorView.h"
#include "ScrollCanvas.h"

class MainWindow : public QMainWindow {
	Q_OBJECT
private:
	std::map<QString,QMdiSubWindow*> m_openedMaps;
	QMdiArea* m_multipleDocumentInterface{ nullptr };
	unsigned int m_newFiles_counter{ 0 };

public slots:
	void slot_new();
	void slot_open();
	void slot_save();
	void slot_closeTab(QObject* destroyedTab);
public:
	explicit MainWindow();
};
