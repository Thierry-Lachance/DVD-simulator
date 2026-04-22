#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QUi>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;
    window.setGeometry(1,1,12,12);
    QWidget widget;
    window.setCentralWidget(&widget);
    window.setWindowTitle("A");


    window.show();
    return QCoreApplication::exec();
}
