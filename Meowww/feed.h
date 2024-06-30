#ifndef FEED_H
#define FEED_H

#include <QDialog>
#include<QPixmap>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QPushButton>
#include<QMovie>
#include<QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class feed;
}
QT_END_NAMESPACE

class feed : public QDialog
{
    Q_OBJECT

public:
    explicit feed(QWidget *parent = nullptr);
    ~feed();
    void init();

public slots:
    void on_foodtable_cellClicked(int row, int column);


private:
    Ui::feed *ui;

    QMovie * eatapplegif;

    QMovie * eatcatfoodgif;

    QMovie * eatchickengif;

    QMovie * eatfishgif;
};

#endif // FEED_H
