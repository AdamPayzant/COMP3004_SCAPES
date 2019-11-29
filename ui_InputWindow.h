/********************************************************************************
** Form generated from reading UI file 'InputWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTWINDOW_H
#define UI_INPUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_InputWindow
{
public:
    QLabel *enterValueDirectiveText;
    QTextEdit *userInputTextEdit;
    QPushButton *confirmationButton;

    void setupUi(QDialog *InputWindow)
    {
        if (InputWindow->objectName().isEmpty())
            InputWindow->setObjectName(QString::fromUtf8("InputWindow"));
        InputWindow->resize(349, 99);
        enterValueDirectiveText = new QLabel(InputWindow);
        enterValueDirectiveText->setObjectName(QString::fromUtf8("enterValueDirectiveText"));
        enterValueDirectiveText->setGeometry(QRect(10, 10, 331, 17));
        userInputTextEdit = new QTextEdit(InputWindow);
        userInputTextEdit->setObjectName(QString::fromUtf8("userInputTextEdit"));
        userInputTextEdit->setGeometry(QRect(10, 30, 331, 31));
        confirmationButton = new QPushButton(InputWindow);
        confirmationButton->setObjectName(QString::fromUtf8("confirmationButton"));
        confirmationButton->setGeometry(QRect(260, 70, 83, 25));

        retranslateUi(InputWindow);

        QMetaObject::connectSlotsByName(InputWindow);
    } // setupUi

    void retranslateUi(QDialog *InputWindow)
    {
        InputWindow->setWindowTitle(QCoreApplication::translate("InputWindow", "Dialog", nullptr));
        enterValueDirectiveText->setText(QCoreApplication::translate("InputWindow", "Enter a value and press the OK button to confirm", nullptr));
        confirmationButton->setText(QCoreApplication::translate("InputWindow", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputWindow: public Ui_InputWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTWINDOW_H
