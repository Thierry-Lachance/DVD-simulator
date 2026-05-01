//
// Created by lxs on 4/22/26.
//

#include "App.h"

#include <iostream>
#include <qmainwindow.h>
#include <qstackedwidget.h>
#include <QWidget>

#include "CustomWindow.h"

using namespace std;

App::App(const string &appName, int appWidth, int appHeight, QApplication *app) {
    _appName = appName;
    _appWidth = appWidth;
    _appHeight = appHeight;
    _app = app;
    _layout = new QGridLayout();
    _mainWindow = new CustomWindow();
    _mainWindow->setLayout(_layout);
    _mainWindow->setWindowTitle(appName.c_str());
    _mainWindow->resize(appWidth, appHeight);
}

QWidget * App::widget(const string &widgetName) const {
    return _widgets.at(widgetName);
}

void App::show() const {
    _mainWindow->show();
}

void App::hide() const {
    _mainWindow->hide();
}

int App::getExitStatus() const {
    return _exitStatus;
}

CustomWindow *App::getMainWindow() const {
    return _mainWindow;
}

std::string App::getActiveLayout() {
    return _activeLayout;
}

std::set<int> App::getPressedKeys() const {
    return _mainWindow->getKeysPressed();
}

void App::addLayout(const string &layoutName) {
    vector<string> widgetVector;
    _layoutsWidgets[layoutName] = widgetVector;
    _layoutsSize[layoutName] = {_appWidth,_appHeight};
    _layoutsFullscreen[layoutName] = false;
}

void App::addLayout(const std::string &layoutName, vector<int> layoutSize) {
    vector<string> vector;
    _layoutsWidgets[layoutName] = vector;
    _layoutsSize[layoutName] = layoutSize;
    _layoutsFullscreen[layoutName] = false;
}

void App::addWidget(std::string widgetName, QWidget *widget) {
    if (widget) {
        _widgets.insert({widgetName,widget});
    }
}

auto App::addWidgetToLayout(const string &widgetName, const string &layoutName) -> void {
    _layoutsWidgets[layoutName].push_back(widgetName);
}

void App::setLayoutMenuBar(const string &layoutName, QMenuBar *bar) {
    _layoutsBars[layoutName] = bar;
}

auto App::setActiveLayout(const string &layoutName) -> void {
    clearLayout();
    if (!_layoutsFullscreen[layoutName]) {
        _mainWindow->resize(_layoutsSize[layoutName][0],_layoutsSize[layoutName][1]);
        _mainWindow->setMinimumSize(_layoutsSize[layoutName][0],_layoutsSize[layoutName][1]);
        _mainWindow->setMaximumSize(_layoutsSize[layoutName][0],_layoutsSize[layoutName][1]);
        _mainWindow->show();
    } else {
        _mainWindow->showFullScreen();
    }
    _layout->setMenuBar(_layoutsBars[layoutName]);
    for (const std::string& widgetName: _layoutsWidgets[layoutName]) {
        _layout->addWidget(_widgets[widgetName]);
    }
    _activeLayout = layoutName;
    _layout->update();
}

void App::setAppName(const string &appName) {
    _appName = appName;
}

void App::setLayoutFullscreen(const std::string &layoutName, bool isFullscreen) {
    _layoutsFullscreen[layoutName] = isFullscreen;
}

void App::clearLayout() {
    if (_activeLayout != "") {
        for (std::string widgetName: _layoutsWidgets[_activeLayout]) {
            if (_widgets[widgetName]) {
                _layout->removeWidget(_widgets[widgetName]);
                _widgets[widgetName]->setParent(nullptr);
            }
        }
        if (_layoutsBars[_activeLayout]) {
            _layoutsBars[_activeLayout]->setParent(nullptr);
        }
        _mainWindow->showNormal();
        _layout->setMenuBar(nullptr);
    }
}

void App::exit() const {
    _app->exit();
}

void App::runApp() {
    _mainWindow->show();
    _exitStatus = QCoreApplication::exec();
}


