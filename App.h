//
// Created by lxs on 4/22/26.
//

#ifndef DVD_SIMULATOR_APP_H
#define DVD_SIMULATOR_APP_H
#include <qboxlayout.h>
#include <QApplication>
#include <qstackedwidget.h>
#include <string>
#include <QtWidgets>
#include <QtCharts>


class App {
private:
    QApplication *_app;
    QWidget *_mainWindow;
    QHBoxLayout *_layout;
    std::string _appName;
    int _appWidth;
    int _appHeight;
    std::string _activeLayout;
    std::map<std::string, std::vector<std::string>> _layoutsWidgets;
    std::map<std::string, QMenuBar*> _layoutsBars;
    std::map<std::string, QWidget*> _widgets;
    int _exitStatus;
public:
    App(std::string appName, int appWidth, int appHeight, QApplication *app);

    QWidget *widget(std::string widgetName);

    int getExitStatus();
    QWidget *getMainWindow();

    void addLayout(std::string layoutName);
    void addWidget(std::string widgetName, QWidget *widget);
    void addWidgetToLayout(std::string widgetName, std::string layoutName);

    void setLayoutMenuBar(std::string layoutName, QMenuBar *bar);
    void setActiveLayout(std::string layoutName);
    void setAppName(std::string appName);

    void clearLayout();

    void exit() const;

    int runApp();
};



#endif //DVD_SIMULATOR_APP_H
