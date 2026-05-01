//
// Created by thierry on 4/27/26.
//

#include "StatsTracker.h"

StatsTracker::StatsTracker(){
}

void StatsTracker::logWallHit(int wallNumber){
    _wallHit[wallNumber]++;
}

int StatsTracker::getTotalNumberOfHit() const {
    return _wallHit[0] + _wallHit[1] + _wallHit[2] + _wallHit[3];
}

int StatsTracker::getNumberOfHitForWall(int wallNumber) const {
    return _wallHit[wallNumber];
}

void StatsTracker::logCornerHit(int cornerNumber){
    _cornerHit[cornerNumber]++;
}

int StatsTracker::getNumberOfHitForCorner(int cornerNumber) const {
    return _cornerHit[cornerNumber];
}