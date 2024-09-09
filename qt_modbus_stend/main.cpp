#include "stend_main_window.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>
#include <vector>
#include "libmodbus/modbus.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "qt_modbus_stend_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    stend_main_window w;
    w.show();
    return a.exec();
}
