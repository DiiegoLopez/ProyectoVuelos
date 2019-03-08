#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtWebSockets>
#include <QTcpSocket>

MainWindow::MainWindow(const QUrl &url, bool debug, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_url(url),
    m_debug(debug)
{
    ui->setupUi(this);
    QTimer::singleShot(0,this,SLOT(run()));
    run();
    onConnected();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnected()
{
    if (m_debug)
        connect(&m_webSocket, &QWebSocket::textMessageReceived,
                this, &MainWindow::onTextMessageReceived);
        m_webSocket.sendTextMessage("Hello, world!");
}

void MainWindow::run(){
    if (m_debug)
        connect(&m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
        connect(&m_webSocket, &QWebSocket::disconnected, this, &MainWindow::closed);
        m_webSocket.open(QUrl(m_url));
}
