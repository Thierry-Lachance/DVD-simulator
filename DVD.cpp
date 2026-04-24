//
// Created by lxs on 4/24/26.
//

#include "DVD.h"


DVD::DVD(QPixmap image, double yVel, double xVel, int x, int y) {
    _image = image;
    _width = image.width();
    _height = image.height();
    _xVel = xVel;
    _yVel = yVel;
    _x = x;
    _y = y;
}

QPixmap DVD::getImage() const {
    return _image;
}
