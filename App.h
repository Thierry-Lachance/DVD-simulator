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


class CustomWindow;

class App {
private:
    QApplication *_app;
    CustomWindow *_mainWindow;
    QGridLayout *_layout;
    std::string _appName;
    int _appWidth;
    int _appHeight;
    std::string _activeLayout;
    std::map<std::string, std::vector<std::string>> _layoutsWidgets;
    std::map<std::string, QMenuBar*> _layoutsBars;
    std::map<std::string, QWidget*> _widgets;
    std::map<std::string, std::vector<int>> _layoutsSize;
    std::map<std::string, bool> _layoutsFullscreen;
    int _exitStatus;
public:
    App(const std::string &appName, int appWidth, int appHeight, QApplication *app);

    QWidget *widget(const std::string &widgetName) const;

    void show() const;
    void hide() const;

    int getExitStatus() const;
    CustomWindow *getMainWindow() const;
    std::string getActiveLayout();
    std::set<int> getPressedKeys() const;

    void addLayout(const std::string &layoutName);
    void addLayout(const std::string &layoutName, std::vector<int> layoutSize);
    void addWidget(std::string widgetName, QWidget *widget);
    void addWidgetToLayout(const std::string &widgetName, const std::string &layoutName);

    void setLayoutMenuBar(const std::string &layoutName, QMenuBar *bar);
    void setActiveLayout(const std::string &layoutName);
    void setAppName(const std::string &appName);
    void setLayoutFullscreen(const std::string &layoutName, bool isFullscreen);

    void clearLayout();

    void exit() const;

    void runApp();
};

#endif //DVD_SIMULATOR_APP_H
