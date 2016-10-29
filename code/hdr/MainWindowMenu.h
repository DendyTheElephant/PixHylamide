#pragma once

#include <QtWidgets>

class MainWindowMenu : public QMenuBar {
	Q_OBJECT
private:
	const int MENU_SIZE{ 200 };

	QPoint m_diff{ 0, 0 };
	bool m_isGrabbed{ false };
	bool m_isMaximized{ false };

	int m_widthBeforeMaximization;
	int m_heightBeforeMaximization;

	QMenu* m_fileMenu;
	QMenu* m_editionMenu;
	QMenu* m_displayMenu;

	bool isOnGrabZone(QMouseEvent *event);
	void maximize();

	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private slots:
	void slot_reduce() {
		window()->showMinimized();
	}
	void slot_maximize() {
		maximize();
	}

public:
	explicit MainWindowMenu(QWidget* parent = 0);

	QAction* action_New;
	QAction* action_Open;
	QAction* action_Save;
	QAction* action_SaveAs;
	QAction* action_Quit;
	QAction* action_SelectAll;
	QAction* action_Previous;
	QAction* action_Next;
};
