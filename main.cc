#include "./ApplicationLogic/MainController.h"
#include "./Interface/MainWindow.h"
#include "./Persistence/PersistenceManager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PersistenceManager persistenceManager;
    MainWindow mainWindow;
    mainWindow.setWindowTitle("SCAPES");
    mainWindow.show();
    MainController mainController(&persistenceManager, &mainWindow);
    mainWindow.setMainController(&mainController);
    return app.exec();
}
