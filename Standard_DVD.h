//
// Created by lxs on 4/27/26.
//

#ifndef DVD_SIMULATOR_STANDARD_DVD_H
#define DVD_SIMULATOR_STANDARD_DVD_H
#include "DVD.h"


class Standard_DVD : public DVD {
public:
    Standard_DVD(QPixmap image, double xVel, double yVel, int x, int y, int screen_width, int screen_height, StatsTracker *stats) : DVD(image,xVel,yVel,x,y,screen_width,screen_height,stats) {};
    void cornerHit() override;
};



#endif //DVD_SIMULATOR_STANDARD_DVD_H
