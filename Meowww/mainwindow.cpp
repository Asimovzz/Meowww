#include "mainwindow.h"
#include "./ui_mainwindow.h"

QImage Hi(":/img/image/hi.png");
QImage hi=Hi.scaled(91,81);

void MainWindow::tail_return()//猫猫收尾巴
{
    if(Skin==0)ui->Cat->setStyleSheet("border-image: url(:/img/image/cat1.png);");
    if(Skin==1)ui->Cat->setStyleSheet("border-image: url(:/img/image/cat2.png);");
    if(Skin==2)ui->Cat->setStyleSheet("border-image: url(:/img/image/cat3.png);");

    int rand_interval=QRandomGenerator::global()->bounded(3000,12000);
    //qDebug()<<rand_interval;
    timer1->start(rand_interval);

}

void MainWindow::tail_wave()//猫猫摇尾巴
{
    if(Skin==0)ui->Cat->setStyleSheet("border-image: url(:/img/image/cat1-1.png);");
    if(Skin==1)ui->Cat->setStyleSheet("border-image: url(:/img/image/cat2-2.png);");
    if(Skin==2)ui->Cat->setStyleSheet("border-image: url(:/img/image/cat3-3.png);");
    QTimer::singleShot(1000,this,SLOT(tail_return()));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //读取好感度
    Filename=":/img/intimacy.txt";
    QFile data(Filename);
    data.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&data);
    intimacy=in.readAll().toInt();
    //qDebug()<<intimacy;
    data.close();

    //音乐播放初始化
    srand(time(0));
    music1=new QMediaPlayer(this);
    music2=new QMediaPlayer(this);
    music3=new QMediaPlayer(this);
    Audio=new QAudioOutput(this);
    Audio->setVolume(0.6);
    last_played=0;

    //设置摇尾巴(时间随机,3s-12s)
    timer1=new QTimer();
    QObject::connect(timer1,&QTimer::timeout,this,&MainWindow::tail_wave);
    int rand_interval=QRandomGenerator::global()->bounded(3000,12000);
    timer1->start(rand_interval);

    ui->setupUi(this);
    
    //设置透明背景与鼠标悬停事件
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    ui->Cat->setAttribute(Qt::WA_Hover,true);
    ui->Cat->installEventFilter(this);
    //connect()
    //this->installEventFilter(this);

    //设置皮肤默认值
    Skin=0;

    //设置其他子窗口
    feedwin=new feed(this);
    feedwin->hide();
    ui->Exit->hide();

    chatwin=new chat(this);
    chatwin->hide();

    webwin=new web(this);
    webwin->hide();

    calendarwin=new QTcalendar(this);
    calendarwin->hide();

    skinwin=new skin(this);
    skinwin->hide();
    connect(skinwin,&skin::skinChange,this,&MainWindow::change_skin);

}

MainWindow::~MainWindow()
{
    QFile Data(Filename);
    Data.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&Data);
    out<<intimacy;
    Data.close();
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent * event)//点击鼠标时获取位置信息
{
    mouse_pos = event->globalPos();
    window_pos = this->pos();
    diff_pos = mouse_pos - window_pos;

    web_pos = mouse_pos - webwin->pos();
    chat_pos = mouse_pos - chatwin->pos();
    feed_pos = mouse_pos - feedwin->pos();
    calendar_pos = mouse_pos - calendarwin->pos();
    skin_pos = mouse_pos - skinwin->pos();

}

void MainWindow::mouseMoveEvent(QMouseEvent* event)//让猫猫跟随鼠标移动
{
    QPoint pos = event->globalPos();
    this->move(pos - diff_pos);

    if(webwin->isVisible())webwin->move(pos - web_pos);
    if(chatwin->isVisible())chatwin->move(pos - chat_pos);
    if(feedwin->isVisible())feedwin->move(pos - feed_pos);
    if(calendarwin->isVisible())calendarwin->move(pos - calendar_pos);
    if(skinwin->isVisible())skinwin->move(pos - skin_pos);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)//设置悬停事件,鼠标放在猫猫身上时显示菜单栏
{
    if(obj==ui->Cat)
    {
        if(event->type()==QEvent::HoverEnter){
            ui->hi->setPixmap(QPixmap::fromImage(hi));
            ui->hi->show();

            ui->Button1->show();
            ui->Button2->show();
            ui->Button3->show();
            ui->Button4->show();
            ui->Button5->show();
            ui->Button6->show();
            ui->Button7->show();
            ui->Button8->show();
        }

        if(event->type()==QEvent::HoverLeave){
            ui->hi->close();

            QTimer::singleShot(4000,this,[this]{//菜单栏在鼠标离开4秒之后收起
                ui->Button1->close();
                ui->Button2->close();
                ui->Button3->close();
                ui->Button4->close();
                ui->Button5->close();
                ui->Button6->close();
                ui->Button7->close();
                ui->Button8->close();
            });

        }

    }

}

