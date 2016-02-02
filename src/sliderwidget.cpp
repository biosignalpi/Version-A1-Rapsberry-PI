#include "sliderwidget.h"
#include <QtWidgets>
#include <QDebug>

SliderWidget::SliderWidget(int min, int max, int tick, QWidget *parent):
    QWidget( parent )
{
    sliderMin = min;
    sliderMax = max;
    tickSize = tick;

    slider = new QSlider(Qt::Horizontal);
    valueLabel = new QLabel;

    slider->setRange(sliderMin,sliderMax);

    valueLabel->setText(QString::number(slider->value()));

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setLabelValue(int)));
    connect(slider, SIGNAL(valueChanged(int)), SIGNAL(valueChanged(int)));
    connect(slider, SIGNAL(sliderReleased()), SIGNAL(sliderReleased()));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(slider, 19);
    hLayout->addWidget(valueLabel, 1);

    setLayout(hLayout);
}

void SliderWidget::setLabelValue(int newValue)
{
    valueLabel->setText(QString::number(sliderMin + newValue*tickSize));
}

void SliderWidget::updateRange()
{
    slider->setRange(sliderMin, sliderMax);
}

void SliderWidget::setTickSize(int t)
{
    tickSize = t;
}

void SliderWidget::setInterval(int min, int max)
{
    sliderMin = min;
    sliderMax = max;

    updateRange();
}

int SliderWidget::getTicksize()
{
    return tickSize;
}

int SliderWidget::getMin()
{
    return sliderMin;
}

int SliderWidget::getMax()
{
    return sliderMax;
}

int SliderWidget::value()
{
    return slider->value();
}

void SliderWidget::setValue(int val)
{
    slider->setValue(val);
    setLabelValue(val);
}
