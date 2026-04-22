//
// Created by lxs on 4/22/26.
//

#include "App.h"

#include <QWidget>

using namespace std;
App::App(std::string appName, int appWidth, int appHeight, QApplication *app, QWidget *mainWindow) {
    _appName = appName;
    _appWidth = appWidth;
    _appHeight = appHeight;
    _app = app;
    _mainWindow = mainWindow;
    _mainWindow->setWindowTitle(_appName.data());
    _mainWindow->resize(_appWidth, _appHeight);
}

QWidget * App::getMainWindow() {
    return _mainWindow;
}

QWidget * App::getWidget(std::string widgetName) {
    return _widgets->at(widgetName);
}

int App::getExitStatus() {
    return _exitStatus;
}

void App::setAppName(std::string appName) {
    _appName = appName;
}

void App::addLayout(std::string layoutName, QLayout *layout) {
    _layouts->at(layoutName) = layout;
}

void App::setActiveLayout(std::string layoutName) {
    _activeLayout = layoutName;
    _mainWindow->setLayout(_layouts->at(layoutName));
}

void App::addWidget(std::string widgetName, QWidget *widget) {
    _widgets->at(widgetName) = widget;
}

void App::addWidgetToLayout(std::string widgetName, std::string layoutName) {
    _layouts->at(layoutName)->addWidget(_widgets->at(widgetName));
}

void App::exit() const {
    _app->exit();
}

int App::runApp() {
    return _app->exec();
}
