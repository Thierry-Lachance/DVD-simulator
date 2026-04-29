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
    /* Wall Indexes :
     *  0 - Top Wall
     *  1 - Right Wall
     *  2 - Bottom Wall
     *  3 - Left Wall
     *
     * Corner Indexes :
     *  0 - Top Left
     *  1 - Top Right
     *  2 - Bottom Right
     *  3 - Bottom Left
     */
    vector<bool> wallHits = {false,false};
    vector<int> sides = {0,0};
    if (_x >= _screen_width-_image.width()+horizontalPadding) {
        wallHits[0] = true;
        _stats->logWallHit(1);
        sides[0] = 1;
    } else if (_x <= 0-horizontalPadding) {
        wallHits[0] = true;
        _stats->logWallHit(3);
        sides[0] = -1;
    }
    if (_y >= _screen_height-_image.height()+verticalPadding) {
        wallHits[1] = true;
        _stats->logWallHit(0);
        sides[1] = 1;
    } else if (_y <= 0-verticalPadding) {
        wallHits[1] = true;
        _stats->logWallHit(2);
        sides[1] = -1;
    }
    if (wallHits[0] && wallHits[1]) {
        if (sides[0] == 1 && sides[1] == 1) {
            _stats->logCornerHit(2);
        } else if (sides[0] == -1 && sides[1] == 1) {
            _stats->logCornerHit(3);
        } else if (sides[0] == 1 && sides[1] == -1) {
            _stats->logCornerHit(1);
        } else if (sides[0] == -1 && sides[1] == -1) {
            _stats->logCornerHit(0);
        }
    }
    return wallHits;
}
