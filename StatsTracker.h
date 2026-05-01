//
// Created by lxs on 4/27/26.
//

#ifndef DVD_SIMULATOR_STATSTRACKER_H
#define DVD_SIMULATOR_STATSTRACKER_H
#include <string>
#include <vector>

class StatsTracker {
private:
    std::vector<int> _wallHit;
    std::vector<int> _cornerHit;
    std::vector<std::vector<int>> _wallHitOverTime;
    std::vector<std::vector<int>> _cornerHitOverTime;
    std::vector<std::vector<int>> _positionOverTime;
    double _dt;
    int _totalTimeSteps;
public:
    StatsTracker(double dt, std::vector<int> startPos);

    double getDt() const;

    void logWallHit(int wallNumber);
    int getTotalNumberOfWallHits() const;
    int getNumberOfHitForWall(int wallNumber) const;

    void logCornerHit(int cornerNumber);
    int getNumberOfHitForCorner(int cornerNumber) const;
    int getTotalNumberOfCornerHits() const;

    void update(std::vector<int> pos);

    void saveCSV(const std::string& fileName);
};



#endif //DVD_SIMULATOR_STATSTRACKER_H
