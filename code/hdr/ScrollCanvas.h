#include <QAbstractScrollArea>

class ScrollCanvas : public QAbstractScrollArea {
public:
	ScrollCanvas(QWidget* parent = 0) : QAbstractScrollArea(parent) {
		QSize areaSize = viewport()->size();
		QSize  widgetSize = size();

		verticalScrollBar()->setPageStep(areaSize.height());
		horizontalScrollBar()->setPageStep(areaSize.width());

		verticalScrollBar()->setRange(0,  areaSize.height());
		horizontalScrollBar()->setRange(0, areaSize.width());
	}
	~ScrollCanvas(){}

	bool viewportEvent(QEvent * event) {
		viewport()->update();
		return true;
	}

	void resizeEvent(QResizeEvent * event) {
		OpenGLWidget* glw = dynamic_cast<OpenGLWidget*>(viewport());
		glw->resizeGL(width(), height());
	}

	void paintEvent(QPaintEvent *event) {
		OpenGLWidget* glw = dynamic_cast<OpenGLWidget*>(viewport());
		glw->paintGL();
	}
};