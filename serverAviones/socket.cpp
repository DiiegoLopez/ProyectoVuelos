#include "socket.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <iostream>
#include <fstream>
#include <QFile>
#include <conexionbbdd.h>




socket::socket() :
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Test Server"),
                                            QWebSocketServer::NonSecureMode, this))


{


    quint16 port=  leerConf(":\configuracion").toUShort();

    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server iniciado en puerto:" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &socket::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &socket::closed);
    } // end if
}


socket::~socket()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

QString socket::leerConf(QString archivo)
{
    QFile inputFile(archivo);

    if(!inputFile.exists())
    {
    qDebug() << "no se ha encontrado el archivo";
    }
    else{


    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
         QString busqueda("port:");
         QString line = in.readLine();

         int pos = line.indexOf(busqueda);
         if (line.contains(busqueda))
         {
             QString resto = line.mid ( pos + busqueda.length());
             return resto;
             inputFile.close();
         }



        }
        QString defecto = "1234";

        return defecto;
        inputFile.close();

    }
    }
}



void socket::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    qDebug() << "Socket conectado:" << pSocket;
    ConexionBBDD b;
    b.Conectar();
    QString vuelo= b.DevolverVuelos();
    qDebug() << "Vuelo enviado!";

    pSocket->sendTextMessage(QString(vuelo));



    connect(pSocket, &QWebSocket::disconnected, this, &socket::socketDisconnected);



    m_clients << pSocket;

}


void socket::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "De:" << pClient << "Mensaje recibido:" << message;






}




void socket::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Socket desconectado:" << pClient;

    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    } // end if
}
