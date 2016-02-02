#include "plot.h"
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_directpainter.h>
#include <qwt_plot_legenditem.h>
#include <qwt_curve_fitter.h>
#include <qwt_painter.h>

class CurveData: public QwtArraySeriesData<QPointF>
{
public:
    CurveData()
    {
    }

    virtual QRectF boundingRect() const
    {
        if ( d_boundingRect.width() < 0.0 )
            d_boundingRect = qwtBoundingRect( *this );

        return d_boundingRect;
    }

    inline void append( const QPointF &point )
    {
        d_samples += point;
    }

    void clear()
    {
        d_samples.clear();
        d_samples.squeeze();
        d_boundingRect = QRectF( 0.0, 0.0, -1.0, -1.0 );
    }
};

Plot::Plot(QString curveTitle, QWidget *parent ):
    QwtPlot( parent ),
    x_interval(0.0, 10.0),
    x_intervalSize(10.0),
    curveMargin(0.001)
{
    d_directPainter = new QwtPlotDirectPainter(this);
    QwtPlotCanvas *d_canvas = new QwtPlotCanvas();

    d_canvas->setPaintAttribute(QwtPlotCanvas::BackingStore, false);
    d_canvas->setPaintAttribute(QwtPlotCanvas::ImmediatePaint, true);

    setAutoReplot(false);
    setCanvas( d_canvas );

    QwtPlotLegendItem *d_legenditem = new QwtPlotLegendItem;
    d_legenditem->setAlignment(Qt::AlignTop);
    d_legenditem->setAlignment(Qt::AlignRight);
    d_legenditem->attach(this);

    QPalette pal = palette();
    pal.setColor(QPalette::WindowText, Qt::black);
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);

    plotLayout()->setAlignCanvasToScales(true);

//    setAxisTitle(QwtPlot::xBottom, "Time [s]");
//    setAxisTitle(QwtPlot::yLeft, "Voltage");
//    setAxisScale(QwtPlot::yLeft, -1.5,1.5);
    setAxisScale(QwtPlot::yLeft, 1.260,1.265);
    //setAxisScale(QwtPlot::yLeft, -1,1);
    //setAxisScale(QwtPlot::yLeft, 2.520,2.525);
    setAxisScale(QwtPlot::xBottom, x_interval.minValue(), x_interval.maxValue());

    QwtPlotGrid *d_grid = new QwtPlotGrid();
    d_grid->setPen(Qt::lightGray, 0.0, Qt::DotLine);
    d_grid->attach(this);

    d_curve = new QwtPlotCurve();
    d_curve->setPen(pal.color(QPalette::WindowText), 1.0);
    //d_curve->setPen(Qt::red);
    d_curve->setRenderHint(QwtPlotCurve::RenderAntialiased, true);
    d_curve->setData(new CurveData());
    d_curve->attach(this);
    d_curve->setTitle(curveTitle);
}

Plot::~Plot()
{
    delete d_directPainter;
}

void Plot::AppendPoint(const QPointF &point)
{
    CurveData *data = static_cast<CurveData *>(d_curve->data());
    data->append(point);
}

void Plot::IncrementInterval()
{
    x_interval = QwtInterval(x_interval.maxValue(), x_interval.maxValue()+x_intervalSize);
    setAxisScale(QwtPlot::xBottom, x_interval.minValue(), x_interval.maxValue());

    CurveData *data = static_cast<CurveData *>(d_curve->data());

    //Step = 0.0005 is 0.5mV per tick, disabed for the moment
    setAxisScale(QwtPlot::yLeft, data->boundingRect().top()-curveMargin, data->boundingRect().bottom()+curveMargin);

    //qDebug()<<"Min:"<<data->boundingRect().top()+0.01<<"Max:"<<data->boundingRect().bottom()-0.01;
}

void Plot::ClearInterval()
{
    x_interval = QwtInterval(0, x_intervalSize);
    setAxisScale(QwtPlot::xBottom, x_interval.minValue(), x_interval.maxValue());
}

void Plot::setInterval(int xmin, int xmax)
{
    x_interval = QwtInterval(xmin,xmax);
    setAxisScale(QwtPlot::xBottom, x_interval.minValue(), x_interval.maxValue());

    QwtPlot::replot();
}

void Plot::DrawCurveSegment(const int length)
{
    CurveData *data = static_cast<CurveData *>(d_curve->data());

    d_directPainter->drawSeries(d_curve, data->size()-(length+1), data->size()-1);
}

void Plot::DrawSinglePoint()
{
    CurveData *data = static_cast<CurveData *>(d_curve->data());

    d_directPainter->drawSeries(d_curve, data->size()-2, data->size()-1);
}

void Plot::ClearPlot()
{
    CurveData *data = static_cast<CurveData *>(d_curve->data());
    data->clear();

    QwtPlot::replot();
}

void Plot::setCurveColor(const QColor &color)
{
    d_curve->setPen(color);
}

void Plot::setCurveMargin(double margin)
{
    curveMargin = margin;
}

void Plot::setYAxis(double ymin, double ymax)
{
    setAxisScale(QwtPlot::yLeft, ymin-curveMargin, ymax+curveMargin);

    QwtPlot::replot();
}
