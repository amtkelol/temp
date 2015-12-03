#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->socketStatus->setText("");
    ui->adressLineEdit->setPlaceholderText("Adress");
    ui->portLineEdit->setPlaceholderText("Port");
    ui->adressLineEdit->setText("google.com");
    ui->portLineEdit->setText("80");

    socket = new TcpSocket();

    connect(ui->startButton, &QPushButton::clicked, [this]() {
        socket->connectSocket(ui->adressLineEdit->text(), ui->portLineEdit->text().toShort());
    });
    connect(ui->stopButton, &QPushButton::clicked, [this]() {
        socket->disconnectSocket();
    });
    connect(socket, &TcpSocket::socketErrorSignal, [this](const QString &err) {
        ui->textEdit->append("Error: " + err);
    });
    connect(socket, &TcpSocket::bytesWrittenSignal, [this](const qint64 &bytes) {
        ui->textEdit->append("Bytes sent: " + QString::number(bytes));
    });

    connect(socket, &TcpSocket::socketStateSignal, [this](QAbstractSocket::SocketState state) {
        switch(state) {
        case 0:
            ui->textEdit->append("Unconnected State");
            ui->socketStatus->setText("Unconnected State");
            break;
        case 1:
            ui->textEdit->append("Host Lookup State");
            ui->socketStatus->setText("Host Lookup State");
            break;
        case 2:
            ui->textEdit->append("Connecting State");
            ui->socketStatus->setText("Connecting State");
            break;
        case 3:
            ui->textEdit->append("Connected State");
            ui->socketStatus->setText("Connected State");
            break;
        case 4:
            ui->textEdit->append("Bound State");
            ui->socketStatus->setText("Bound State");
            break;
        case 5:
            ui->textEdit->append("Listening State");
            ui->socketStatus->setText("Listening State");
            break;
        case 6:
            ui->textEdit->append("Closing State");
            ui->socketStatus->setText("Closing State");
            break;
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
