#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QUdpSocket>
#include <QDateTime>

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
    am=0;
    socket= new QUdpSocket(this);
        socket->bind(7777);
        connect(socket, SIGNAL(readyRead()),
        this, SLOT(read()));
}

void MainWindow::on_pushButton_clicked()
{

    QDateTime time = QDateTime::currentDateTime();
    if (ui->textEdit->toPlainText()==""||ui->textEdit->toPlainText()==NULL) return;
    QString str="[" + name +"]["+ time.toString() + "]: "+ ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QByteArray data;
    data.append(str);
    socket->writeDatagram(data.data(), data.size(),
                             QHostAddress::Broadcast, 7777);
}


void MainWindow::on_pushButton_2_clicked()
{
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

void MainWindow::on_pushButton_2_pressed(){}

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
        if (msg.at(0)!='[')
            adduser(msg);
        else
        ui->textBrowser->append(msg);
    }
}

void MainWindow::adduser(QString name){
    bool flag=true;
    for ( int i = 0; i < am; i++)
        if (names.at(i)==name) {flag=false; break;}
    if (flag) {names.push_back(name);
    ui->textBrowser_2->append(name);
    ui->textBrowser->append(name + "has joined");
    am++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}





