#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"feed.h"
#include"chat.h"
#include"web.h"
#include"skin.h"
#include"qtcalendar.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <QPropertyAnimation>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QtMultimediaWidgets>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void check_window();
    QPoint diff_pos;
    QPoint mouse_pos;
    QPoint window_pos;
    QPoint web_pos;
    QPoint chat_pos;
    QPoint feed_pos;
    QPoint calendar_pos;
    QPoint skin_pos;
    int intimacy;//猫猫亲密度
    int Skin;//猫猫当前皮肤
    QString Filename;
    QTimer *timer1;
    QTimer * timer2;

    QAudioOutput *Audio;
    QMediaPlayer *music1;
    QMediaPlayer *music2;
    QMediaPlayer *music3;
    int last_played;

    feed* feedwin;
    chat* chatwin;
    web* webwin;
    skin* skinwin;
    QTcalendar* calendarwin;




private slots:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    bool eventFilter(QObject*,QEvent*);

    void tail_wave();
    void tail_return();
    //void random_wave(QTimer*);
    void change_skin(int newValue);

    void on_Button1_clicked();
    void on_Button2_clicked();
    void on_Button3_clicked();
    void on_Button4_clicked();
    void on_Button5_clicked();
    void on_Button6_clicked();
    void on_Button7_clicked();
    void on_Button8_clicked();

    void on_Exit_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
