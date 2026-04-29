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

void DVD::updatePos(double dt) {
    _x += (int)(_xVel * dt * 1000);
    _y += (int)(_yVel * dt * 1000);
}

void DVD::updateVel(std::vector<bool> wallHits) {
    if (wallHits[0]) {
        _xVel *= -1;
    }
    if (wallHits[1]) {
        _yVel *= -1;
    }
}

vector<bool> DVD::checkCollisions() {
    vector<bool> wallHits = {false,false};
    bool collision = false;
    if (_x >= _screen_width-_image.width() || _x <= 0) {
        wallHits[0] = true;
        collision = true;
        // TODO : STATS TRACKER ADD WALL HIT
    }
    if (_y >= _screen_height-_image.height() || _y <= 0) {
        wallHits[1] = true;
        collision = true;
        // TODO : STATS TRACKER ADD WALL HIT
    }
    if (collision) {
        collisionEffect();
    }
    return wallHits;
}
