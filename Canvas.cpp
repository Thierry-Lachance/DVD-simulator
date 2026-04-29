//
// Created by lxs on 4/24/26.
//

#include "Canvas.h"

#include <qpaintengine.h>

Canvas::Canvas(int width, int height, bool isFullscreen) {
    _width = width;
    _height = height;
    _canvas = new QPixmap(width,height);
    _canvas->fill();
    this->setPixmap(*_canvas);
    _isFullscreen = isFullscreen;
    _clearColor = QColor(0,0,0);
    if (isFullscreen) {
        this->setScaledContents(true);
        this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    }
}

void Canvas::showCanvas() {
    if (_isFullscreen) {
        this->showFullScreen();
        this->grabKeyboard();
    } else {
        this->show();
    }
}

void Canvas::hideCanvas() {
    this->hide();
}


void Canvas::setClearColor(int r, int g, int b) {
    _clearColor = QColor(r,g,b);
}

void Canvas::update() {
    this->setPixmap(*_canvas);
}

void Canvas::clear(bool update) {
    _canvas = new QPixmap(_width,_height);
    _canvas->fill(_clearColor);
    if (update) {
        this->setPixmap(*_canvas);
    }
}

void Canvas::fill(int r, int g, int b) {
    _canvas->fill(QColor(r,g,b));
}

void Canvas::fill(int r, int g, int b, int a) {
    _canvas->fill(QColor(r,g,b,a));
}

void Canvas::drawImage(QPixmap image, int x, int y) {
    QPainter *painter = new QPainter(_canvas);
    painter->drawPixmap(x,y,image);
    painter->end();
}

void Canvas::drawText(std::string text, int r, int g, int b , int x , int y) {
    QPainter *painter = new QPainter(_canvas);
    painter->setBrush(QColor(r,g,b));
    painter->drawText(x,y,text.data());
    painter->end();
}
