#include "EditorView.h"

EditorView::EditorView(QFileInfo filePath, QWidget* parent) : QGraphicsView(parent) {

	setRenderHints(QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);

	m_filePath = filePath;

	// Image creation
	m_image_background = QImage(m_filePath.absoluteFilePath());
	m_image_normalMap = QImage(m_image_background.size(), QImage::Format_ARGB32);
	m_image_sketch = QImage(m_image_background.size(), QImage::Format_ARGB32);

	// Scene initialization
	m_scene = new QGraphicsScene();
	setScene(m_scene);

	// Alpha mask for the painter, and transparent filling for unintialized images
	m_image_mask = m_image_background.createAlphaMask();
	m_painter = new QPainter(&m_image_normalMap);
	m_painter->setRenderHint(QPainter::Antialiasing);
	m_painter->setClipRegion(QRegion(QPixmap::fromImage(m_image_mask)));
	m_image_normalMap.fill(Qt::transparent);
	m_image_sketch.fill(Qt::transparent);


	// Creation of the GraphicsItems (layers made from Images)
	m_layer_background = m_scene->addPixmap(QPixmap::fromImage(m_image_background));
	m_layer_background->setTransformationMode(Qt::SmoothTransformation);
	m_layer_background->setOpacity(0.5);
	m_layer_background->setZValue(1);

	m_layer_sketch = m_scene->addPixmap(QPixmap::fromImage(m_image_sketch));
	m_layer_sketch->setTransformationMode(Qt::SmoothTransformation);
	m_layer_sketch->setZValue(2);

	m_layer_normalMap = m_scene->addPixmap(QPixmap::fromImage(m_image_normalMap));
	m_layer_normalMap->setTransformationMode(Qt::SmoothTransformation);
	m_layer_normalMap->setZValue(0);


	m_polyLine[0] = m_polyLine[1] = m_polyLine[2] = QPoint();

	// Fills the normal map with flat value!
	m_painter->fillRect(0, 0, m_image_background.width() - 1, m_image_background.height() - 1, QColor(127, 127, 255, 255));
	m_layer_normalMap->setPixmap(QPixmap::fromImage(m_image_normalMap));
}

EditorView::~EditorView() {
}

void EditorView::mousePressEvent(QMouseEvent *event) {

}

void EditorView::mouseReleaseEvent(QMouseEvent *event) {
	
}

void EditorView::mouseMoveEvent(QMouseEvent *event) {

}

void EditorView::wheelEvent(QWheelEvent* event) {
	//e->modifiers().testFlag(Qt::ControlModifier) : CTRL

	// Typical Calculations (Ref Qt Doc)
	const int degrees = event->delta() / 8;
	int steps = degrees / 15;

	double scaleFactor = 1.15; //How fast we zoom
	
	if (steps > 0) {
		scale(scaleFactor, scaleFactor);
		centerOn(m_layer_background);
	}
	else {
		scale(1.0/scaleFactor, 1.0/scaleFactor);
		centerOn(m_layer_background);
	}
}

void EditorView::tabletEvent(QTabletEvent *event) {

	switch (event->type()) {
		case QEvent::TabletPress:
			if (!m_styletDown) {
				m_styletDown = true;
				m_polyLine[0] = m_polyLine[1] = m_polyLine[2] = event->pos();
			}
			break;
		case QEvent::TabletRelease:
			if (m_styletDown)
				m_styletDown = false;
			break;
		case QEvent::TabletMove:
			m_polyLine[2] = m_polyLine[1];
			m_polyLine[1] = m_polyLine[0];
			m_polyLine[0] = event->pos();

			if (m_styletDown) {
				paintPixmap(event);
			}
			break;
		default:
			break;
	}
	update();
}

void EditorView::paintPixmap(QTabletEvent *event) {
	m_painter->fillRect(0, 0, m_image_background.width() - 1, m_image_background.height() - 1, QColor(127, 127, 255, 255));

	m_layer_normalMap->setPixmap(QPixmap::fromImage(m_image_normalMap));
	viewport()->update();
}