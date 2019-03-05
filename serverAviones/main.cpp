#include <QCoreApplication>
#include <socket.h>
#include <conexionbbdd.h>

int main(int argc, char *argv[])
{
     QCoreApplication a(argc, argv);


    socket *server = new socket();
    QObject::connect(server, &socket::closed, &a, &QCoreApplication::quit);
    ConexionBBDD b;
    b.Conectar();
    b.DevolverVuelos();






    return a.exec();
}
