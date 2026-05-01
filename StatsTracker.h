//
// Created by lxs on 4/27/26.
//

#ifndef DVD_SIMULATOR_STATSTRACKER_H
#define DVD_SIMULATOR_STATSTRACKER_H



class StatsTracker {
    private:
        int _wallHit[4] = {};
        int _cornerHit[4] = {};
    public:
        StatsTracker();
        void logWallHit(int wallNumber);

        int getTotalNumberOfHit() const;
        int getNumberOfHitForWall(int wallNumber) const;

        void logCornerHit(int cornerNumber);
        int getNumberOfHitForCorner(int cornerNumber) const;
        int getTotalNumberOfCornerHits() const;


};



#endif //DVD_SIMULATOR_STATSTRACKER_H
