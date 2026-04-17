#include "dvdsimulator.h"
#include "ui_dvdsimulator.h"

DVDSimulator::DVDSimulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DVDSimulator)
{
    ui->setupUi(this);
}

DVDSimulator::~DVDSimulator()
{
    delete ui;
}
