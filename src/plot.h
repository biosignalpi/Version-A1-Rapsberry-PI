#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>

class QwtPlotCurve;
class QwtPlotDirectPainter;
/**
 * @class Plot
 * @brief Extension of QwtPlot used for plotting data
 * @author Jonatan
 *
*/
class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot( QString curveTitle = "",  QWidget *parent = NULL );
    virtual ~Plot();

    void AppendPoint(const QPointF &);
    void DrawCurveSegment(const int length);
    void ClearPlot();
    void DrawSinglePoint();
    void IncrementInterval();
    void ClearInterval();
    void setInterval(int xmin, int xmax);
    void setCurveColor(const QColor & color);
    void setCurveMargin(double);
    void setYAxis(double, double);

private:
    QwtPlotCurve *d_curve;
    QwtPlotDirectPainter *d_directPainter;

    QwtInterval x_interval;
    double x_intervalSize;
    double curveMargin;
};

#endif // PLOT_H
