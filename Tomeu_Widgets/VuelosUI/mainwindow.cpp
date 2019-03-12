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
            this, &MainWindow::recibirMensaje);
    m_webSocket.sendTextMessage("Mensaje de prueba");

    QMessageBox::information(this, tr("Atención"), tr("Se ha establecido la conexión"));
    ReadJson();
}

void MainWindow::run()
{
    connect(&m_webSocket, &QWebSocket::disconnected, this, &MainWindow::closed);
    connect(&m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);

    m_webSocket.open(QUrl(m_url));
}

void MainWindow::ReadJson()
{

    int idVuelo;
    QString horaVuelo;
    QString infoVuelo;
    QString nombreComp;
    QString destino;
    int nPuerta;

    QString path = "/home/tom/Documentos/ProyectoVuelos/Tomeu_Widgets/VuelosUI/json/vuelo.json";
       QFile vueloFileR(path);
       if(!vueloFileR.open(QIODevice::ReadOnly)){
           qDebug()<<"Failed to open "<<"path";

       }

       QTextStream file_text(&vueloFileR);
       QString stringJsonR;
       stringJsonR = file_text.readAll();
       vueloFileR.close();
       QByteArray bytesJson = stringJsonR.toLocal8Bit();
       auto vueloDocR=QJsonDocument::fromJson(bytesJson);

       if(vueloDocR.isNull()){
           qDebug()<<"Failed to create JSON doc.";
           QMessageBox::information(this, tr("Atención"), tr("Failed to create JSON doc."));
       }
       if(!vueloDocR.isObject()){
           qDebug()<<"JSON is not an object.";
           QMessageBox::information(this, tr("Atención"), tr("JSON is not an object."));
       }

       QJsonObject vueloJsonR=vueloDocR.object();

       if(vueloJsonR.isEmpty()){
           qDebug()<<"JSON object is empty.";
           QMessageBox::information(this, tr("Atención"), tr("JSON object is empty."));
       }

       QVariantMap mapJson = vueloJsonR.toVariantMap();

       idVuelo = mapJson["idvuelo"].toInt();
       horaVuelo = mapJson["horaVuelo"].toString();
       infoVuelo = mapJson["informacionvuelo"].toString();
       nombreComp = mapJson["nombrecompania"].toString();
       destino = mapJson["nombredestino"].toString();
       nPuerta = mapJson["numeropuerta"].toInt();

       this->ui->lblMEnsaje->setText(infoVuelo);
}

void MainWindow::recibirMensaje(QString msg){
    QWebSocket *pClient = qobject_cast<QWebSocket *> (sender());
    /*escribirVuelo(msg);*/
}

void MainWindow::escribirVuelo(QString vuelo){
    QFile file("/home/tom/Documentos/ProyectoVuelos/Tomeu_Widgets/VuelosUI/json/vuelo.json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);
    out << vuelo << endl;

    file.close();
}
