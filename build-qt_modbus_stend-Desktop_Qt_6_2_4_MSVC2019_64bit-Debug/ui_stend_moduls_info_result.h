/********************************************************************************
** Form generated from reading UI file 'stend_moduls_info_result.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STEND_MODULS_INFO_RESULT_H
#define UI_STEND_MODULS_INFO_RESULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stend_moduls_info_result
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;

    void setupUi(QWidget *stend_moduls_info_result)
    {
        if (stend_moduls_info_result->objectName().isEmpty())
            stend_moduls_info_result->setObjectName(QString::fromUtf8("stend_moduls_info_result"));
        stend_moduls_info_result->resize(735, 566);
        tabWidget = new QTabWidget(stend_moduls_info_result);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 731, 561));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(stend_moduls_info_result);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(stend_moduls_info_result);
    } // setupUi

    void retranslateUi(QWidget *stend_moduls_info_result)
    {
        stend_moduls_info_result->setWindowTitle(QCoreApplication::translate("stend_moduls_info_result", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("stend_moduls_info_result", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("stend_moduls_info_result", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stend_moduls_info_result: public Ui_stend_moduls_info_result {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEND_MODULS_INFO_RESULT_H
