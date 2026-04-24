
#include <iostream>
#include <QtWidgets>
#include <QtCharts>

#include "App.h"

using namespace std;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    App app("Test",100,100,&a);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    app.addLayout("mainLayout",mainLayout);

    QHBoxLayout *statsLayout = new QHBoxLayout();
    app.addLayout("statsLayout",statsLayout);

    QAction *statsAction = new QAction();
    statsAction->setText("Stats");
    QObject::connect(statsAction, &QAction::triggered,[&]() {
        cout << "Switiching to stats page" << endl;
        app.setActiveLayout("statsLayout");
    });

    QAction *mainMenuAction = new QAction();
    mainMenuAction->setText("Main Menu");
    QObject::connect(mainMenuAction, &QAction::triggered,[&]() {
        cout << "Switiching to main page" << endl;
        app.setActiveLayout("mainLayout");
    });

    QMenuBar *bar = new QMenuBar();
    bar->addAction(statsAction);
    bar->addAction(mainMenuAction);

    QPushButton *button = new QPushButton();
    button->setText("Exit Application...");
    QObject::connect(button,&QPushButton::clicked,[&]() {
        cout << "You clicked the exit button..." << endl;
        QApplication::quit();
    });

    app.addWidget("exitButton",button);
    app.addWidgetToLayout("exitButton","mainLayout");

    app.addWidget("menuBar",bar);
    app.addWidgetToLayout("menuBar","mainLayout");
    app.addWidgetToLayout("menuBar","statsLayout");

    app.setActiveLayout("statsLayout");
    return app.runApp();
}