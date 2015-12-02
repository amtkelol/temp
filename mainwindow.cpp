#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->socketStatus->setText("");
    ui->bytesSent->setText("");

    socket = new TcpSocket();

    connect(socket, &TcpSocket::bytesWrittenSignal, [this](const qint64 &bytes) {
        ui->bytesSent->setText(QString::number(bytes));
    });

    connect(socket, &TcpSocket::socketStateSignal, [this](QAbstractSocket::SocketState state) {
        switch(state) {
        case 0:
            ui->socketStatus->setText("Unconnected State");
            break;
        case 1:
            ui->socketStatus->setText("Host Lookup State");
            break;
        case 2:
            ui->socketStatus->setText("Connecting State");
            break;
        case 3:
            ui->socketStatus->setText("Connected State");
            break;
        case 4:
            ui->socketStatus->setText("Bound State");
            break;
        case 5:
            ui->socketStatus->setText("Listening State");
            break;
        case 6:
            ui->socketStatus->setText("Closing State");
            break;
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
