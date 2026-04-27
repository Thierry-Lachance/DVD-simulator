#include <iostream>
#include <QtWidgets>
#include <QtCharts>
#include <thread>
#include <chrono>
#include <string>
#include <unistd.h>

#include "App.h"
#include "Canvas.h"
#include "CustomWindow.h"
#include "DVD.h"
#include "Standard_DVD.h"

using namespace std;

struct DVD_PARAMS {
    string simulationName;
    int screen_width;
    int screen_height;
    QPixmap image;
    vector<int> pos;
    vector<double> vel;
    /* DVDTypes :
     * 0 - Standard
     * 1 - Side Scroller DVD
     * 2 - Climber DVD
    */
    int DVDType;
    bool saveCSV;
};

void keyHandlerFunction(App *app, Canvas *canvas) {
    std::set<int> keys;
    cout << "Key handler thread is running" << endl;
    while (true) {
        if (app->getActiveLayout() == "simulation") {
            app->getMainWindow()->grabKeyboard();
            keys = app->getPressedKeys();
            if (keys.count(Qt::Key_Escape)) {
                canvas->hideCanvas();
                app->setActiveLayout("mainLayout");
                cout << "Ending simulation ... " << endl;
            }
        }
    }
}

void simHandlerFunction(App *app, Canvas *canvas, DVD_PARAMS *dvd_params) {
    while (true) {
        if (app->getActiveLayout() == "simulation") {
            auto t1 = chrono::steady_clock::now();
            auto t2 = chrono::steady_clock::now();
            double dt;
            StatsTracker stats;
            if (dvd_params->DVDType == 0) {
                Standard_DVD dvd(dvd_params->image, dvd_params->vel[0], dvd_params->vel[1], dvd_params->pos[0], dvd_params->pos[1],
                        dvd_params->screen_width, dvd_params->screen_height, &stats);
            }
            while (app->getActiveLayout() == "simulation") {
                dt = std::chrono::duration<double>(chrono::duration_cast<chrono::milliseconds>(t2 - t1)).count();
                t1 = chrono::steady_clock::now();
                canvas->clear(false);
                canvas->update();
                t2 = chrono::steady_clock::now();
            }
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    int screen_width = QApplication::primaryScreen()->size().width();
    int screen_height = QApplication::primaryScreen()->size().height();

    DVD_PARAMS dvd_params;
    //dvd_params.image = QPixmap("../dvd-image.png");
    dvd_params.screen_height = screen_height;
    dvd_params.screen_width = screen_width;

    App app("DVD-SIMULATOR",600,400,&a);

    app.addLayout("mainLayout");
    app.addLayout("statsLayout");
    app.addLayout("simulation", {screen_width,screen_height});
    app.setLayoutFullscreen("statsLayout",true);
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

    // TODO: ADDD SIMULATION NAME AND DVD TYPE

    QPushButton *runButton = new QPushButton();
    runButton->setText("Run Simulation");
    QObject::connect(runButton,&QPushButton::clicked,[&]() {
        cout << "You clicked the run simulation button..." << endl;
        app.setActiveLayout("simulation");
        canvas->showCanvas();
        dvd_params.pos[0] = xPosSpinBox->value();
        dvd_params.pos[1] = yPosSpinBox->value();
        dvd_params.vel[0] = xVelSpinBox->value();
        dvd_params.vel[1] = yVelSpinBox->value();
        dvd_params.saveCSV = saveCheckbox->isChecked();
        // TODO: ADDD SIMULATION NAME AND DVD TYPE
    });

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
    thread simThread([&]{ simHandlerFunction(&app, canvas, &dvd_params); });
    app.runApp();
    keyThread.detach();
    simThread.detach();
    return app.getExitStatus();
}