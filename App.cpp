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
    _mainWindow = new QStackedWidget;
    _mainWindow->setWindowTitle(appName.c_str());
    _mainWindow->resize(appWidth, appHeight);

}

QStackedWidget *App::getMainWindow() {
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

void App::addLayout(string layoutName, QHBoxLayout *layout) {
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    _mainWindow->addWidget(widget);
    _layoutsStorage[layoutName] = layout;
    vector<string> vector;
    _layoutsWidgets[layoutName] = vector;
    _layouts.insert({layoutName,_mainWindow->count()});
}

void App::setActiveLayout(string layoutName) {
    _activeLayout = _layouts.at(layoutName);
    for (const std::string& widgetName: _layoutsWidgets[layoutName]) {
        _layoutsStorage[layoutName]->addWidget(_widgets[widgetName]);
    }
    _mainWindow->setCurrentWidget(_layoutsStorage[layoutName]->parentWidget());
}

void App::addWidget(std::string widgetName, QWidget *widget) {
    _widgets.insert({widgetName,widget});
}

void App::addWidgetToLayout(string widgetName, string layoutName) {
    _layoutsWidgets[layoutName].push_back(widgetName);
}

void App::exit() const {
    _app->exit();
}

int App::runApp() {
    _mainWindow->show();
    return QCoreApplication::exec();
}
