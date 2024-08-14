/********************************************************************************
** Form generated from reading UI file 'stend_main_window.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STEND_MAIN_WINDOW_H
#define UI_STEND_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stend_main_window
{
public:
    QWidget *centralwidget;
    QPushButton *button_read;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *lab_reg_1;
    QLabel *lab_reg_2;
    QLabel *lab_reg_3;
    QLabel *lab_reg_4;
    QLabel *lab_reg_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *stend_main_window)
    {
        if (stend_main_window->objectName().isEmpty())
            stend_main_window->setObjectName(QString::fromUtf8("stend_main_window"));
        stend_main_window->resize(595, 467);
        centralwidget = new QWidget(stend_main_window);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        button_read = new QPushButton(centralwidget);
        button_read->setObjectName(QString::fromUtf8("button_read"));
        button_read->setGeometry(QRect(60, 170, 80, 18));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(150, 110, 101, 171));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lab_reg_1 = new QLabel(widget);
        lab_reg_1->setObjectName(QString::fromUtf8("lab_reg_1"));

        verticalLayout->addWidget(lab_reg_1);

        lab_reg_2 = new QLabel(widget);
        lab_reg_2->setObjectName(QString::fromUtf8("lab_reg_2"));

        verticalLayout->addWidget(lab_reg_2);

        lab_reg_3 = new QLabel(widget);
        lab_reg_3->setObjectName(QString::fromUtf8("lab_reg_3"));

        verticalLayout->addWidget(lab_reg_3);

        lab_reg_4 = new QLabel(widget);
        lab_reg_4->setObjectName(QString::fromUtf8("lab_reg_4"));

        verticalLayout->addWidget(lab_reg_4);

        lab_reg_5 = new QLabel(widget);
        lab_reg_5->setObjectName(QString::fromUtf8("lab_reg_5"));

        verticalLayout->addWidget(lab_reg_5);

        stend_main_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(stend_main_window);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 595, 21));
        stend_main_window->setMenuBar(menubar);
        statusbar = new QStatusBar(stend_main_window);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        stend_main_window->setStatusBar(statusbar);

        retranslateUi(stend_main_window);

        QMetaObject::connectSlotsByName(stend_main_window);
    } // setupUi

    void retranslateUi(QMainWindow *stend_main_window)
    {
        stend_main_window->setWindowTitle(QCoreApplication::translate("stend_main_window", "stend_main_window", nullptr));
        button_read->setText(QCoreApplication::translate("stend_main_window", "start read", nullptr));
        lab_reg_1->setText(QString());
        lab_reg_2->setText(QString());
        lab_reg_3->setText(QString());
        lab_reg_4->setText(QString());
        lab_reg_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class stend_main_window: public Ui_stend_main_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEND_MAIN_WINDOW_H
