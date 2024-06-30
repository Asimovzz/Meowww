#include "feed.h"
#include "./ui_feed.h"

feed::feed(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::feed)
{
    ui->setupUi(this);
    init();
}

feed::~feed()
{
    delete ui;
}

void feed::init(){

    setModal(false);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->foodtable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    eatapplegif=new QMovie(":/img/feeding_Img/cateatapple.gif");
    eatcatfoodgif=new QMovie(":/img/feeding_Img/cateatcatfood.gif");
    eatchickengif=new QMovie(":/img/feeding_Img/cateatchicken.gif");
    eatfishgif=new QMovie(":/img/feeding_Img/cateatfish.gif");

    ui->toeat->resize(157,172);
    ui->eatapple_catfood->resize(157,172);
    ui->eatchicken->resize(187,171);
    ui->eatfish->resize(213,173);
    QPoint tmp=mapToGlobal(ui->eatfish->pos());
    ui->eatfish->move(tmp.x()-4,tmp.y()-1);
    //ui->Cat->setStyleSheet("border-image: url(:/img/feeding_Img/cattoeat.png);");
    ui->toeat->setPixmap(QPixmap(":/img/feeding_Img/cattoeat.png"));
    ui->toeat->setAlignment(Qt::AlignCenter);
    ui->toeat->setScaledContents(true);
    ui->toeat->show();
}

void feed::on_foodtable_cellClicked(int row, int column)
{
    ui->toeat->setVisible(false);
    if(row==0&&column==0){
        ui->eatapple_catfood->setMovie(eatapplegif);
        ui->eatapple_catfood->setAlignment(Qt::AlignCenter);
        ui->eatapple_catfood->setScaledContents(true);
        eatapplegif->start();
        ui->eatapple_catfood->show();
        //qDebug()<<eatapplegif->frameCount();
        connect(eatapplegif, &QMovie::finished, this,[=]{
            eatapplegif->stop();
            ui->eatapple_catfood->close();
            ui->toeat->setVisible(true);
        });
    }
    else if(row==0&&column==1){
        ui->eatapple_catfood->setMovie(eatcatfoodgif);
        ui->eatapple_catfood->setAlignment(Qt::AlignCenter);
        ui->eatapple_catfood->setScaledContents(true);
        eatcatfoodgif->start();
        ui->eatapple_catfood->show();
        //qDebug()<<eatcatfoodgif->frameCount();
        connect(eatcatfoodgif, &QMovie::finished, this,[=]{
            eatcatfoodgif->stop();
            ui->eatapple_catfood->close();
            ui->toeat->setVisible(true);
        });
    }
    else if(row==1&&column==0){
        ui->eatchicken->setMovie(eatchickengif);
        ui->eatchicken->setAlignment(Qt::AlignCenter);
        ui->eatchicken->setScaledContents(true);
        eatchickengif->start();
        ui->eatchicken->show();
        qDebug()<<eatchickengif->frameCount();
        connect(eatchickengif, &QMovie::finished, this,[=]{
            eatchickengif->stop();
            ui->eatchicken->close();
            ui->toeat->setVisible(true);
        });
    }
    else{
        ui->eatfish->setMovie(eatfishgif);
        ui->eatfish->setAlignment(Qt::AlignCenter);
        ui->eatfish->setScaledContents(true);
        eatfishgif->start();
        ui->eatfish->show();
        //qDebug()<<eatfishgif->frameCount();
        connect(eatfishgif, &QMovie::finished, this,[=]{
            eatfishgif->stop();
            ui->eatfish->close();
            ui->toeat->setVisible(true);
        });
    }
}

