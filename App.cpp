//
// Created by lxs on 4/22/26.
//

#include "App.h"

#include <qmainwindow.h>
#include <qstackedwidget.h>
#include <QWidget>

using namespace std;
App::App(string appName, int appWidth, int appHeight, QApplication *app) {
    _appName = appName;
    _appWidth = appWidth;
    _appHeight = appHeight;
    _app = app;
    _layout = new QHBoxLayout();
    _mainWindow = new QWidget();
    _mainWindow->setLayout(_layout);
    _mainWindow->setWindowTitle(appName.c_str());
    _mainWindow->resize(appWidth, appHeight);
}

QWidget *App::getMainWindow() {
    return _mainWindow;
}

QWidget * App::widget(string widgetName) {
    return _widgets.at(widgetName);
}

int App::getExitStatus() {
    return _exitStatus;
}

void App::setAppName(string appName) {
    _appName = appName;
}

void App::addLayout(string layoutName) {
    vector<string> vector;
    _layoutsWidgets[layoutName] = vector;
}

void App::setActiveLayout(string layoutName) {
    for (auto widget: _layout->children()) {
        widget->setParent(nullptr);
    }
    _layout->setMenuBar(_layoutsBars[layoutName]);
    for (const std::string& widgetName: _layoutsWidgets[layoutName]) {
        _layout->addWidget(_widgets[widgetName]);
    }
}

void App::addWidget(std::string widgetName, QWidget *widget) {
    _widgets.insert({widgetName,widget});
}

void App::addWidgetToLayout(string widgetName, string layoutName) {
    _layoutsWidgets[layoutName].push_back(widgetName);
}

void App::setLayoutMenuBar(std::string layoutName, QMenuBar *bar) {
    _layoutsBars[layoutName] = bar;
}

void App::exit() const {
    _app->exit();
}

int App::runApp() {
    _mainWindow->show();
    return QCoreApplication::exec();
}
