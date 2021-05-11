#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include <QApplication>
#include <QDate>
#include <QtSerialPort/QSerialPort>
#include <QFile>
#include <QTextStream>
#include "memoria.h"


namespace Ui {
class MainWindow;
}

class Parametro
{
private:
    uint8_t Humedad;
    float Temperatura;
    float Presion;
    int frecuencia;

public:
    Parametro() {Humedad = 0; Temperatura = 0; Presion = 0; frecuencia = 5;
    Config_PedirMemoria = 0; Config_Frecuencia = 0;}
    void Set_Datos (uint8_t);
    void Set_Datos (uint8_t, float Temp, float Presss);
    void SetFrec (int);
    int Get_Frec ();
    void Set_Temperatura (float);
    void Set_Temperatura (uint8_t,uint8_t);
    void Set_Presion (float);
    void Set_Presion (uint8_t Press_byte1, uint8_t Press_byte2,uint8_t);
    float Get_Temperatura ();
    float Get_Presion ();
    uint8_t Get_Humedad();
    int Config_PedirMemoria;
    int Config_Frecuencia;
    int Config_Cancelar;

};

class Fecha
{
private:
    uint8_t dia;
    uint8_t mes;
    uint16_t anio;
    uint8_t hora;
    uint8_t min;
    uint8_t seg;

public:
    Fecha(){dia = 1; mes = 1; anio=2000; hora = 0; min = 0; seg = 0;}
    void SetDatos(uint8_t anio_byte1, uint8_t anio_byte2, uint8_t mes_, uint8_t dia_, uint8_t hora_, uint8_t min_, uint8_t seg_);
    uint16_t GetAnio ();
    uint8_t Getmes();
    uint8_t Gethora ();
    uint8_t Getdia();
    uint8_t Getmin();
    uint8_t Getseg();
};

class MainWindow : public QMainWindow,public Parametro
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QByteArray m_datos_recibidos;
    QByteArray buf;
    unsigned char estado;
    QTimer *timer;
    void puerto_write (char *msg);
    void puerto_write (const QByteArray&);


    bool Puerto_Null();


private slots:
    void on_pushButton_clicked();
    void Horario ();
    void on_pushButton_Cerrar_clicked();
    void on_conectar_clicked();
    void onDatosRecibidos ();
    void ProcesarComandos();
    void Guardar (unsigned char);
    void Guardar (Parametro&);
    void Guardar_Memoria (uint8_t*);
    void Guardar_Memoria (Fecha&);
    void Guardar_Memoria (Parametro&);
    void visualizar (Parametro&);
    void EnviarFecha (void);

    void on_pushButton_PedirMemoria_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *puerto;

};






#endif // MAINWINDOW_H
