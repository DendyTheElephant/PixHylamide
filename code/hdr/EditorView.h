#pragma once

#include <iostream>

/* External dependencies */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <QtWidgets>

class EditorView : public QGraphicsView {
	Q_OBJECT
private:
	bool m_isSavedOnce{ false };
	bool m_isModifiedSinceLastSave{ true };
	QFileInfo m_filePath;

	QImage m_image_background;
	QImage m_image_sketch;
	QImage m_image_normalMap;

	QImage m_image_mask;
	QPainter* m_painter;

	QPoint m_polyLine[3];
	bool m_styletDown{false};

	QGraphicsScene* m_scene;
	QGraphicsPixmapItem* m_layer_background;
	QGraphicsPixmapItem* m_layer_sketch;
	QGraphicsPixmapItem* m_layer_normalMap;

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent* event);

	void tabletEvent(QTabletEvent *event);
	void paintPixmap(QTabletEvent* event);

	//void paintEvent(QPaintEvent *);

public:
	explicit EditorView(QFileInfo filePath, QWidget* parent = 0);
	~EditorView();
};
