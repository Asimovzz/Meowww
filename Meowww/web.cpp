#include "web.h"
#include "./ui_web.h"

web::web(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::web)
{
    ui->setupUi(this);
    init();
}

web::~web()
{
    delete ui;
}

void web::init(){
    setModal(false);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->coursebtn->setToolTip("北大教学网");
    ui->netdiskbtn->setToolTip("北大网盘");
    ui->portalbtn->setToolTip("北大门户");
    ui->treeholebtn->setToolTip("北大树洞");
}
void web::on_coursebtn_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("https://course.pku.edu.cn/")));
}

void web::on_netdiskbtn_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("https://disk.pku.edu.cn/")));
}

void web::on_portalbtn_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("https://portal.pku.edu.cn/")));
}

void web::on_treeholebtn_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("https://treehole.pku.edu.cn/web/")));
}

