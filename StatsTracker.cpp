//
// Created by thierry on 4/27/26.
//

#include "StatsTracker.h"

StatsTracker::StatsTracker(){

    wallHit = new int[4];
}

void StatsTracker::logWallHit(int wallNumber){
    wallHit[wallNumber]++;
}

int StatsTracker::getTotalNumberOfHit(){
    return wallHit[0] + wallHit[1] + wallHit[2] + wallHit[3];
}

int StatsTracker::getNumberOfHitForWall(int wallNumber){
    return wallHit[wallNumber];
}

void StatsTracker::logCornerHit(int cornerNumber){
    cornerHit[cornerNumber]++;
}
int StatsTracker::getNumberOfHitForCorner(int cornerNumber){
    return cornerHit[cornerNumber];
}