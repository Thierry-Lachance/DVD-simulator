//
// Created by lxs on 4/24/26.
//

#ifndef DVD_SIMULATOR_DVD_H
#define DVD_SIMULATOR_DVD_H
#include <qpixmap.h>


class DVD {
private:
    QPixmap _image;
    int _width;
    int _height;
    double _yVel;
    double _xVel;
    int _x;
    int _y;
public:
    DVD(QPixmap image, double yVel, double xVel, int x, int y);
    QPixmap getImage() const;
};


#endif //DVD_SIMULATOR_DVD_H
