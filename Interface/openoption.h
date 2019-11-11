#ifndef OPENOPTION_H
#define OPENOPTION_H

#include <QDialog>

namespace Ui {
class openoption;
}

class openoption : public QDialog
{
    Q_OBJECT

public:
    explicit openoption(QWidget *parent = nullptr);
    ~openoption();

private:
    Ui::openoption *ui;
};

#endif // OPENOPTION_H
