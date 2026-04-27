//
// Created by lxs on 4/24/26.
//

#ifndef DVD_SIMULATOR_DVD_H
#define DVD_SIMULATOR_DVD_H
#include <qpixmap.h>

#include "StatsTracker.h"


class DVD {
private:
    QPixmap _image;
    int _width;
    int _height;
    int _screen_width;
    int _screen_height;
    double _yVel;
    double _xVel;
    int _x;
    int _y;
    StatsTracker *_stats;
public:
    DVD(QPixmap image, double xVel, double yVel, int x, int y, int screen_width, int screen_height, StatsTracker *stats);
    QPixmap getImage() const;
    virtual void cornerHit() = 0;
};


#endif //DVD_SIMULATOR_DVD_H
