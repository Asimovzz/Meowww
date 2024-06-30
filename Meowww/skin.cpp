#include "skin.h"
#include "./ui_skin.h"

skin::skin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::skin)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setMinimumSize(170,90);
    this->setMaximumSize(170,90);
}

skin::~skin()
{
    delete ui;
}

void skin::on_choose_skin_1_clicked()
{
    emit skinChange(0);
}


void skin::on_choose_skin_2_clicked()
{
    emit skinChange(1);
}


void skin::on_choose_skin_3_clicked()
{
    emit skinChange(2);
}

