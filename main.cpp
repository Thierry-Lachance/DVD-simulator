#include <iostream>
#include <QtWidgets>
#include <QtCharts>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>

#include "App.h"
#include "Canvas.h"
#include "CustomWindow.h"
#include "DVD.h"
#include "Standard_DVD.h"

using namespace std;

void keyHandlerFunction(App *app, Canvas *canvas) {
    std::set<int> keys;
    cout << "Key handler thread is running" << endl;
    while (true) {
        if (app->getActiveLayout() == "simulation") {
            keys = app->getPressedKeys();
            if (keys.count(Qt::Key_Escape)) {
                canvas->hideCanvas();
                app->setActiveLayout("mainLayout");
                cout << "Ending simulation ... " << endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void simHandlerFunction(App *app, Canvas *canvas, DVD_PARAMS *dvd_params) {
    while (true) {
        if (app->getActiveLayout() == "simulation") {
            auto t1 = chrono::steady_clock::now();
            auto t2 = chrono::steady_clock::now();
            double dt;
            StatsTracker stats;

            DVD *dvd;
            Standard_DVD Std_DVD = Standard_DVD(*dvd_params, &stats);

            if (dvd_params->DVDType == 0) {
                dvd = &Std_DVD;
            } else {
                dvd = &Std_DVD;
            }

            while (app->getActiveLayout() == "simulation") {
                t2 = chrono::steady_clock::now();
                dt = std::chrono::duration<double>(chrono::duration_cast<chrono::milliseconds>(t2 - t1)).count();
                dvd->updatePos(dt);
                dvd->updateVel(dvd->checkCollisions());
                t1 = chrono::steady_clock::now();
                canvas->clear();
                canvas->drawImage(dvd->getImage(),dvd->getX(),dvd->getY());
                canvas->drawText("FRAME/MS: " + to_string(1/dt), 255, 0, 0,0,15);QMetaObject::invokeMethod(canvas, "renderFrame",
                    Qt::QueuedConnection,
                    Q_ARG(QPixmap, *canvas->getCanvas()));
            }
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    int screen_width = QApplication::primaryScreen()->size().width();
    int screen_height = QApplication::primaryScreen()->size().height();

    vector<QObject*> objects;

    DVD_PARAMS dvd_params;
    dvd_params.image = QPixmap("../dvd.png");
    dvd_params.screen_height = screen_height;
    dvd_params.screen_width = screen_width;

    App app("DVD-SIMULATOR",600,500,&a);

    QAction *statsAction = new QAction();
    statsAction->setText("Stats");
    QObject::connect(statsAction, &QAction::triggered,[&]() {
        cout << "Switiching to stats page" << endl;
        app.setActiveLayout("statsLayout");
    });

    objects.push_back(statsAction);

    QAction *mainMenuAction = new QAction();
    mainMenuAction->setText("Main Menu");
    QObject::connect(mainMenuAction, &QAction::triggered,[&]() {
        cout << "Switiching to main page" << endl;
        app.setActiveLayout("mainLayout");
    });

    objects.push_back(mainMenuAction);

    QMenuBar *bar = new QMenuBar();
    bar->addAction(mainMenuAction);
    bar->addAction(statsAction);

    objects.push_back(bar);

    Canvas *canvas = new Canvas(screen_width,screen_height, true);
    canvas->fill(0,0,0);

    objects.push_back(canvas);

    QDoubleSpinBox *xVelSpinBox = new QDoubleSpinBox;
    QLabel *xVelLabel = new QLabel;
    QDoubleSpinBox *yVelSpinBox = new QDoubleSpinBox;
    QLabel *yVelLabel = new QLabel;

    objects.push_back(xVelSpinBox);
    objects.push_back(yVelSpinBox);
    objects.push_back(xVelLabel);
    objects.push_back(yVelLabel);

    xVelLabel->setText("Logo X Axis Velocity:");
    yVelLabel->setText("Logo Y Axis Velocity:");

    xVelSpinBox->setValue(1.0);
    yVelSpinBox->setValue(1.0);

    xVelSpinBox->setSingleStep(1);
    yVelSpinBox->setSingleStep(1);

    QSpinBox *xPosSpinBox = new QSpinBox;
    QLabel *xPosLabel = new QLabel;
    QSpinBox *yPosSpinBox = new QSpinBox;
    QLabel *yPosLabel = new QLabel;

    objects.push_back(xPosSpinBox);
    objects.push_back(yPosSpinBox);
    objects.push_back(xPosLabel);
    objects.push_back(yPosLabel);

    xPosLabel->setText("Logo X Start Position:");
    yPosLabel->setText("Logo Y Start Position:");

    xPosSpinBox->setMaximum(screen_width-dvd_params.image.width());
    yPosSpinBox->setMaximum(screen_height-dvd_params.image.height());

    xPosSpinBox->setMinimum(0);
    yPosSpinBox->setMinimum(0);

    xPosSpinBox->setValue(1);
    yPosSpinBox->setValue(1);

    xPosSpinBox->setSingleStep(10);
    yPosSpinBox->setSingleStep(10);

    QCheckBox *saveCheckbox = new QCheckBox;
    saveCheckbox->setChecked(true);
    saveCheckbox->setText("Save stats to .csv ?");

    objects.push_back(saveCheckbox);

    QLabel *simNameLabel = new QLabel;
    simNameLabel->setText("Simulation Name:");

    objects.push_back(simNameLabel);

    QLineEdit *simNameEdit = new QLineEdit;
    simNameEdit->setPlaceholderText("SIMULATION-NAME");

    objects.push_back(simNameEdit);

    QLabel *dvdTypeLabel = new QLabel;
    dvdTypeLabel->setText("Set DVD type:");

    objects.push_back(dvdTypeLabel);

    QComboBox *dvdTypeComboBox = new QComboBox;
    dvdTypeComboBox->setFixedHeight(25);

    objects.push_back(dvdTypeComboBox);

    dvdTypeComboBox->addItem("0 - Standard DVD",0);
    dvdTypeComboBox->addItem("1 - Side Scroller DVD",1);
    dvdTypeComboBox->addItem("2 - Climber DVD",2);

    QLabel *padding = new QLabel;
    padding->setText(" ");
    padding->setFixedHeight(5);

    objects.push_back(padding);

    QPushButton *runButton = new QPushButton();
    runButton->setText("Run Simulation");

    objects.push_back(runButton);

    QPushButton *saveButton = new QPushButton();
    saveButton->setText("Save Simulation Config");

    objects.push_back(saveButton);

    QPushButton *loadButton = new QPushButton();
    loadButton->setText("Load Simulation Config");

    objects.push_back(loadButton);

    QObject::connect(saveButton,&QPushButton::clicked,[&]() {
        ofstream output("../"+simNameEdit->text().toStdString()+".csv");
        if (output.is_open()) {
            output << saveCheckbox->isChecked() << ";" << dvdTypeComboBox->currentData().toInt() << "\n";
            output << xPosSpinBox->value() << ";" << yPosSpinBox->value() << "\n";
            output << xVelSpinBox->value() << ";" << yVelSpinBox->value() << "\n";
            output.close();
        } else {
            cout << "An error happened while saving the simulation config..." << endl;
        }
    });

    QObject::connect(loadButton,&QPushButton::clicked,[&]() {
        string file = QFileDialog::getOpenFileName(app.getMainWindow(), "Load File", QApplication::applicationDirPath(),"CSV Files (*.csv)").toStdString();
        ifstream input(file);
        if (input.is_open()) {
            simNameEdit->setText(QString(file.substr(file.find_last_of('/')+1).c_str()).replace(".csv",""));
            string line;
            int lidx = 0;
            while (getline(input,line)) {
                if (lidx == 0) {
                    saveCheckbox->setChecked(atoi(line.substr(0,line.find(';')).c_str()));
                    line.replace(0,line.find(';')+1,"");
                    dvdTypeComboBox->setCurrentIndex(atoi(line.c_str()));
                } else if (lidx == 1) {
                    xPosSpinBox->setValue(atoi(line.substr(0,line.find(';')).c_str()));
                    line.replace(0,line.find(';')+1,"");
                    yPosSpinBox->setValue(atoi(line.c_str()));
                } else if (lidx == 2) {
                    xVelSpinBox->setValue(atof(line.substr(0,line.find(';')).c_str()));
                    line.replace(0,line.find(';')+1,"");
                    yVelSpinBox->setValue(atof(line.c_str()));
                }
                lidx++;
            }
            input.close();
        } else {
            cout << "An error happened while loading the simulation config..." << endl;
        }
    });

    QObject::connect(runButton,&QPushButton::clicked,[&]() {
        dvd_params.x = xPosSpinBox->value();
        dvd_params.y = yPosSpinBox->value();
        dvd_params.xVel = xVelSpinBox->value();
        dvd_params.yVel = yVelSpinBox->value();
        dvd_params.saveCSV = saveCheckbox->isChecked();
        dvd_params.simulationName = simNameEdit->text().toStdString();
        dvd_params.DVDType = dvdTypeComboBox->currentIndex();
        cout << "You clicked the run simulation button..." << endl;
        app.setActiveLayout("simulation");
        canvas->showCanvas();
        app.getMainWindow()->grabKeyboard();
    });

    app.addLayout("mainLayout");
    app.addLayout("statsLayout");
    app.addLayout("simulation", {screen_width,screen_height});
    app.setLayoutFullscreen("statsLayout",true);
    app.setLayoutFullscreen("simulation",true);

    app.setLayoutMenuBar("mainLayout",bar);
    app.setLayoutMenuBar("statsLayout",bar);

    app.addWidget("padding",padding);
    app.addWidget("dvdTypeLabel",dvdTypeLabel);
    app.addWidget("dvdTypeComboBox",dvdTypeComboBox);
    app.addWidget("simNameLabel",simNameLabel);
    app.addWidget("simNameEdit",simNameEdit);
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
    app.addWidget("saveConfigButton",saveButton);
    app.addWidget("loadConfigButton",loadButton);

    app.addWidgetToLayout("dvdTypeLabel","mainLayout");
    app.addWidgetToLayout("dvdTypeComboBox","mainLayout");
    app.addWidgetToLayout("simNameLabel","mainLayout");
    app.addWidgetToLayout("simNameEdit","mainLayout");
    app.addWidgetToLayout("xPosLabel","mainLayout");
    app.addWidgetToLayout("xPosSpinBox","mainLayout");
    app.addWidgetToLayout("yPosLabel","mainLayout");
    app.addWidgetToLayout("yPosSpinBox","mainLayout");
    app.addWidgetToLayout("xVelLabel","mainLayout");
    app.addWidgetToLayout("xVelSpinBox","mainLayout");
    app.addWidgetToLayout("yVelLabel","mainLayout");
    app.addWidgetToLayout("yVelSpinBox","mainLayout");
    app.addWidgetToLayout("saveCheckbox","mainLayout");
    app.addWidgetToLayout("saveConfigButton","mainLayout");
    app.addWidgetToLayout("loadConfigButton","mainLayout");
    app.addWidgetToLayout("runSimulationButton","mainLayout");

    app.setActiveLayout("mainLayout");

    thread keyThread([&]{ keyHandlerFunction(&app, canvas); });
    thread simThread([&]{ simHandlerFunction(&app, canvas, &dvd_params); });
    app.runApp();
    keyThread.detach();
    simThread.detach();
    return app.getExitStatus();
}