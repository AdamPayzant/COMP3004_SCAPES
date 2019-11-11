#ifndef SAVEWINDOW_H
#define SAVEWINDOW_H


#include <QDialog>

namespace Ui {
class savewindow;
}

class savewindow : public QDialog
{
    Q_OBJECT

public:
    explicit savewindow(QWidget *parent = nullptr);
    ~savewindow();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::savewindow *ui;
};

#endif // SAVEWINDOW_H
