//
// Created by lxs on 4/27/26.
//

#ifndef DVD_SIMULATOR_STANDARD_DVD_H
#define DVD_SIMULATOR_STANDARD_DVD_H
#include "DVD.h"

class Standard_DVD : public DVD {
public:
    Standard_DVD(DVD_PARAMS dvd_params, StatsTracker *stats) : DVD(dvd_params,stats) {};
    void collisionEffect(std::vector<bool> wallHits) override;
};



#endif //DVD_SIMULATOR_STANDARD_DVD_H
