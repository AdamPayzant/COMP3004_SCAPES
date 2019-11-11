#ifndef MAINWINDOW_H
#include <QMainWindow>
#include <QtGui>

#include "savewindow.h"
#include "openoption.h"
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_compile_clicked(bool checked);

    void on_compile_clicked();

    void on_pushButton_clicked();

    void on_Openbutton_clicked();

    void on_save_clicked();

    void on_compilebutton_clicked();

private:
    Ui::MainWindow *ui;
    string  Filename;
};

#endif // MAINWINDOW_H
