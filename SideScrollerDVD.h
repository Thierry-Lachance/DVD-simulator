//
// Created by lxs on 4/29/26.
//

#ifndef DVD_SIMULATOR_SIDESCROLLERDVD_H
#define DVD_SIMULATOR_SIDESCROLLERDVD_H
#include "DVD.h"


class SideScrollerDVD : public DVD {

public:
    SideScrollerDVD(DVD_PARAMS dvd_params, StatsTracker *stats) : DVD(dvd_params,stats) {};
    void collisionEffect(std::vector<bool> wallHits) override;
};



#endif //DVD_SIMULATOR_SIDESCROLLERDVD_H
