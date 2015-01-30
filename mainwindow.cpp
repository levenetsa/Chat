#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QUdpSocket>

//variables
QUdpSocket *socket;
QString name;

//methods
void send_msg();
bool check_name();
void read();
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket= new QUdpSocket(this);
        socket->bind(34444);
        connect(socket, SIGNAL(readyRead()),
        this, SLOT(read()));
}

void MainWindow::on_pushButton_clicked()
{
    QString str="[" + name + "]: "+ ui->textEdit->toPlainText();
    QByteArray datagram;
    datagram.append(str);
    socket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, 34444);
}


void MainWindow::on_pushButton_2_clicked()
{
    name = ui->textEdit_2->toPlainText();
    if (check_name())
    {
        ui->label_3->setText(name);
        ui->textBrowser->append("Your name is " + name);
    }
}

bool MainWindow::check_name()
{
    if (name == "" || name == NULL)
    {
        ui->textBrowser->append("Wrong name!");
        return false;
    }
    return true;
}

void MainWindow::read()
{
    QByteArray datagram;
    while (socket->hasPendingDatagrams())
    {
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());
        QString msg = QString(datagram);
        ui->textBrowser->append(msg);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}





