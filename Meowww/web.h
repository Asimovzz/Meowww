#ifndef WEB_H
#define WEB_H

#include <QDialog>
#include <QDesktopServices>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui {
class web;
}
QT_END_NAMESPACE

class web : public QDialog
{
    Q_OBJECT

public:
    explicit web(QWidget *parent = nullptr);
    ~web();
    void init();

private slots:

    void on_coursebtn_clicked();
    void on_netdiskbtn_clicked();
    void on_portalbtn_clicked();
    void on_treeholebtn_clicked();

private:
    Ui::web *ui;
};

#endif // WEB_H
