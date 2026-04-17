#ifndef DVDSIMULATOR_H
#define DVDSIMULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class DVDSimulator;
}
QT_END_NAMESPACE

class DVDSimulator : public QMainWindow
{
    Q_OBJECT

public:
    explicit DVDSimulator(QWidget *parent = nullptr);
    ~DVDSimulator() override;

private:
    Ui::DVDSimulator *ui;
};
#endif // DVDSIMULATOR_H
