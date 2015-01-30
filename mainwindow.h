#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool check_name();
    void adduser(QString);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_pressed();

    void on_pushButton_2_clicked();

    void read();


private:
    Ui::MainWindow *ui;
    QVector<QString> names;
    int am;
};

#endif // MAINWINDOW_H
