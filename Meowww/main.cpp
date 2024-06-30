#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Meowww_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.setFixedSize(360,360);
    w.setWindowTitle("Meowww");
    w.setWindowIcon(QIcon(":/img/image/cat1.png"));
    w.setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint); // 设置窗口无边框&置于所有窗口顶层
    w.show();
    return a.exec();
}
