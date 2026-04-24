//
// Created by lxs on 4/24/26.
//

#ifndef DVD_SIMULATOR_CANVAS_H
#define DVD_SIMULATOR_CANVAS_H

#include <qlabel.h>

class Canvas : public QLabel {
private:
    int _width;
    int _height;
    bool _isFullscreen;
    QPixmap _canvas;

public:
    Canvas(int width, int height, bool isFullscreen);

    void showCanvas();
    void hideCanvas();

    void update();

    void fill(int r, int g, int b);
    void fill(int r, int g, int b, int a);

    void drawText(std::string text, int r, int g, int b, int x, int y);
};



#endif //DVD_SIMULATOR_CANVAS_H
