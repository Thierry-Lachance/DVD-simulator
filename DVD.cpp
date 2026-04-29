//
// Created by lxs on 4/24/26.
//

#include "DVD.h"

using namespace std;

DVD::DVD(DVD_PARAMS dvd_params, StatsTracker *stats) {
    _image = dvd_params.image;
    _width = _image.width();
    _height = _image.height();
    _xVel = dvd_params.xVel;
    _yVel = dvd_params.yVel;
    _x = dvd_params.x;
    _y = dvd_params.y;
    _stats = stats;
    _screen_height = dvd_params.screen_height;
    _screen_width = dvd_params.screen_width;
}

QPixmap DVD::getImage() const {
    return _image;
}

int DVD::getX() const {
    return _x;
}

int DVD::getY() const {
    return _y;
}

int DVD::getWidth() const {
    return _width;
}

void DVD::updatePos(double dt) {
    _x += floor(_xVel * dt * 1/dt);
    _y += floor(_yVel * dt * 1/dt);
}

void DVD::updateVel(std::vector<bool> wallHits) {
    if (wallHits[0]) {
        _xVel *= -1;
        if (_x <= 0) {
            _x = 0;
        } else {
            _x = _screen_width - _width;
        }
    }
    if (wallHits[1]) {
        _yVel *= -1;
        if (_y <= 0) {
            _y = 0;
        } else {
            _y = _screen_height - _height;
        }
    }
}

vector<bool> DVD::checkCollisions(int horizontalPadding, int verticalPadding) {
    vector<bool> wallHits = {false,false};
    if (_x >= _screen_width-_image.width()+horizontalPadding || _x <= 0-horizontalPadding) {
        wallHits[0] = true;
        // TODO : STATS TRACKER ADD WALL HIT
    }
    if (_y >= _screen_height-_image.height()+verticalPadding || _y <= 0-verticalPadding) {
        wallHits[1] = true;
        // TODO : STATS TRACKER ADD WALL HIT
    }
    return wallHits;
}
