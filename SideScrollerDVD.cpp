//
// Created by lxs on 4/29/26.
//

#include "SideScrollerDVD.h"

#include <iostream>

using namespace std;
void SideScrollerDVD::collisionEffect(vector<bool> wallHits) {
    if (wallHits[0]) {
        if (_x <= 0 - _width) {
            _x = _screen_width;
        } else {
            _x = 0 - _width;
        }
        _xVel *= -1;
    }
}
