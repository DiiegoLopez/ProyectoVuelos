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
