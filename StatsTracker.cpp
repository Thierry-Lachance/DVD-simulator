//
// Created by thierry on 4/27/26.
//

#include "StatsTracker.h"

#include <iostream>
#include <fstream>
#include <qfiledialog.h>

using namespace std;

StatsTracker::StatsTracker(double dt, vector<int> startPos){
    _dt = dt;
    _totalTimeSteps = 0;
    _wallHit = {0,0,0,0};
    _wallHitOverTime = {{0,0,0,0}};
    _cornerHit = {0,0,0,0};
    _cornerHitOverTime = {{0,0,0,0}};
    _positionOverTime = {startPos};
}

double StatsTracker::getDt() const {
    return _dt;
}

void StatsTracker::logWallHit(int wallNumber){
    _wallHit[wallNumber]++;
}

int StatsTracker::getTotalNumberOfWallHits() const {
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

int StatsTracker::getTotalNumberOfCornerHits() const {
    return _cornerHit[0] + _cornerHit[1] + _cornerHit[2] + _cornerHit[3];
}

void StatsTracker::update(std::vector<int> pos) {
    _totalTimeSteps++;
    _positionOverTime.push_back(pos);
    _wallHitOverTime.push_back(_wallHit);
    _cornerHitOverTime.push_back(_cornerHit);
}

void StatsTracker::saveCSV(const std::string& fileName) {
    ofstream output("../"+fileName+".csv");
    if (output.is_open()) {
        output << _dt << ";" << _totalTimeSteps << "\n";
        output << getTotalNumberOfWallHits() << ";" << getTotalNumberOfCornerHits() << "\n";
        output << _wallHit[0] << ";" << _wallHit[1] << ";" << _wallHit[2] << ";" << _wallHit[3] << "\n";
        output << _cornerHit[0] << ";" << _cornerHit[1] << ";" << _cornerHit[2] << ";" << _cornerHit[3] << "\n";
        for (const auto& vec: _wallHitOverTime) {
            output << ";";
            for (const auto elem: vec) {
                output << elem << " ";
            }
        }
        output << "\n";
        for (const auto& vec: _cornerHitOverTime) {
            output << ";";
            for (const auto elem: vec) {
                output << elem << " ";
            }
        }
        output << "\n";
        for (const auto& vec: _positionOverTime) {
            output << ";";
            for (const auto elem: vec) {
                output << elem << " ";
            }
        }
        output << "\n";
    } else {
        cout << "An error happened while saving stats..." << endl;
    }
}
