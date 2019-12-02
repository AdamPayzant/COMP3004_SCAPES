/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *menuButtonNewOption;
    QAction *menuButtonOpenOption;
    QAction *menuButtonSaveOption;
    QAction *menuButtonCompileOption;
    QAction *menuButtonRunOption;
    QAction *menuButtonFuncDescOption;
    QAction *menuButtonAboutOption;
    QAction *menuButtonCloseOption;
    QWidget *centralWidget;
    QTextEdit *sourceTextWindow;
    QTextEdit *feedbackWindow;
    QMenuBar *menuBar;
    QMenu *menuButtonFile;
    QMenu *menuProgram;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(871, 682);
        menuButtonNewOption = new QAction(MainWindow);
        menuButtonNewOption->setObjectName(QString::fromUtf8("menuButtonNewOption"));
        menuButtonOpenOption = new QAction(MainWindow);
        menuButtonOpenOption->setObjectName(QString::fromUtf8("menuButtonOpenOption"));
        menuButtonSaveOption = new QAction(MainWindow);
        menuButtonSaveOption->setObjectName(QString::fromUtf8("menuButtonSaveOption"));
        menuButtonCompileOption = new QAction(MainWindow);
        menuButtonCompileOption->setObjectName(QString::fromUtf8("menuButtonCompileOption"));
        menuButtonRunOption = new QAction(MainWindow);
        menuButtonRunOption->setObjectName(QString::fromUtf8("menuButtonRunOption"));
        menuButtonFuncDescOption = new QAction(MainWindow);
        menuButtonFuncDescOption->setObjectName(QString::fromUtf8("menuButtonFuncDescOption"));
        menuButtonAboutOption = new QAction(MainWindow);
        menuButtonAboutOption->setObjectName(QString::fromUtf8("menuButtonAboutOption"));
        menuButtonCloseOption = new QAction(MainWindow);
        menuButtonCloseOption->setObjectName(QString::fromUtf8("menuButtonCloseOption"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sourceTextWindow = new QTextEdit(centralWidget);
        sourceTextWindow->setObjectName(QString::fromUtf8("sourceTextWindow"));
        sourceTextWindow->setGeometry(QRect(10, 10, 851, 401));
        feedbackWindow = new QTextEdit(centralWidget);
        feedbackWindow->setObjectName(QString::fromUtf8("feedbackWindow"));
        feedbackWindow->setGeometry(QRect(10, 420, 851, 211));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 871, 22));
        menuButtonFile = new QMenu(menuBar);
        menuButtonFile->setObjectName(QString::fromUtf8("menuButtonFile"));
        menuProgram = new QMenu(menuBar);
        menuProgram->setObjectName(QString::fromUtf8("menuProgram"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuButtonFile->menuAction());
        menuBar->addAction(menuProgram->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuButtonFile->addAction(menuButtonNewOption);
        menuButtonFile->addAction(menuButtonOpenOption);
        menuButtonFile->addAction(menuButtonSaveOption);
        menuButtonFile->addAction(menuButtonCloseOption);
        menuProgram->addAction(menuButtonCompileOption);
        menuProgram->addAction(menuButtonRunOption);
        menuHelp->addAction(menuButtonFuncDescOption);
        menuHelp->addAction(menuButtonAboutOption);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        menuButtonNewOption->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        menuButtonOpenOption->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        menuButtonSaveOption->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        menuButtonCompileOption->setText(QCoreApplication::translate("MainWindow", "Compile", nullptr));
        menuButtonRunOption->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        menuButtonFuncDescOption->setText(QCoreApplication::translate("MainWindow", "Functionality Description", nullptr));
        menuButtonAboutOption->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        menuButtonCloseOption->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        menuButtonFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuProgram->setTitle(QCoreApplication::translate("MainWindow", "Program", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
