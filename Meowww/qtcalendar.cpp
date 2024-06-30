#include "qtcalendar.h"

QTcalendar::QTcalendar(QWidget *parent):QWidget(parent){
    this->setAutoFillBackground(true);
    this->setStyleSheet(("font-size:14px;"
                         "font-family:华文仿宋;"));

    this->setMinimumSize(290,225);
    this->setMaximumSize(290,225);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::FramelessWindowHint;
    flags |=Qt::WindowStaysOnTopHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    QFrame* background=new QFrame(this);
    background->setObjectName("background");
    background->setGeometry(this->geometry());
    background->resize(width(),height());
    background->setStyleSheet("QFrame#background{border-image:url(:/img/image/calendar_background.png)}");


    init();
}

QTcalendar::~QTcalendar(){}

void QTcalendar::SetCurrentDate(int year,int month,int day){
    currentDate.setDate(year,month,day);
}

QDate QTcalendar::GetCurrentDate(){
    return currentDate;
}

void QTcalendar::FillCalendar(){
    QDate firstDay;
    firstDay.setDate(currentDate.year(),currentDate.month(),1);
    int firstnum=firstDay.dayOfWeek();
    QDate firstDayOfMonth=firstDay.addDays(-(firstnum-1));
    for(int i=0;i<42;i++){
        if(firstDayOfMonth.month()!=currentDate.month()){
            datewidgets[i]->SetDate(firstDayOfMonth.year(),firstDayOfMonth.month(),firstDayOfMonth.day(),false);
        }
        else {
            datewidgets[i]->SetDate(firstDayOfMonth.year(),firstDayOfMonth.month(),firstDayOfMonth.day(),true);
        }
        firstDayOfMonth=firstDayOfMonth.addDays(1);
    }
}

void QTcalendar::initLabels(){
    for(int i=0;i<7;i++){
        weeklabels[i]=new QLabel(this);
        weeklabels[i]->setAttribute(Qt::WA_TranslucentBackground);
        weeklabels[i]->setGeometry(17+i*40,25,40,20);
    }
    weeklabels[0]->setText("Mon");
    weeklabels[1]->setText("Tue");
    weeklabels[2]->setText("Wed");
    weeklabels[3]->setText("Thu");
    weeklabels[4]->setText("Fri");
    weeklabels[5]->setText("Sat");
    weeklabels[6]->setText("Sun");
}

void QTcalendar::initCalendar(){
    for(int i=0;i<42;i++){
        datewidgets[i]=new Datewidget(this);
        datewidgets[i]->setGeometry(5+i%7*40,40+i/7*30,40,30);
        connect(datewidgets[i],SIGNAL(updateCurrentDate(QDate)),this,SLOT(HaveDateSelect(QDate)));
    }
    FillCalendar();
}

void QTcalendar::init(){
    currentDate=QDate::currentDate();
    lastYearButton=new QPushButton(this);
    lastYearButton->setGeometry(5,5,50,25);
    lastYearButton->setText("<<");
    lastYearButton->setWindowOpacity(0.1);
    lastMonthButton=new QPushButton(this);
    lastMonthButton->setGeometry(60,5,50,25);
    lastMonthButton->setText("<");
    lastMonthButton->setWindowOpacity(0.1);
    cdlabel=new QLabel(this);
    cdlabel->setGeometry(116,6,64,20);
    cdlabel->setText(getFormatMonth());
    nextMonthButton=new QPushButton(this);
    nextMonthButton->setGeometry(180,5,50,25);
    nextMonthButton->setText(">");
    nextMonthButton->setWindowOpacity(0.1);
    nextYearButton=new QPushButton(this);
    nextYearButton->setGeometry(235,5,50,25);
    nextYearButton->setText(">>");
    nextYearButton->setWindowOpacity(0.1);
    connect(lastYearButton,SIGNAL(clicked()),this,SLOT(JumpLastYear()));
    connect(lastMonthButton,SIGNAL(clicked()),this,SLOT(JumpLastMonth()));
    connect(nextMonthButton,SIGNAL(clicked()),this,SLOT(JumpNextMonth()));
    connect(nextYearButton,SIGNAL(clicked()),this,SLOT(JumpNextYear()));  

    initLabels();
    initCalendar();
}

QString QTcalendar::getFormatMonth(){
    QString ans="";
    ans+=QString::number(currentDate.year());
    ans+="年";
    ans+=QString::number(currentDate.month());
    ans+="月";
    return ans;
}

void QTcalendar::HaveDateSelect(QDate date){
    emit DateSelectSignal(date);
}

void QTcalendar::JumpLastYear(){
    currentDate=currentDate.addYears(-1);
    FillCalendar();
    cdlabel->setText(getFormatMonth());
}

void QTcalendar::JumpLastMonth(){
    currentDate=currentDate.addMonths(-1);
    FillCalendar();
    cdlabel->setText(getFormatMonth());
}

void QTcalendar::JumpNextMonth(){
    currentDate=currentDate.addMonths(1);
    FillCalendar();
    cdlabel->setText(getFormatMonth());
}

void QTcalendar::JumpNextYear(){
    currentDate=currentDate.addYears(1);
    FillCalendar();
    cdlabel->setText(getFormatMonth());
}
