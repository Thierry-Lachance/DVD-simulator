//
// Created by lxs on 4/24/26.
//

#include "Canvas.h"

Canvas::Canvas(int width, int height, bool isFullscreen) {
    _width = width;
    _height = height;
    _canvas = QPixmap(width,height);
    _canvas.fill();
    this->setPixmap(_canvas);
    _isFullscreen = isFullscreen;
    if (isFullscreen) {
        this->setScaledContents(true);
        this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    }
}

void Canvas::showCanvas() {
    if (_isFullscreen) {
        this->showFullScreen();
    } else {
        this->show();
    }
}

void Canvas::hideCanvas() {
    this->hide();
}

void Canvas::fill(int r, int g, int b) {
    _canvas = this->pixmap();
    _canvas.fill(QColor(r,g,b));
    this->setPixmap(_canvas);
}

void Canvas::fill(int r, int g, int b, int a) {
    _canvas = this->pixmap();
    _canvas.fill(QColor(r,g,b,a));
    this->setPixmap(_canvas);
}
