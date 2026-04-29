//
// Created by lxs on 4/29/26.
//

#include "ClimberDVD.h"

void ClimberDVD::collisionEffect(std::vector<bool> wallHits) {
    if (wallHits[0]) {
        _y -= floor(_screen_height/5);
    }
}
