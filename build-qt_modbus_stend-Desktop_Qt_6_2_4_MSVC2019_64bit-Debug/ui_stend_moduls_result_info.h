/********************************************************************************
** Form generated from reading UI file 'stend_moduls_result_info.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STEND_MODULS_RESULT_INFO_H
#define UI_STEND_MODULS_RESULT_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stend_moduls_result_info
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;

    void setupUi(QWidget *stend_moduls_result_info)
    {
        if (stend_moduls_result_info->objectName().isEmpty())
            stend_moduls_result_info->setObjectName(QString::fromUtf8("stend_moduls_result_info"));
        stend_moduls_result_info->resize(757, 637);
        tabWidget = new QTabWidget(stend_moduls_result_info);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 731, 601));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(stend_moduls_result_info);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(stend_moduls_result_info);
    } // setupUi

    void retranslateUi(QWidget *stend_moduls_result_info)
    {
        stend_moduls_result_info->setWindowTitle(QCoreApplication::translate("stend_moduls_result_info", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("stend_moduls_result_info", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("stend_moduls_result_info", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stend_moduls_result_info: public Ui_stend_moduls_result_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEND_MODULS_RESULT_INFO_H
