#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QUdpSocket>
#include <QDateTime>

//variables
QUdpSocket *socket;
QString name;

//methods

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //amout of users in chat
    //atbiginnig is 0
    am = 0;
    //new socket for recieving mails
    socket = new QUdpSocket(this);
    //bind at empty port
    socket->bind(7777);
    //connecting of recieving signalto read() slot
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(read()));
}

void MainWindow::on_pushButton_clicked()
{
    //sending message
    QDateTime time = QDateTime::currentDateTime();
    if (ui->textEdit->toPlainText() == "" || ui->textEdit->toPlainText() == NULL) return;
    QString str = "[" + name + "][" + time.toString() + "]: " + ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QByteArray data;
    data.append(str);
    socket->writeDatagram(data.data(), data.size(),
                          QHostAddress::Broadcast, 7777);
}


void MainWindow::on_pushButton_2_clicked()
{
    // changing name
    name = ui->textEdit_2->toPlainText();
    if (check_name())
    {
        QByteArray data;
        data.append(name);
        socket->writeDatagram(data.data(), data.size(),
                              QHostAddress::Broadcast, 7777);
        ui->label_3->setText(name);
        ui->textBrowser->append("Your name is " + name);
    }
}

void MainWindow::on_pushButton_2_pressed() {}

bool MainWindow::check_name()
{
    //check if name is empty
    if (name == "" || name == NULL)
    {
        ui->textBrowser->append("Wrong name!");
        return false;
    }
    return true;
}

void MainWindow::read()
{
    //reading from socket
    QByteArray data;
    while (socket->hasPendingDatagrams())
    {
        //resize data
        data.resize(socket->pendingDatagramSize());
        socket->readDatagram(data.data(), data.size());
        //getting message
        QString msg = QString(data);
        if (msg.at(0) != '[')
            //for new users
            adduser(msg);
        else
            //for simple message
            ui->textBrowser->append(msg);
    }
}

void MainWindow::adduser(QString name)
{
    bool flag = true;
    //chek if user with same name was in chat
    for ( int i = 0; i < am; i++)
        if (names.at(i) == name)
        {
            flag = false;
            break;
        }
    //if not then add
    if (flag)
    {
        names.push_back(name);
        ui->textBrowser_2->append(name);
        ui->textBrowser->append(name + " has joined");
        am++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


