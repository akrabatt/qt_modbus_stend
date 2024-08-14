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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stend_main_window
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QComboBox *com_box;
    QPushButton *button_start_send_message;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *stend_main_window)
    {
        if (stend_main_window->objectName().isEmpty())
            stend_main_window->setObjectName(QString::fromUtf8("stend_main_window"));
        stend_main_window->resize(457, 412);
        centralwidget = new QWidget(stend_main_window);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 10, 41, 21));
        com_box = new QComboBox(centralwidget);
        com_box->addItem(QString());
        com_box->addItem(QString());
        com_box->addItem(QString());
        com_box->addItem(QString());
        com_box->addItem(QString());
        com_box->setObjectName(QString::fromUtf8("com_box"));
        com_box->setGeometry(QRect(50, 60, 71, 22));
        button_start_send_message = new QPushButton(centralwidget);
        button_start_send_message->setObjectName(QString::fromUtf8("button_start_send_message"));
        button_start_send_message->setGeometry(QRect(170, 150, 80, 18));
        stend_main_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(stend_main_window);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 457, 17));
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
        label->setText(QCoreApplication::translate("stend_main_window", "\320\277\321\200\320\270\320\262\320\265\321\202", nullptr));
        com_box->setItemText(0, QCoreApplication::translate("stend_main_window", "COM1", nullptr));
        com_box->setItemText(1, QCoreApplication::translate("stend_main_window", "COM2", nullptr));
        com_box->setItemText(2, QCoreApplication::translate("stend_main_window", "COM3", nullptr));
        com_box->setItemText(3, QCoreApplication::translate("stend_main_window", "OCM4", nullptr));
        com_box->setItemText(4, QCoreApplication::translate("stend_main_window", "COM5", nullptr));

        button_start_send_message->setText(QCoreApplication::translate("stend_main_window", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stend_main_window: public Ui_stend_main_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEND_MAIN_WINDOW_H
