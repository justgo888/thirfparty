#include "lineswidget.h"
QT_CHARTS_USE_NAMESPACE

LinesWidget::LinesWidget(QWidget *parent)
    : QWidget{parent},max_points(51),xTickCount(6),yTickCount(6)
{

    pHLayout = new QHBoxLayout(this);

    lineSeries = new QLineSeries();        //创建折线系列
    lineSeries->setUseOpenGL(true);
    lineSeries->setPen(QPen(Qt::blue,1,Qt::SolidLine));
    lineSeries->pen().setColor("#87CEFA");
    /*为系列里添加100个数据*/
    for(quint8 i=0; i<max_points; i++)
    {
        lineSeries->append(i,0);
        pointSet.append(i);
    }
    lineSeries->setName("系列一");                  //设置系列名称

    axisX = new QValueAxis;
    //axisX->setRange(0,max_points);
    //axisX->setLabelFormat("%g");
    axisX->setTitleText("axisX");
    axisX->setTickCount(xTickCount);

    axisY = new QValueAxis;
    axisY->setRange(0,255);
    axisY->setTitleText("axisY");
    axisY->setTickCount(yTickCount);

    chartView = new QChartView(this);
    _Chart = new QChart();                          //创建图标对象
    _Chart->addSeries(lineSeries);                  //向图表中添加系列
    //_Chart->createDefaultAxes();                       //创建默认的坐标，必须在addSeries之后调用
    _Chart->setAxisX(axisX,lineSeries);
    _Chart->setAxisY(axisY,lineSeries);


    _Chart->setTheme(QChart::ChartThemeQt);           //设置图标主题
    _Chart->setTitle("图标实例");                       //设置图标名称
    //_Chart->legend()->hide();                          //隐藏图例，也就是不显示系列名称了
    chartView->setChart(_Chart);                    //向chartView中添加图标

    chartView->resize(QSize(500,300));              //重新设置chartView的大小

    chartView->setRenderHints(QPainter::Antialiasing);//消除边缘，看起来平滑一些


    leftBtn=new QPushButton(this);
    leftBtn->setText("<");
    //leftBtn->resize(80,200);
    leftBtn->setMaximumHeight(180);
    leftBtn->setMinimumHeight(180);
    leftBtn->setFont(QFont("仿宋", 18));
    connect(leftBtn,&QPushButton::clicked,this,&LinesWidget::slot_leftBtn_click);

    rhttBtn=new QPushButton(this);
    rhttBtn->setText(">");
    rhttBtn->setFont(QFont("仿宋", 18));
    //rhttBtn->resize(80,200);
    rhttBtn->setMaximumHeight(180);
    rhttBtn->setMinimumHeight(180);
    connect(rhttBtn,&QPushButton::clicked,this,&LinesWidget::slot_rhttBtn_click);

    pHLayout->addWidget(leftBtn);
    pHLayout->addWidget(chartView);
    pHLayout->addWidget(rhttBtn);

    this->setLayout(pHLayout);
    this->resize(700,400);
}

void LinesWidget::dynamicAppendPoint(uint16_t value)
{
    {
        //    if(pointSet.size()>max_points)
        //    {
        //        pointSet.pop_front();
        //        pointSet.append(value);
        //        lineSeries->clear();
        //        paintLinePoints();
        //    }
        //    else
        //    {
        //        pointSet.append(value);
        //        lineSeries->clear();
        //        paintLinePoints();
        //    }
    }


    if(pointSet.size()>max_points)
    {
        qreal dwidth= _Chart->plotArea().width()/(max_points-1); //一次滚动多少宽度
        _Chart->scroll(dwidth,0);
        lineSeries->append(pointSet.size(),value);
        pointSet.append(value);
    }
    else
    {
        pointSet.append(value);
    }
}

void LinesWidget::paintOnePoints(const uint16_t index, const uint8_t value)
{
    lineSeries->append(index,value);
}

void LinesWidget::clearLineSerial()
{
    lineSeries->clear();
    pointSet.clear();
}

void LinesWidget::paintLinePoints()
{
    for(uint16_t i=0;i<pointSet.size();i++)
    {
        lineSeries->append(i,pointSet[i]);
    }
}

void LinesWidget::slot_leftBtn_click()
{
    qreal dwidth= _Chart->plotArea().width()/(max_points-1); //一次滚动多少宽度
    _Chart->scroll(-dwidth*10,0);
}

void LinesWidget::slot_rhttBtn_click()
{
    qreal dwidth= _Chart->plotArea().width()/(max_points-1); //一次滚动多少宽度
    _Chart->scroll(dwidth*10,0);
}
