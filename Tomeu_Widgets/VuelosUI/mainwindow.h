#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QtWebSockets>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(const QUrl &url, bool debug = false, QWidget *parent = nullptr);
    ~MainWindow();
    void run();
Q_SIGNALS:
    void closed();
    void onTextMessageReceived();


private Q_SLOTS:
    void onConnected();


private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