void MainWindow::change_skin(int newValue)//接收信号,换皮肤
{
    Skin=newValue;
    switch(Skin)
    {
        case 0:
            ui->Cat->setStyleSheet("border-image: url(:/img/image/cat1.png);");
            break;

        case 1:
            ui->Cat->setStyleSheet("border-image: url(:/img/image/cat2.png);");
            break;

        case 2:
            ui->Cat->setStyleSheet("border-image: url(:/img/image/cat3.png);");
            break;
    }
}

void MainWindow::check_window()//检查其他窗口是否关闭
{
    if(feedwin->isVisible())feedwin->hide();
    if(skinwin->isVisible())skinwin->hide();
    if(calendarwin->isVisible())calendarwin->hide();
    if(webwin->isVisible())webwin->hide();
    if(chatwin->isVisible())chatwin->hide();
}

void MainWindow::on_Button1_clicked()//给猫猫喂食按钮
{

    if(feedwin->isHidden()){
        QPoint tmp=mapToGlobal(ui->Button1->pos());
        feedwin->move(tmp.x()-231,tmp.y()+12);
        check_window();
        feedwin->show();
        ui->Cat->setVisible(false);
        ui->Exit->show();
    }
}

void MainWindow::on_Button2_clicked()//猫猫换皮肤按钮
{

    if(skinwin->isHidden()){
        QPoint tmp=mapToGlobal(ui->Button2->pos());
        skinwin->move(tmp.x()-8,tmp.y()-51);
        check_window();
        skinwin->show();
    }
    else{
        skinwin->hide();
    }
}

void MainWindow::on_Button3_clicked()//和猫猫一起听音乐
{

    int ran=rand()%3+1;
    if(ran==last_played)ran=(ran)%3+1;

    //qDebug()<<ran;
    music1->stop();
    music2->stop();
    music3->stop();

    if(ran==1){
        intimacy+=15;
        music1->setSource(QUrl::fromUserInput("qrc:/music/music/八木侑紀,佐伯伊織,井澤詩織 - Shiny Happy Days.mp3"));
        music1->setAudioOutput(Audio);
        music1->play();
        //qDebug()<<"1 played";
        last_played=1;
    }

    if(ran==2){
        intimacy+=10;
        music2->setSource(QUrl::fromUserInput("qrc:/music/music/FLuoRiTe - NYA!!!.mp3"));
        music2->setAudioOutput(Audio);
        music2->play();
        //qDebug()<<"2 played";
        last_played=2;
    }

    if(ran==3){
        intimacy+=5;
        music3->setSource(QUrl::fromUserInput("qrc:/music/music/Bradley - Tom And Jerry.mp3"));
        music3->setAudioOutput(Audio);
        music3->play();
        //qDebug()<<"3 played";
        last_played=3;
    }

}

void MainWindow::on_Button4_clicked()//打开猫猫日历
{

    if(calendarwin->isHidden()){
        QPoint tmp=mapToGlobal(ui->Button4->pos());
        calendarwin->move(tmp.x()-310,tmp.y()-110);
        //calendarwin->setStyleSheet("#calendarwin{border-image:url(:/img/image/calendar_background.png)}");
        check_window();
        calendarwin->show();
    }
    else{
        calendarwin->hide();
    }
}

void MainWindow::on_Button5_clicked()//访问猫猫常用的网站
{
    if(webwin->isHidden()){
        QPoint tmp=mapToGlobal(ui->Button5->pos());
        webwin->move(tmp.x()-180,tmp.y());
        check_window();
        webwin->show();
    }
    else{
        webwin->hide();
    }
}

void MainWindow::on_Button6_clicked()//打开猫猫聊天室
{
    intimacy+=6;
    if(chatwin->isHidden()){
        QPoint tmp=mapToGlobal(ui->Button6->pos());
        chatwin->move(tmp.x()-231,tmp.y()-165);
        check_window();
        chatwin->show();
        //ui->Cat->setVisible(false);
    }
    else{
        chatwin->hide();
        //ui->Cat->setVisible(true);
    }

}

void MainWindow::on_Button7_clicked()//最小化猫猫
{
    //渐变消失动画
    QPropertyAnimation *anime=new QPropertyAnimation(this,"windowOpacity");
    anime->setDuration(260);
    anime->setStartValue(1);
    anime->setEndValue(0);

    connect(anime,&QPropertyAnimation::finished,[this](){this->showMinimized(); this->setWindowOpacity(1);});
    anime->start();

}

void MainWindow::on_Button8_clicked()//关闭猫猫按钮
{
    //渐变消失动画
    QPropertyAnimation *anime=new QPropertyAnimation(this,"windowOpacity");
    anime->setDuration(260);
    anime->setStartValue(1);
    anime->setEndValue(0);

    connect(anime,&QPropertyAnimation::finished,[this](){this->close(); this->setWindowOpacity(1);});
    anime->start();
    //this->close();
}

void MainWindow::on_Exit_clicked()
{
    feedwin->hide();
    ui->Cat->setVisible(true);
    ui->Exit->close();
}
