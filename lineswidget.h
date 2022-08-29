#ifndef LINESWIDGET_H
#define LINESWIDGET_H

#include <QWidget>
#include <QChart>
#include <QtCharts>
#include <QChartView>
#include <QSplineSeries>
#include <QPushButton>

class LinesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LinesWidget(QWidget *parent = nullptr);

    void    dynamicAppendPoint(uint16_t value);
    void    paintOnePoints(const uint16_t index,const uint8_t value);
    void    clearLineSerial();

signals:

public slots:
    void slot_leftBtn_click();
    void slot_rhttBtn_click();

private:
    uint16_t            max_points;
    uint8_t             xTickCount;
    uint8_t             yTickCount;
    QVector<uint16_t>   pointSet;

    QChart              *_Chart;
    QLineSeries         *lineSeries;

    QChartView          *chartView;
    QValueAxis          *axisX;
    QValueAxis          *axisY;
    QPushButton         *leftBtn;
    QPushButton         *rhttBtn;
    QHBoxLayout         *pHLayout;// = new QHBoxLayout();

    void    paintLinePoints();

};

#endif // LINESWIDGET_H
