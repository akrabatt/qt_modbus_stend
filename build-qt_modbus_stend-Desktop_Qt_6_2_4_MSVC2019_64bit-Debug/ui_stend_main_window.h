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
#include <QtWidgets/QCheckBox>
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
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBox_active_mops_1;
    QCheckBox *checkBox_active_mops_2;
    QCheckBox *checkBox_active_mops_3;
    QCheckBox *checkBox_active_mops_4;
    QCheckBox *checkBox_active_mops_5;
    QCheckBox *checkBox_active_mops_6;
    QCheckBox *checkBox_active_mops_7;
    QCheckBox *checkBox_active_mops_8;
    QCheckBox *checkBox_active_mops_9;
    QCheckBox *checkBox_active_mops_10;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox_active_mups_1;
    QCheckBox *checkBox_active_mups_2;
    QCheckBox *checkBox_active_mups_3;
    QCheckBox *checkBox_active_mups_4;
    QCheckBox *checkBox_active_mups_5;
    QCheckBox *checkBox_active_mups_6;
    QCheckBox *checkBox_active_mups_7;
    QCheckBox *checkBox_active_mups_8;
    QCheckBox *checkBox_active_mups_9;
    QCheckBox *checkBox_active_mups_10;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *stend_main_window)
    {
        if (stend_main_window->objectName().isEmpty())
            stend_main_window->setObjectName(QString::fromUtf8("stend_main_window"));
        stend_main_window->resize(590, 921);
        centralwidget = new QWidget(stend_main_window);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 341, 76));
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
        answer_connection_lable->setGeometry(QRect(360, 60, 121, 31));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 160, 291, 621));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, 0, 10, -1);
        checkBox_active_mops_1 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mops_1->setObjectName(QString::fromUtf8("checkBox_active_mops_1"));

        verticalLayout_3->addWidget(checkBox_active_mops_1);

        checkBox_active_mops_2 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mops_2->setObjectName(QString::fromUtf8("checkBox_active_mops_2"));

        verticalLayout_3->addWidget(checkBox_active_mops_2);

        checkBox_active_mops_3 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mops_3->setObjectName(QString::fromUtf8("checkBox_active_mops_3"));

        verticalLayout_3->addWidget(checkBox_active_mops_3);

        checkBox_active_mops_4 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mops_4->setObjectName(QString::fromUtf8("checkBox_active_mops_4"));

        verticalLayout_3->addWidget(checkBox_active_mops_4);

        checkBox_active_mops_5 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mops_5->setObjectName(QString::fromUtf8("checkBox_active_mops_5"));

        verticalLayout_3->addWidget(checkBox_active_mops_5);

        checkBox_active_mops_6 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mops_6->setObjectName(QString::fromUtf8("checkBox_active_mops_6"));

        verticalLayout_3->addWidget(checkBox_active_mops_6);

        checkBox_active_mops_7 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mops_7->setObjectName(QString::fromUtf8("checkBox_active_mops_7"));

        verticalLayout_3->addWidget(checkBox_active_mops_7);

        checkBox_active_mops_8 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mops_8->setObjectName(QString::fromUtf8("checkBox_active_mops_8"));

        verticalLayout_3->addWidget(checkBox_active_mops_8);

        checkBox_active_mops_9 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mops_9->setObjectName(QString::fromUtf8("checkBox_active_mops_9"));

        verticalLayout_3->addWidget(checkBox_active_mops_9);

        checkBox_active_mops_10 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mops_10->setObjectName(QString::fromUtf8("checkBox_active_mops_10"));

        verticalLayout_3->addWidget(checkBox_active_mops_10);


        horizontalLayout_2->addLayout(verticalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(10, -1, 10, -1);
        checkBox_active_mups_1 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mups_1->setObjectName(QString::fromUtf8("checkBox_active_mups_1"));

        verticalLayout_2->addWidget(checkBox_active_mups_1);

        checkBox_active_mups_2 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mups_2->setObjectName(QString::fromUtf8("checkBox_active_mups_2"));

        verticalLayout_2->addWidget(checkBox_active_mups_2);

        checkBox_active_mups_3 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mups_3->setObjectName(QString::fromUtf8("checkBox_active_mups_3"));

        verticalLayout_2->addWidget(checkBox_active_mups_3);

        checkBox_active_mups_4 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mups_4->setObjectName(QString::fromUtf8("checkBox_active_mups_4"));

        verticalLayout_2->addWidget(checkBox_active_mups_4);

        checkBox_active_mups_5 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mups_5->setObjectName(QString::fromUtf8("checkBox_active_mups_5"));

        verticalLayout_2->addWidget(checkBox_active_mups_5);

        checkBox_active_mups_6 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mups_6->setObjectName(QString::fromUtf8("checkBox_active_mups_6"));

        verticalLayout_2->addWidget(checkBox_active_mups_6);

        checkBox_active_mups_7 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mups_7->setObjectName(QString::fromUtf8("checkBox_active_mups_7"));

        verticalLayout_2->addWidget(checkBox_active_mups_7);

        checkBox_active_mups_8 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mups_8->setObjectName(QString::fromUtf8("checkBox_active_mups_8"));

        verticalLayout_2->addWidget(checkBox_active_mups_8);

        checkBox_active_mups_9 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mups_9->setObjectName(QString::fromUtf8("checkBox_active_mups_9"));

        verticalLayout_2->addWidget(checkBox_active_mups_9);

        checkBox_active_mups_10 = new QCheckBox(horizontalLayoutWidget);
        checkBox_active_mups_10->setObjectName(QString::fromUtf8("checkBox_active_mups_10"));

        verticalLayout_2->addWidget(checkBox_active_mups_10);


        horizontalLayout_2->addLayout(verticalLayout_2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 130, 211, 16));
        stend_main_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(stend_main_window);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 590, 25));
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
        just_lable_1->setText(QCoreApplication::translate("stend_main_window", "            \320\242\320\265\321\201\321\202 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217 (\321\201\320\272\320\276\321\200\320\276\321\201\321\202\321\214 115200)", nullptr));
        just_lable_2->setText(QCoreApplication::translate("stend_main_window", "COM \320\277\320\276\321\200\321\202:", nullptr));
        line_in_com_num->setPlaceholderText(QCoreApplication::translate("stend_main_window", "COM1...", nullptr));
        button_test_connection->setText(QCoreApplication::translate("stend_main_window", "\321\202\320\265\321\201\321\202 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217", nullptr));
        answer_connection_lable->setText(QString());
        checkBox_active_mops_1->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\236\320\237\320\241 1", nullptr));
        checkBox_active_mops_2->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\236\320\237\320\241 2", nullptr));
        checkBox_active_mops_3->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\236\320\237\320\241 3", nullptr));
        checkBox_active_mops_4->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\236\320\237\320\241 4", nullptr));
        checkBox_active_mops_5->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\236\320\237\320\241 5", nullptr));
        checkBox_active_mops_6->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\236\320\237\320\241 6", nullptr));
        checkBox_active_mops_7->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\236\320\237\320\241 7", nullptr));
        checkBox_active_mops_8->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\236\320\237\320\241 8", nullptr));
        checkBox_active_mops_9->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\236\320\237\320\241 9", nullptr));
        checkBox_active_mops_10->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\236\320\237\320\241 10", nullptr));
        checkBox_active_mups_1->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\243\320\237\320\241 1", nullptr));
        checkBox_active_mups_2->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\243\320\237\320\241 2", nullptr));
        checkBox_active_mups_3->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\243\320\237\320\241 3", nullptr));
        checkBox_active_mups_4->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\243\320\237\320\241 4", nullptr));
        checkBox_active_mups_5->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\243\320\237\320\241 5", nullptr));
        checkBox_active_mups_6->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\243\320\237\320\241 6", nullptr));
        checkBox_active_mups_7->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\243\320\237\320\241 7", nullptr));
        checkBox_active_mups_8->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\243\320\237\320\241 8", nullptr));
        checkBox_active_mups_9->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\243\320\237\320\241 9", nullptr));
        checkBox_active_mups_10->setText(QCoreApplication::translate("stend_main_window", "\320\234\320\243\320\237\320\241 10", nullptr));
        label->setText(QCoreApplication::translate("stend_main_window", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\270\321\201\320\277\321\213\321\202\321\203\320\265\320\274\321\213\320\265 \320\274\320\276\320\264\321\203\320\273\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stend_main_window: public Ui_stend_main_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEND_MAIN_WINDOW_H
