#ifndef QTCALENDAR_H
#define QTCALENDAR_H

#pragma once
#include <QLabel>
#include <QPushButton>
#include <QDate>
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QLinearGradient>
#include <QFont>

QT_BEGIN_NAMESPACE
namespace Ui {
class QTcalendar;
}
QT_END_NAMESPACE

class Datewidget:public QWidget{
    Q_OBJECT

private:
    bool canSelect;  //只有当前月份的日期可以选择
    bool isMoveIn;
    QDate currentDate;

public:

    Datewidget(QWidget* parrent=nullptr):QWidget(parrent){
        isMoveIn=false;
    }

    ~Datewidget(){}

    void SetDate(int year,int month,int day,bool isThisMonth){
        currentDate.setDate(year,month,day);
        canSelect=isThisMonth;
        update();
    }

    QDate GetCurrentDate(){
        return currentDate;
    }

signals:
    void updateCurrentDate(QDate date);

protected:
    void mouseReleaseEvent(QMouseEvent* event){
        if(canSelect){
            emit updateCurrentDate(currentDate);
        }
    }

    void enterEvent(QEvent* event){
        isMoveIn=true;
        update();
    }

    void leaveEvent(QEvent* event){
        isMoveIn=false;
        update();
    }

    void paintEvent(QPaintEvent* event){
        QPainter painter(this);
        painter.save();
        QFont font;
        font.setFamily("华文仿宋");
        font.setPointSize(11);
        font.setBold(true);
        painter.setFont(font);
        int xx=1;
        int yy=1;
        int ww=this->geometry().width();
        int hh=this->geometry().height();
        if(isMoveIn){
            QPen pen;
            pen.setBrush(QColor(0,200,250,200));  //颜色，红绿蓝透明度
            pen.setWidth(2);
            painter.setPen(pen);
            painter.setFont(font);
            painter.drawRect(xx+1,yy+1,ww-2,hh-2);  //绘制日期矩形边框，左上角顶点（xx+2，yy+2），宽ww-4，高hh-4
        }
        painter.restore();
        if(canSelect){
            QPen pen2;
            pen2.setBrush(QColor(0,0,0));
            painter.setPen(pen2);
            painter.setFont(font);
            painter.drawText(ww/2-5,hh/2,QString::number(currentDate.day()));
        }
        else{
            QPen pen2;
            //#b2a9b1
            pen2.setBrush(QColor(178,169,177));
            painter.setPen(pen2);
            painter.setFont(font);
            painter.drawText(ww/2-5,hh/2,QString::number(currentDate.day()));
        }
    }

};

class QTcalendar : public QWidget
{
    Q_OBJECT

public:
    QTcalendar(QWidget *parent = nullptr);
    ~QTcalendar();
    void SetCurrentDate(int year,int month,int day);
    QDate GetCurrentDate();

private:
    void FillCalendar();
    void initCalendar();
    void initLabels();
    void init();
    QString getFormatMonth();

    QLabel *weeklabels[7];
    Datewidget *datewidgets[42];
    QPushButton *lastYearButton;
    QPushButton *lastMonthButton;
    QPushButton *nextMonthButton;
    QPushButton *nextYearButton;
    QDate currentDate;
    QLabel *cdlabel;

public slots:
    void HaveDateSelect(QDate date);
    void JumpLastYear();
    void JumpLastMonth();
    void JumpNextMonth();
    void JumpNextYear();

signals:
    void DateSelectSignal(QDate date);
};
#endif // QTCALENDAR_H
