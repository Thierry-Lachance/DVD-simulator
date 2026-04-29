//
// Created by lxs on 4/29/26.
//

#ifndef DVD_SIMULATOR_CLIMBERDVD_H
#define DVD_SIMULATOR_CLIMBERDVD_H
#include "DVD.h"


class ClimberDVD : public DVD {
public:
    ClimberDVD(DVD_PARAMS dvd_params, StatsTracker *stats) : DVD(dvd_params,stats) {};
    void collisionEffect(std::vector<bool> wallHits) override;
};



#endif //DVD_SIMULATOR_CLIMBERDVD_H
