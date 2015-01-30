#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    //for socket
    Q_OBJECT

public:
    //mainw window
    explicit MainWindow(QWidget *parent = 0);
    //check if name is empty
    bool check_name();
    //add new user
    void adduser(QString);
    ~MainWindow();

private slots:
    //slot for send button
    void on_pushButton_clicked();

    void on_pushButton_2_pressed();
    //socket for chenge name button
    void on_pushButton_2_clicked();
    //slot for reading from socket
    void read();


private:
    Ui::MainWindow *ui;
    //vector for names of users in chat
    QVector<QString> names;
    //amount of users in chat
    int am;
};

#endif // MAINWINDOW_H
