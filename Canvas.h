//
// Created by lxs on 4/24/26.
//

#ifndef DVD_SIMULATOR_CANVAS_H
#define DVD_SIMULATOR_CANVAS_H

#include <qlabel.h>

class Canvas : public QLabel {
    Q_OBJECT
private:
    int _width;
    int _height;
    bool _isFullscreen;
    QPixmap *_canvas;
    QColor _clearColor;
public slots:
    void renderFrame(QPixmap frame);
public:
    Canvas(int width, int height, bool isFullscreen);

    QPixmap* getCanvas();

    void showCanvas();
    void hideCanvas();

    void setClearColor(int r, int g, int b);

    void clear();

    void fill(int r, int g, int b);
    void fill(int r, int g, int b, int a);

    void drawImage(QPixmap image, int x, int y);

    void drawText(std::string text, int r, int g, int b, int x, int y);
};



#endif //DVD_SIMULATOR_CANVAS_H
