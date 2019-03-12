#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtWebSockets>
#include <QJsonParseError>

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

        QFile file("/home/tom/Documentos/ProyectoVuelos/Tomeu_Widgets/VuelosUI/json/vuelo.json");
        bool abre = file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray jsonData = file.readAll();
        file.close();

        if (abre) qDebug() << "abierto";

        QJsonParseError *error = new QJsonParseError;
        QJsonDocument document(QJsonDocument::fromJson(jsonData, error));

        qDebug() << error->errorString();
        qDebug() << "DATOS: " << document.toJson().constData();

        QJsonObject object = document.object();

        QJsonValue value = object.value("vuelos");
        QJsonArray array = value.toArray();


        foreach (const QJsonValue & v, array){
            QString ars[] = {"idvuelo", "horavuelo", "informacionvuelo", "nombredestino", "nombrecompania", "numeropuerta"};

            // Meter

            QTableWidgetItem* item = new QTableWidgetItem;
            QString valor = v.toObject().value(ars[0]).toString();
            item->setText(valor);
            this->ui->tabla->setItem(0, 0, item);

        }

}

void MainWindow::recibirMensaje(QString msg){
    QWebSocket *pClient = qobject_cast<QWebSocket *> (sender());
    escribirVuelo(msg);
}

void MainWindow::escribirVuelo(QString vuelo){
    QFile file("/home/tom/Documentos/ProyectoVuelos/Tomeu_Widgets/VuelosUI/json/vuelo.json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);
    out << vuelo << endl;

    file.close();
}
