//
// Created by lxs on 4/24/26.
//

#include "DVD.h"


DVD::DVD(QPixmap image, double yVel, double xVel, int x, int y, int screen_width, int screen_height, StatsTracker *stats) {
    _image = image;
    _width = image.width();
    _height = image.height();
    _xVel = xVel;
    _yVel = yVel;
    _x = x;
    _y = y;
    _stats = stats;
    _screen_height = screen_height;
    _screen_width = screen_width;
}

QPixmap DVD::getImage() const {
    return _image;
}
