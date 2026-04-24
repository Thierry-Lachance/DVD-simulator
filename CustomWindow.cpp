//
// Created by lxs on 4/24/26.
//

#include "CustomWindow.h"

#include <qevent.h>

CustomWindow::CustomWindow() {
}

std::set<int> CustomWindow::getKeysPressed() {
    return _keysPressed;
}

void CustomWindow::keyPressEvent(QKeyEvent *event) {
    QWidget::keyPressEvent(event);
    _keysPressed.insert(event->key());
}

void CustomWindow::keyReleaseEvent(QKeyEvent *event) {
    QWidget::keyReleaseEvent(event);
    _keysPressed.erase(event->key());
}
