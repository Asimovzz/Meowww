#include "chat.h"
#include "./ui_chat.h"
#include"QRandomGenerator"

chat::chat(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chat)
{
    ui->setupUi(this);
    init();
}

chat::~chat()
{
    delete ui;
}

void chat::init(){
    setModal(false);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    asks=QVector<QString>{"hello","hi~~~","你好","meowwwwww","goodbye","byebye","See you again","OI!","Mamba out!","What can I say!","man!",
                            "Whoa","Geez","Hmmmmm" };

    dialogs["hello"]=QVector<QString>{"hi~~~","hello!!!","你好","meowwwwww"};
    dialogs["hi~~~"]=QVector<QString>{"hi~~~","hello!!!","你好","meowwwwww"};
    dialogs["你好"]=QVector<QString>{"hi~~~","hello!!!","你好","meowwwwww"};
    dialogs["meowwwwww"]=QVector<QString>{"meowwwwww","meow","meowwww","meowwwww","woemmmmmm"};

    dialogs["goodbye"]=QVector<QString>{"meowwwwww","byebye","See you again"};
    dialogs["byebye"]=QVector<QString>{"meowwwwww","byebye","See you again"};
    dialogs["See you again"]=QVector<QString>{"meowwwwww","byebye","See you again"};

    dialogs["OI!"]=QVector<QString>{"OI!"};

    dialogs["man!"]=QVector<QString>{"Mamba out!","What can I say!"};
    dialogs["Mamba out!"]=QVector<QString>{"man!","What can I say!"};
    dialogs["What can I say!"]=QVector<QString>{"Mamba out!","man!"};

    dialogs["Hmmmmm"]=QVector<QString>{"yamiyami","Whoa","Geez"};
    dialogs["Whoa"]=QVector<QString>{"yamiyami","Hmmmmm","Geez"};
    dialogs["Geez"]=QVector<QString>{"yamiyami","Whoa","Hmmmmm"};

    connect(ui->words1,&QPushButton::clicked,this,[&](){
        this->response(ui->words1->text());
    });
    connect(ui->words2,&QPushButton::clicked,this,[&](){
       this->response(ui->words2->text());
    });
    connect(ui->words3,&QPushButton::clicked,this,[&](){
        this->response(ui->words3->text());
    });
    connect(ui->words4,&QPushButton::clicked,this,[&](){
        this->response(ui->words4->text());
    });


}

void chat::response(const QString& ask){
    int randomIndex = QRandomGenerator::global()->bounded(0,dialogs[ask].size());
    //qDebug()<<randomIndex;
    ui->responsetext->setText(dialogs[ask][randomIndex]);
}

void chat::on_refreshbtn_clicked()
{
    int randomIndex1 = QRandomGenerator::global()->bounded(0,asks.size());
    int randomIndex2 = QRandomGenerator::global()->bounded(0,asks.size());
    int randomIndex3 = QRandomGenerator::global()->bounded(0,asks.size());
    int randomIndex4 = QRandomGenerator::global()->bounded(0,asks.size());

    ui->words1->setText(asks[randomIndex1]);
    ui->words2->setText(asks[randomIndex2]);
    ui->words3->setText(asks[randomIndex3]);
    ui->words4->setText(asks[randomIndex4]);
}

