#ifndef DIALOG_H
#define DIALOG_H

#include "mainwindow.h"
#include<QtSerialPort/QSerialPort>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog, public Parametro
{
    Q_OBJECT
    QTimer m_timer;
    QTimer m_timer_rojo;
    QTimer m_timer_verde;
    int velset;
    int index;

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_Aceptar_clicked();


    void on_pushButton_Ver_Historial_clicked();


    void on_pushButton_4_clicked();

private:
    Ui::Dialog *ui;
};




#endif // DIALOG_H
