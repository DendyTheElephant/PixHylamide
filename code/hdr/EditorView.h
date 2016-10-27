#pragma once

#include <iostream>

/* External dependencies */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLWidget.h"

class EditorView : public OpenGLWidget {
	Q_OBJECT
private:
	bool m_isSavedOnce{ false };
	bool m_isModifiedSinceLastSave{ true };
	QString m_name;
	QAbstractScrollArea *m_scrollingWidget;

public:
	explicit EditorView(QWidget* parent = 0);
	~EditorView();
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

	bool isSavedOnce() const { return m_isSavedOnce; }
	bool isModifiedSinceLastSave() const { return m_isModifiedSinceLastSave; }
	void setName(QString name) { m_name = name; }
	QString getName() const { return m_name; }
};
