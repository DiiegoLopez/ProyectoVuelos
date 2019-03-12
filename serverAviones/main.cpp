#include <QCoreApplication>
#include <socket.h>
#include <conexionbbdd.h>
#include <QDebug>

int main(int argc, char *argv[])
{
     QCoreApplication a(argc, argv);


    socket *server = new socket();
    QObject::connect(server, &socket::closed, &a, &QCoreApplication::quit);
    server->closed();










    return a.exec();
}
