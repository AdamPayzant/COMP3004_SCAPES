/********************************************************************************
** Form generated from reading UI file 'SaveWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEWINDOW_H
#define UI_SAVEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_SaveWindow
{
public:
    QDialogButtonBox *confirmationBar;
    QTextEdit *filenameTextEdit;
    QLabel *saveWindowInst;

    void setupUi(QDialog *SaveWindow)
    {
        if (SaveWindow->objectName().isEmpty())
            SaveWindow->setObjectName(QString::fromUtf8("SaveWindow"));
        SaveWindow->resize(400, 139);
        confirmationBar = new QDialogButtonBox(SaveWindow);
        confirmationBar->setObjectName(QString::fromUtf8("confirmationBar"));
        confirmationBar->setGeometry(QRect(40, 100, 341, 32));
        confirmationBar->setOrientation(Qt::Horizontal);
        confirmationBar->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        filenameTextEdit = new QTextEdit(SaveWindow);
        filenameTextEdit->setObjectName(QString::fromUtf8("filenameTextEdit"));
        filenameTextEdit->setGeometry(QRect(10, 60, 371, 31));
        saveWindowInst = new QLabel(SaveWindow);
        saveWindowInst->setObjectName(QString::fromUtf8("saveWindowInst"));
        saveWindowInst->setGeometry(QRect(10, 10, 371, 41));
        saveWindowInst->setWordWrap(true);

        retranslateUi(SaveWindow);

        QMetaObject::connectSlotsByName(SaveWindow);
    } // setupUi

    void retranslateUi(QDialog *SaveWindow)
    {
        SaveWindow->setWindowTitle(QCoreApplication::translate("SaveWindow", "Dialog", nullptr));
        saveWindowInst->setText(QCoreApplication::translate("SaveWindow", "Please provide the filename you'd like to use to store the source code.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SaveWindow: public Ui_SaveWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEWINDOW_H
