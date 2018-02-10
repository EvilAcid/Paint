#include "paintwidget.h"
#include "paintsettings.h"
#include "eventhandler.h"

#include <QDebug>
#include <QPainter>
#include <QObject>

paintWidget::paintWidget(QWidget *parent)
	: QMainWindow(parent) {
    h = new EventHandler();
	setMinimumHeight(200);
	setMinimumWidth(200);
	QObject::connect(this, SIGNAL(signalOpenSettingsWindow()), h,
					 SLOT(SlotOpenSettingsWindow()));
	//--------------------------------------------------
	QObject::connect(h, SIGNAL(signalOpenSettings()),
					 this, SLOT(SlotOpenSettingsWindow()));
	//--------------------------------------------------
	QObject::connect(h, SIGNAL(signalSliderChanched(int)),
					 this, SLOT(SlotSliderChanchedValue(int)));
	//--------------------------------------------------
	emit signalOpenSettingsWindow();
}

paintWidget::~paintWidget() {
}

void paintWidget::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	//painter.drawLine(0, 0, width(), height());
	//Start links oben
	for (int i = 0; i <= height() + 1; i += distValue ) {
		painter.drawLine(0, 0, width(), i);
	}
	for (int i = 0; i <= width() + 1; i += distValue ) {
		painter.drawLine(0, 0, i, height());
	}
	//--------------------------------------------------
	//Start links oben
	for (int i = height(); i > 0 ; i -= distValue ) {
		painter.drawLine(0, i, width(), height());
	}
	for (int i = width(); i > 0 ; i -= distValue ) {
		painter.drawLine(i, 0, width(), height());
	}
}

void paintWidget::SlotOpenSettingsWindow() {
	qDebug() << "SlotopenSettingWindow ausgelöst";
    paintSettings *ps = new paintSettings(h);
	ps->show();
}

void paintWidget::SlotSliderChanchedValue(int v) {
	qDebug() << "Paint: Slider Wert geändert -> " << v;
	distValue = v;
	paintWidget::repaint();
}


