/********************************************************************************
** Form generated from reading UI file 'savewindow.ui'
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *InputLabel;
    QTextEdit *textEdit;
    QPushButton *EnterValue;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 133);
        InputLabel = new QLabel(Dialog);
        InputLabel->setObjectName(QString::fromUtf8("InputLabel"));
        InputLabel->setGeometry(QRect(20, 10, 311, 17));
        textEdit = new QTextEdit(Dialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(13, 40, 371, 31));
        EnterValue = new QPushButton(Dialog);
        EnterValue->setObjectName(QString::fromUtf8("EnterValue"));
        EnterValue->setGeometry(QRect(280, 100, 101, 25));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        InputLabel->setText(QCoreApplication::translate("Dialog", "Please Enter a Number for input", nullptr));
        EnterValue->setText(QCoreApplication::translate("Dialog", "Submit Value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEWINDOW_H
