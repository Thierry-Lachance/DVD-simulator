//
// Created by lxs on 4/24/26.
//

#ifndef DVD_SIMULATOR_CUSTOMWINDOW_H
#define DVD_SIMULATOR_CUSTOMWINDOW_H
#include <QWidget>


class CustomWindow: public QWidget {
private:
    std::set<int> _keysPressed;
public:
    CustomWindow();
    std::set<int> getKeysPressed();
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};



#endif //DVD_SIMULATOR_CUSTOMWINDOW_H
