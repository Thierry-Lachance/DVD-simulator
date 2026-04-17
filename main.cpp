#include <iostream>
#include <QtWidgets/QtWidgets>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.resize(1,1);
    window.show();
    window.setWindowTitle(QApplication::translate("toplevel", "Top-level widget"));
    return app.exec();
}