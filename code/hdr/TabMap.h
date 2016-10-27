#pragma once

#include <QtWidgets>

class TabMap : public QMdiSubWindow {
	Q_OBJECT
private:
	bool m_isSavedOnce{ false };
	bool m_isModifiedSinceLastSave{ true };
	QString m_name;

public:
	explicit TabMap();
};
