#include <iostream>
#include <QtWidgets>
#include <QtCharts>

#include "App.h"

using namespace std;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    App app("DVD-SIMULATOR",600,400,&a);

    app.addLayout("mainLayout");
    app.addLayout("statsLayout");

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
    bar->addAction(mainMenuAction);
    bar->addAction(statsAction);

    app.setLayoutMenuBar("mainLayout",bar);
    app.setLayoutMenuBar("statsLayout",bar);

    /*
     *QPushButton *button = new QPushButton();
     *   button->setText("Exit Application...");
     *   QObject::connect(button,&QPushButton::clicked,[&]() {
     *       cout << "You clicked the exit button..." << endl;
     *       QApplication::quit();
     *   });
     */

    QPushButton *runButton = new QPushButton();
       runButton->setText("Run Simulation");
       QObject::connect(runButton,&QPushButton::clicked,[&]() {
           cout << "You clicked the run simulation button..." << endl;
            app.hide();
       });

    QDoubleSpinBox *xVelSpinBox = new QDoubleSpinBox;
    QLabel *xVelLabel = new QLabel;
    QDoubleSpinBox *yVelSpinBox = new QDoubleSpinBox;
    QLabel *yVelLabel = new QLabel;

    xVelLabel->setText("Logo X Axis Velocity:");
    yVelLabel->setText("Logo Y Axis Velocity:");

    xVelSpinBox->setValue(1.0);
    yVelSpinBox->setValue(1.0);

    xVelSpinBox->setSingleStep(0.1);
    yVelSpinBox->setSingleStep(0.1);

    QSpinBox *xPosSpinBox = new QSpinBox;
    QLabel *xPosLabel = new QLabel;
    QSpinBox *yPosSpinBox = new QSpinBox;
    QLabel *yPosLabel = new QLabel;

    xPosLabel->setText("Logo X Start Position:");
    yPosLabel->setText("Logo Y Start Position:");

    xPosSpinBox->setValue(1);
    yPosSpinBox->setValue(1);

    xPosSpinBox->setSingleStep(10);
    yPosSpinBox->setSingleStep(10);

    QCheckBox *saveCheckbox = new QCheckBox;
    saveCheckbox->setChecked(true);
    saveCheckbox->setText("Save stats to .csv ?");

    app.addWidget("xVelLabel",xVelLabel);
    app.addWidget("xVelSpinBox",xVelSpinBox);
    app.addWidget("yVelLabel",yVelLabel);
    app.addWidget("yVelSpinBox",yVelSpinBox);
    app.addWidget("xPosLabel",xPosLabel);
    app.addWidget("xPosSpinBox",xPosSpinBox);
    app.addWidget("yPosLabel",yPosLabel);
    app.addWidget("yPosSpinBox",yPosSpinBox);
    app.addWidget("saveCheckbox",saveCheckbox);
    app.addWidget("runSimulationButton",runButton);

    app.addWidgetToLayout("xPosLabel","mainLayout");
    app.addWidgetToLayout("xPosSpinBox","mainLayout");
    app.addWidgetToLayout("yPosLabel","mainLayout");
    app.addWidgetToLayout("yPosSpinBox","mainLayout");
    app.addWidgetToLayout("xVelLabel","mainLayout");
    app.addWidgetToLayout("xVelSpinBox","mainLayout");
    app.addWidgetToLayout("yVelLabel","mainLayout");
    app.addWidgetToLayout("yVelSpinBox","mainLayout");
    app.addWidgetToLayout("saveCheckbox","mainLayout");
    app.addWidgetToLayout("runSimulationButton","mainLayout");

    app.setActiveLayout("statsLayout");
    return app.runApp();
}