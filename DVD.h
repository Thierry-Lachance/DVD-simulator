//
// Created by lxs on 4/24/26.
//

#ifndef DVD_SIMULATOR_DVD_H
#define DVD_SIMULATOR_DVD_H
#include <qpixmap.h>

#include "StatsTracker.h"

struct DVD_PARAMS {
    std::string simulationName;
    int screen_width;
    int screen_height;
    QPixmap image;
    int x;
    int y;
    double xVel;
    double yVel;
    /* DVDTypes :
     * 0 - Standard
     * 1 - Side Scroller DVD
     * 2 - Climber DVD
    */
    int DVDType = 0;
    bool saveCSV;
};

class DVD {
protected:
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
    DVD(DVD_PARAMS dvd_params, StatsTracker *stats);

    QPixmap getImage() const;

    int getX() const;
    int getY() const;

    int getWidth() const;

    void updatePos(double dt);
    void updateVel(std::vector<bool> wallHits);

    std::vector<bool> checkCollisions(int horizontalPadding, int verticalPadding);
    virtual void collisionEffect(std::vector<bool> wallHits) = 0;
};


#endif //DVD_SIMULATOR_DVD_H
