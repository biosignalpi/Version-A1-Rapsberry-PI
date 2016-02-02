#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>


/**
 * @brief Class used by PlottingWidget to enable a slider for the different signals plotted
 *
 * @author Jonatan
 */
class SliderWidget : public QWidget
{
    Q_OBJECT

public:
    SliderWidget(int min = 0, int max = 10, int tick = 1, QWidget * = NULL);
    void setTickSize(int);
    void setInterval(int, int);
    int getTicksize();
    int getMin();
    int getMax();
    int value();
    void setValue(int);

signals:
    void sliderReleased();
    void valueChanged(int);

private slots:
    void setLabelValue(int);

private:
    void updateRange();

    QSlider *slider;
    QLabel *valueLabel;
    int tickSize;
    int sliderMin;
    int sliderMax;
};

#endif // SLIDERWIDGET_H
