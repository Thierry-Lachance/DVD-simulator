//
// Created by lxs on 4/22/26.
//

#ifndef DVD_SIMULATOR_APP_H
#define DVD_SIMULATOR_APP_H
#include <qboxlayout.h>
#include <QApplication>
#include <qstackedwidget.h>
#include <string>


class App {
private:
    QApplication *_app;
    QStackedWidget *_mainWindow;
    std::string _appName;
    int _appWidth;
    int _appHeight;
    int _activeLayout;
    std::map<std::string, int> _layouts;
    std::map<std::string, QWidget*> _widgets;
    int _exitStatus;
public:
    App(std::string appName, int appWidth, int appHeight, QApplication *app);

    QStackedWidget *getMainWindow();
    QWidget *widget(std::string widgetName);

    int getExitStatus();

    void setAppName(std::string appName);
    void addLayout(std::string layoutName, QHBoxLayout *layout);
    void setActiveLayout(std::string layoutName);
    void addWidget(std::string widgetName, QWidget *widget);
    void addWidgetToLayout(std::string widgetName, std::string layoutName);

    void exit() const;

    int runApp();
};



#endif //DVD_SIMULATOR_APP_H
