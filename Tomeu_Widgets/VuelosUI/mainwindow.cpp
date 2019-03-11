#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtWebSockets>

MainWindow::MainWindow(const QUrl &url, bool debug, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_url(url)
{
    ui->setupUi(this);
    QTimer::singleShot(0,this,SLOT(run()));
    run();
    //onConnected();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &MainWindow::onTextMessageReceived);
    m_webSocket.sendTextMessage("Cocaina fresca!");
}

void MainWindow::run()
{
    connect(&m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &MainWindow::closed);
    m_webSocket.open(QUrl(m_url));
}

void MainWindow::ReadJson(int idVuelo, QString horaVuelo, QString infoVuelo, QString nombreComp, QString destino, int nPuerta)
{

    QString path = "/home/usuario/pruebaJson/vuelo.json";
       QFile vueloFileR(path);
       if(!vueloFileR.open(QIODevice::ReadOnly)){
           qDebug()<<"Failed to open "<<"path";
           exit(1);
       }

       QTextStream file_text(&vueloFileR);
       QString stringJsonR;
       stringJsonR = file_text.readAll();
       vueloFileR.close();
       QByteArray bytesJson = stringJsonR.toLocal8Bit();
       auto vueloDocR=QJsonDocument::fromJson(bytesJson);

       if(vueloDocR.isNull()){
           qDebug()<<"Failed to create JSON doc.";
           exit(2);
       }
       if(!vueloDocR.isObject()){
           qDebug()<<"JSON is not an object.";
           exit(3);
       }

       QJsonObject vueloJsonR=vueloDocR.object();

       if(vueloJsonR.isEmpty()){
           qDebug()<<"JSON object is empty.";
           exit(4);
       }

       QVariantMap mapJson = vueloJsonR.toVariantMap();

       idVuelo = mapJson["idVuelo"].toInt();
       horaVuelo = mapJson["horaVuelo"].toString();
       infoVuelo = mapJson["infoVuelo"].toString();
       nombreComp = mapJson["nombreComp"].toString();
       destino = mapJson["destino"].toString();
       nPuerta = mapJson["nPuerta"].toInt();

       qDebug()<< "idvuelo: " << idVuelo;
       qDebug()<< "Hora vuelo: " << horaVuelo;
       qDebug()<< "Info vuelo: " << infoVuelo;
       qDebug()<< "Nombre compañia: " << nombreComp;
       qDebug()<< "Destino: " << destino;
       qDebug()<< "nº Puerta" << nPuerta;
}
