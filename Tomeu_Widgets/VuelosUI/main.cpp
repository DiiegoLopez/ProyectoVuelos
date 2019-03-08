#include <QApplication>
#include <QFile>
#include "mainwindow.h"

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    QCommandLineParser parser;
       parser.setApplicationDescription("QtWebSockets example: echoclient");
       parser.addHelpOption();

       QCommandLineOption dbgOption(QStringList() << "d" << "debug",
               QCoreApplication::translate("main", "Debug output [default: off]."));
       parser.addOption(dbgOption);
       parser.process(a);
       bool debug = parser.isSet(dbgOption);

       MainWindow w(QUrl(QStringLiteral("ws://192.168.31.168:3347")), debug);
       QObject::connect(&w, &MainWindow::closed, &a, &QCoreApplication::quit);

       QFile file("/home/tom/Documentos/ProyectoVuelos/Tomeu_Widgets/VuelosUI/qss/style.qss");
       if (file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           w.setStyleSheet(file.readAll());
           file.close();
       }

    w.show();


    return a.exec();
}
