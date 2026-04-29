//
// Created by thierry on 4/27/26.
//

#include "StatsTracker.h"

StatsTracker::StatsTracker(){
}

void StatsTracker::logWallHit(int wallNumber){
    wallHit[wallNumber]++;
}

int StatsTracker::getTotalNumberOfHit() const {
    return wallHit[0] + wallHit[1] + wallHit[2] + wallHit[3];
}

int StatsTracker::getNumberOfHitForWall(int wallNumber) const {
    return wallHit[wallNumber];
}

void StatsTracker::logCornerHit(int cornerNumber){
    cornerHit[cornerNumber]++;
}

int StatsTracker::getNumberOfHitForCorner(int cornerNumber) const {
    return cornerHit[cornerNumber];
}