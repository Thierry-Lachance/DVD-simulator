//
// Created by lxs on 4/27/26.
//

#ifndef DVD_SIMULATOR_STATSTRACKER_H
#define DVD_SIMULATOR_STATSTRACKER_H



class StatsTracker {
    private:
        int[] wallHit;
        int[] cornerHit;
    public:
        StatsTracker();
        void logWallHit(int wallNumber);
        int getTotalNumberOfHit();
        int getNumberOfHitForWall(int wallNumber);

        void logCornerHit(int cornerNumber);
        int getNumberOfHitForCorner(int cornerNumber);


};



#endif //DVD_SIMULATOR_STATSTRACKER_H
