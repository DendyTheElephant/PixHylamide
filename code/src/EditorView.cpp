#include "EditorView.h"

EditorView::EditorView(QWidget* parent) : OpenGLWidget(60, parent) {
	setMinimumSize(1800, 1600);
}

EditorView::~EditorView() {
}

void EditorView::initializeGL() {
	glViewport(0, 0, width(), height());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glm::perspective(60.0f, static_cast<float>(width()) / static_cast<float>(height()), 0.001f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glm::lookAt(glm::vec3(0.0, 20.0, 10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

void EditorView::resizeGL(int width, int height) {
	if (height == 0)
		height = 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glm::perspective(60.0f, static_cast<float>(width) / static_cast<float>(height), 0.001f, 100.0f);
}

void EditorView::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}