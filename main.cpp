#include <iostream>
#include <QtWidgets>
#include <QtCharts>
#include <thread>
#include <chrono>
#include <string>
#include "App.h"
#include "Canvas.h"
#include "CustomWindow.h"

using namespace std;

void keyHandlerFunction(App *app, Canvas *canvas) {
    std::set<int> keys;
    cout << "Key handler thread is running" << endl;
    while (true) {
        keys = app->getPressedKeys();
        if (app->getActiveLayout() == "simulation") {
            app->getMainWindow()->grabKeyboard();
            if (keys.count(Qt::Key_Escape)) {
                canvas->hideCanvas();
                app->setActiveLayout("mainLayout");
                cout << "Ending simulation ... " << endl;
            }
        }
    }
}

void simHandlerFunction(App *app, Canvas *canvas) {
    while (true) {
        if (app->getActiveLayout() == "simulation") {
            auto current = chrono::high_resolution_clock::now();
            auto previous = chrono::high_resolution_clock::now();
            chrono::duration<double> dt;
            while (app->getActiveLayout() == "simulation") {
                current = chrono::high_resolution_clock::now();
                canvas->fill(255,255,255);
                canvas->drawText("Test :" + to_string(dt.count()),255,255,255,0,20);
                canvas->update();
                previous = current;
                dt = current - previous;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    int screen_width = a.primaryScreen()->size().width();
    int screen_height = a.primaryScreen()->size().height();

    App app("DVD-SIMULATOR",600,400,&a);

    app.addLayout("mainLayout");
    app.addLayout("statsLayout");
    app.addLayout("simulation", {screen_width,screen_height});
    app.setLayoutFullscreen("simulation",true);

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

    Canvas *canvas = new Canvas(screen_width,screen_height, true);
    canvas->fill(0,0,0);

    QPushButton *runButton = new QPushButton();
    runButton->setText("Run Simulation");
    QObject::connect(runButton,&QPushButton::clicked,[&]() {
        cout << "You clicked the run simulation button..." << endl;
        app.setActiveLayout("simulation");
        canvas->showCanvas();
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

    app.setActiveLayout("mainLayout");

    thread keyThread([&]{ keyHandlerFunction(&app, canvas); });
    thread simThread([&]{ simHandlerFunction(&app, canvas); });
    app.runApp();
    keyThread.detach();
    simThread.detach();
    return app.getExitStatus();
}