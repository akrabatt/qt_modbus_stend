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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stend_main_window
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *just_lable_1;
    QHBoxLayout *horizontalLayout;
    QLabel *just_lable_2;
    QSpacerItem *horizontalSpacer;
    QLineEdit *line_in_com_num;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *button_test_connection;
    QLabel *answer_connection_lable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *stend_main_window)
    {
        if (stend_main_window->objectName().isEmpty())
            stend_main_window->setObjectName(QString::fromUtf8("stend_main_window"));
        stend_main_window->resize(1280, 794);
        centralwidget = new QWidget(stend_main_window);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 281, 61));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        just_lable_1 = new QLabel(verticalLayoutWidget);
        just_lable_1->setObjectName(QString::fromUtf8("just_lable_1"));

        verticalLayout->addWidget(just_lable_1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        just_lable_2 = new QLabel(verticalLayoutWidget);
        just_lable_2->setObjectName(QString::fromUtf8("just_lable_2"));

        horizontalLayout->addWidget(just_lable_2);

        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        line_in_com_num = new QLineEdit(verticalLayoutWidget);
        line_in_com_num->setObjectName(QString::fromUtf8("line_in_com_num"));

        horizontalLayout->addWidget(line_in_com_num);

        horizontalSpacer_2 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        button_test_connection = new QPushButton(verticalLayoutWidget);
        button_test_connection->setObjectName(QString::fromUtf8("button_test_connection"));

        horizontalLayout->addWidget(button_test_connection);


        verticalLayout->addLayout(horizontalLayout);

        answer_connection_lable = new QLabel(centralwidget);
        answer_connection_lable->setObjectName(QString::fromUtf8("answer_connection_lable"));
        answer_connection_lable->setGeometry(QRect(300, 30, 101, 31));
        stend_main_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(stend_main_window);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 21));
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
        just_lable_1->setText(QCoreApplication::translate("stend_main_window", "\320\242\320\265\321\201\321\202 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217 (\321\201\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216 115200)", nullptr));
        just_lable_2->setText(QCoreApplication::translate("stend_main_window", "COM \320\277\320\276\321\200\321\202:", nullptr));
        line_in_com_num->setPlaceholderText(QCoreApplication::translate("stend_main_window", "COM1...", nullptr));
        button_test_connection->setText(QCoreApplication::translate("stend_main_window", "\321\202\320\265\321\201\321\202", nullptr));
        answer_connection_lable->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class stend_main_window: public Ui_stend_main_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEND_MAIN_WINDOW_H
