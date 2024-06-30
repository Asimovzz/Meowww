#ifndef SKIN_H
#define SKIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class skin;
}
QT_END_NAMESPACE

class skin : public QMainWindow
{
    Q_OBJECT

public:
    skin(QWidget *parent = nullptr);
    ~skin();

signals:
    void skinChange(int newValue);

private slots:
    void on_choose_skin_1_clicked();

    void on_choose_skin_2_clicked();

    void on_choose_skin_3_clicked();

private:
    Ui::skin *ui;
};
#endif // SKIN_H
