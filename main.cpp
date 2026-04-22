
#include <iostream>
#include <QtWidgets>
#include <QtCharts>

#include "App.h"

using namespace std;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QWidget window;

    App app("Test",100,100,&a,&window);
    QHBoxLayout *layout = new QHBoxLayout();
    app.addLayout("mainLayout",layout);
    app.setActiveLayout("mainLayout");

    QMenuBar *bar = new QMenuBar();
    app.addWidget("menuBar",bar);
    app.addWidgetToLayout("menuBar","mainLayout");

    QPushButton *button = new QPushButton(&window);
    button->setText("Exit Application...");
    app.addWidget("exitButton",button);
    app.addWidgetToLayout("exitButton","mainLayout");
    QObject::connect(button,&QPushButton::clicked,[&]() {
        cout << "You clicked the exit button..." << endl;
        QApplication::quit();
    });

    return app.runA*pp();
}