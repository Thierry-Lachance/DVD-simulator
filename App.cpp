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
    _layout = new QVBoxLayout();
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

void App::show() {
    _mainWindow->show();
}

void App::hide() {
    _mainWindow->hide();
}

int App::getExitStatus() {
    return _exitStatus;
}

void App::setAppName(string appName) {
    _appName = appName;
}

void App::addLayout(string layoutName) {
    vector<string> widgetVector;
    _layoutsWidgets[layoutName] = widgetVector;
    _layoutsSize[layoutName] = {_appWidth,_appHeight};
}

void App::addLayout(std::string layoutName, vector<int> layoutSize) {
    vector<string> vector;
    _layoutsWidgets[layoutName] = vector;
    _layoutsSize[layoutName] = layoutSize;
}

void App::setActiveLayout(string layoutName) {
    clearLayout();
    _mainWindow->resize(_layoutsSize[layoutName][0],_layoutsSize[layoutName][1]);
    _mainWindow->setMinimumSize(_layoutsSize[layoutName][0],_layoutsSize[layoutName][1]);
    _mainWindow->setMaximumSize(_layoutsSize[layoutName][0],_layoutsSize[layoutName][1]);
    _layout->setMenuBar(_layoutsBars[layoutName]);
    for (const std::string& widgetName: _layoutsWidgets[layoutName]) {
        _layout->addWidget(_widgets[widgetName]);
    }
    _activeLayout = layoutName;
    _layout->update();
}

void App::addWidget(std::string widgetName, QWidget *widget) {
    if (widget) {
        _widgets.insert({widgetName,widget});
    }
}

void App::addWidgetToLayout(string widgetName, string layoutName) {
    _layoutsWidgets[layoutName].push_back(widgetName);
}

void App::setLayoutMenuBar(std::string layoutName, QMenuBar *bar) {
    _layoutsBars[layoutName] = bar;
}

void App::clearLayout() {
    if (_activeLayout != "") {
        for (std::string widgetName: _layoutsWidgets[_activeLayout]) {
            if (_widgets[widgetName]) {
                _layout->removeWidget(_widgets[widgetName]);
                _widgets[widgetName]->setParent(nullptr);
            }
        }
        _layout->setMenuBar(nullptr);
    }
}

void App::exit() const {
    _app->exit();
}

int App::runApp() {
    _mainWindow->show();
    return QCoreApplication::exec();
}
