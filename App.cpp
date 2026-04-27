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

App::App(string appName, int appWidth, int appHeight, QApplication *app) {
    _appName = appName;
    _appWidth = appWidth;
    _appHeight = appHeight;
    _app = app;
    _layout = new QVBoxLayout();
    _mainWindow = new CustomWindow();
    _mainWindow->setLayout(_layout);
    _mainWindow->setWindowTitle(appName.c_str());
    _mainWindow->resize(appWidth, appHeight);
}

CustomWindow *App::getMainWindow() {
    return _mainWindow;
}

std::string App::getActiveLayout() {
    return _activeLayout;
}

std::set<int> App::getPressedKeys() {
    return _mainWindow->getKeysPressed();
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

void App::setLayoutFullscreen(std::string layoutName, bool isFullscreen) {
    _layoutsFullscreen[layoutName] = isFullscreen;
}

void App::addLayout(string layoutName) {
    vector<string> widgetVector;
    _layoutsWidgets[layoutName] = widgetVector;
    _layoutsSize[layoutName] = {_appWidth,_appHeight};
    _layoutsFullscreen[layoutName] = false;
}

void App::addLayout(std::string layoutName, vector<int> layoutSize) {
    vector<string> vector;
    _layoutsWidgets[layoutName] = vector;
    _layoutsSize[layoutName] = layoutSize;
    _layoutsFullscreen[layoutName] = false;
}

void App::setActiveLayout(string layoutName) {
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


