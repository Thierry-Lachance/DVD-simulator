
#include <iostream>
#include <QtWidgets>

using namespace std;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QHBoxLayout *layout = new QHBoxLayout();

    QWidget window;
    QMenuBar *bar = new QMenuBar();
    bar->addMenu("This does absolutely nothing ...");
    layout->addWidget(bar);


    QPushButton *button = new QPushButton(&window);
    button->setText("Exit Application...");
    QObject::connect(button,&QPushButton::clicked,[&]() {
        cout << "You clicked the exit button..." << endl;
        QApplication::quit();
    });

    layout->addWidget(button);
    window.setLayout(layout);
    window.resize(300,200);
    window.setWindowTitle("Fenetre test");

    window.show();

    return QApplication::exec();
}