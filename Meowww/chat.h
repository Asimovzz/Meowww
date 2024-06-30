#ifndef CHAT_H
#define CHAT_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class chat;
}
QT_END_NAMESPACE

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = nullptr);
    ~chat();
    void init();
    void response(const QString& ask);

private slots:
    void on_refreshbtn_clicked();

private:
    Ui::chat *ui;
    std::unordered_map<QString,QVector<QString>> dialogs;
    QVector<QString> asks;
};

#endif // CHAT_H
