/********************************************************************************
** Form generated from reading UI file 'moduls_result.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODULS_RESULT_H
#define UI_MODULS_RESULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>

QT_BEGIN_NAMESPACE

class Ui_moduls_result
{
public:

    void setupUi(QTabWidget *moduls_result)
    {
        if (moduls_result->objectName().isEmpty())
            moduls_result->setObjectName(QString::fromUtf8("moduls_result"));
        moduls_result->resize(400, 300);

        retranslateUi(moduls_result);

        QMetaObject::connectSlotsByName(moduls_result);
    } // setupUi

    void retranslateUi(QTabWidget *moduls_result)
    {
        moduls_result->setWindowTitle(QCoreApplication::translate("moduls_result", "TabWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class moduls_result: public Ui_moduls_result {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODULS_RESULT_H
