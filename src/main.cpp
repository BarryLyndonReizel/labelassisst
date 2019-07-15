#include "mainwin.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(APPNAME);
    a.setWindowIcon(QIcon(":/icons/app.png"));
    CMainWin w;
    w.show();

    return a.exec();
}
