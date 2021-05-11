#include "dialog.h"
#include "ui_dialog.h"
#include "historial.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include"qserialport.h"
#include<QSerialPortInfo>
#include<QSerialPort>
#include"qserialportinfo.h"
Parametro Par;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //this->setWindowsTitle("Configuración");
    this->setWindowFlags(Qt::Window|Qt::MSWindowsFixedSizeDialogHint|Qt::WindowMinMaxButtonsHint);
    this->setWindowTitle("Configuración");

}



Dialog::~Dialog()
{
    delete ui;

}

//------------------------------------------------------------------------------------------------------------//
void Dialog::on_pushButton_Aceptar_clicked()
{
    static bool val;
    uint16_t tiempo = 0;
    if ((val= (ui->radioButton_1seg->isChecked())))
        tiempo = 1;

    if ((val= (ui->radioButton_15seg->isChecked())))
        tiempo = 15;

    if ((val= (ui->radioButton_1min->isChecked())))
        tiempo = 60;

    if ((val= (ui->radioButton_3min->isChecked())))
        tiempo = 180;

    if ((val= (ui->radioButton_10min->isChecked())))
        tiempo = 600;

    if (tiempo != 0){
        Par.Config_Frecuencia = 1;
        Par.SetFrec (tiempo);

        this->close();

    }
    else
    {
        Par.Config_Frecuencia = 0;
        QMessageBox msgBox;
        msgBox.setText("No ha realizado cambios");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        this->close();
    }
}



//-------------------------------------------------------------------------------------------------------------//
void Dialog::on_pushButton_Ver_Historial_clicked()
{
    Historial Data;
    Data.setModal(true);
    Data.exec();
}



void Dialog::on_pushButton_4_clicked()
{
    Par.Config_Cancelar = 1;
}
