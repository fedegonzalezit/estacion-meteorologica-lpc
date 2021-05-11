#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include"qserialport.h"
#include<QSerialPortInfo>
#include<QSerialPort>
#include"qserialportinfo.h"
extern Parametro Par;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer (this);
    connect (timer, SIGNAL (timeout()), this, SLOT(Horario()));
    timer->start(1000);
    this->setWindowTitle("Estación Meteorologica");
    puerto = NULL;
    QList <QSerialPortInfo> port = QSerialPortInfo::availablePorts();   //QSerialEnumerator::getPorts();    //genero el QList y lo completo con los detalles (nombres) de los puertos que nos da el Sist. Operativo
    ui->comboBox->clear();                                                  //limpio el combo box
    for(int i=0; i<port.size(); i++)
    {
          ui->comboBox->addItem(port.at(i).QSerialPortInfo::portName());        //lleno el combo box con los datos del QList
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::puerto_write (char *msg)
{
    puerto->write(msg);
}
void MainWindow::puerto_write (const QByteArray &data)
{

    puerto->write(data);
}


bool MainWindow::Puerto_Null()
{
    if (puerto){
        return 1;
    }
    return 0;
}
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------//
void MainWindow::on_pushButton_clicked()
{
    Parametro param;
    Dialog Configuracion;                //instancio un objeto de la clase Dialog
    Configuracion.setModal(true);      //Seteo la ventana de la forma "modal"
    Configuracion.exec();              //ejecuto el segundo objeto

    QByteArray b;

    if (!Par.Config_Cancelar)
    {
        if (Par.Config_Frecuencia)
            Par.Config_Frecuencia = 0;

            if(Puerto_Null())
            {
                param.SetFrec(Par.Get_Frec());
                b.append(0xA7);
                b.append(0xA6);
                b.append(Par.Get_Frec()>>8);
                b.append(Par.Get_Frec()&0xFF);

                puerto_write(b);

                QMessageBox msgBox;
                msgBox.setText("Los cambios han sido guardados con éxito");
                msgBox.setIcon(QMessageBox::Information);
                msgBox.exec();
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText("Los cambios no se han podido guardar");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.exec();
            }

       }
       else
        Par.Config_Cancelar = 0;




}
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//
void MainWindow::on_pushButton_Cerrar_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Salir", "¿Está seguro que desea salir?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes){
        QApplication::quit();
    }


}
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
void MainWindow::Horario()
{
    QTime time = QTime::currentTime();
    QDate fecha = QDate::currentDate();
    QString time_text = time.toString("hh:mm:ss");
    QString fecha_text = fecha.toString("dd/MM/yyyy ");
    time_text = ("Fecha: ") + fecha_text + ("Hora: ") + time_text;
    ui->label_Hora->setText(time_text);
}

//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//  Configura el puerto seleccionado y lo abre
// Togglea abriendo - cerrando el puerto
void MainWindow::on_conectar_clicked()
{
    if(!puerto)
    {
        puerto= new QSerialPort(ui->comboBox->currentText());
            puerto->setBaudRate(QSerialPort::Baud9600);
            puerto->setDataBits(QSerialPort::Data8);
            puerto->setFlowControl(QSerialPort::NoFlowControl);
            puerto->setStopBits(QSerialPort::OneStop);
            puerto->setParity(QSerialPort::NoParity);

            if(puerto->open(QIODevice::ReadWrite))//==true
            {
                ui->label_estado->setText("CONECTADO");
                connect(puerto, SIGNAL(readyRead()),this,SLOT(onDatosRecibidos()));
            }
    }

   else
   {
               ui->label_estado->setText("DESCONECTADO");
       puerto->close();
       delete puerto;
       puerto=NULL;

   }


}

//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//

void MainWindow::onDatosRecibidos()
{

    QByteArray bytes;
    int cant = puerto->bytesAvailable();    //me devuelve la cantidad de bytes disponibles
    bytes.resize(cant);                     //redimensiona
    puerto->read(bytes.data(),bytes.size());    //en bytes quedan los datos recibidos
    m_datos_recibidos += bytes;
    ProcesarComandos();

}



//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//


//Trama esperada (P, R,temp_byte1, temp_byte2, presion_byte1, presion_byte2, humedad)
//Trama esperada (#,@, datos de memoria)
//Trama esperada (&,%, F) Pide la fecha;

void MainWindow::ProcesarComandos()
{
    typedef enum
    {
        H0=0,
        ESPERA_R,
        PARAMETROS,
        ESPERA_ARROBA,
        GUARDAR_MEMORIA_1,
        ESPERA_D,
        ESPERA_K,
        GUARDAR_MEMORIA_DATOS,
        GUARDAR_MEMORIA_FECHA,
        FECHA1,
        FECHA2

    } ESTADOS;

    static ESTADOS estado = H0;
    static uint8_t d[5];
    static uint8_t j=0, k=0;
    static uint16_t largo;

    for(static int i=0; i < m_datos_recibidos.count(); i++)
    {
        uint8_t dato = m_datos_recibidos[i];
        Parametro param;
        Fecha fech;
       // s.sprintf("%d", dato);
        switch(estado)
            {
             case H0:
                 if(dato == 'P')
                   estado = ESPERA_R;

                 if (dato == '#')
                     estado = ESPERA_ARROBA;
                 if (dato == '&')
                     estado = FECHA1;

             break;

            case ESPERA_R:
                if(dato == 'R')
                    estado = PARAMETROS;
                else{
                    estado = H0;
                }
            break;

            case ESPERA_ARROBA:
                if (dato == '@')
                    estado = GUARDAR_MEMORIA_1;
                else
                    estado = H0;

            break;

            case FECHA1:
                if(dato == '%')
                    estado = FECHA2;
                else
                    estado = H0;
            break;

            case FECHA2:
                if (dato == 'F')
                    EnviarFecha ();
                estado = H0;
            break;

            case GUARDAR_MEMORIA_1:

                d[j] = dato;
                j++;
                if (j == 2)
                {
                    estado = ESPERA_K;
                    j = 0;
                    largo = (d[0]<<8)|(d[1]&0xFF);
                    largo = (largo-2)/15;

                }

            break;

            case ESPERA_K:
                if (dato == 'K')
                {
                    estado = GUARDAR_MEMORIA_FECHA;
                }
                else
                {
                    estado = H0;
                }
            break;

            case GUARDAR_MEMORIA_FECHA:

                d[j] = dato;
                j++;
                if (j == 7)
                {
                    fech.SetDatos(d[0],d[1],d[2],d[3],d[4],d[5],d[6]);
                    Guardar_Memoria(fech);
                    estado = ESPERA_D;
                    j=0;
                }

            break;

            case ESPERA_D:
                if (dato == 'D')
                {
                    estado = GUARDAR_MEMORIA_DATOS;
                }
                else
                {
                    estado = H0;
                }
            break;

            case GUARDAR_MEMORIA_DATOS:

                //largo = largo-2;
                d[j] = dato;
                j++;

                if (j >= 6)
                {
                    param.Set_Temperatura(d[0],d[1]);
                    param.Set_Datos(d[2]);
                    param.Set_Presion(d[3],d[4],d[5]);
                    Guardar_Memoria (param);
                    k++;
                    j = 0;
                    estado = ESPERA_K;
                }
//                if (k == largo)
//                {
//                    k = 0;
////                    Memoria Memo;
////                    Memo.setModal(true);
////                    Memo.exec();
//                    largo = 0;
//                    estado = H0;
//                    i = 0;
//                    m_datos_recibidos.clear();
//                }

            break;


            case PARAMETROS:
                //Se espera recibir, (temp_byte1, temp_byte2, presion_byte1, presion_byte2, presion_byte3, humedad)
                d[j] = dato;
                j++;
                if (j==6)
                {
                    j=0;
                    //Seteo humedad
                    param.Set_Datos(d[5]);
                    param.Set_Temperatura(d[0],d[1]);
                    param.Set_Presion(d[2], d[3], d[4]);
                    visualizar(param);
                    Guardar(param);
                    estado = H0;
                    i = -1;
                    m_datos_recibidos.clear();
                }
            break;

            }
    }
}

//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//

void MainWindow::Guardar(unsigned char dato)
{
    QString Datos;
    QFile file("datos_memoria.txt");

    if (!file.open(QFile::Append | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Error al abrir el archivo");
    }

    QTextStream out(&file);
    out << Datos.sprintf("%c", dato);
    //Termino linea
    if (dato == 'F')
        out << Datos.sprintf("\r\n%c", dato);

    file.close ();
}

//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//

void MainWindow::visualizar(Parametro &param)
{
    QString cadena;

    cadena.sprintf("%fºC", param.Get_Temperatura());
    ui->label_Temperatura->clear();
    ui->label_Temperatura->setText(cadena);

    cadena.sprintf("%d%%", param.Get_Humedad());
    ui->label_Humedad->clear();
    ui->label_Humedad->setText(cadena);

    cadena.sprintf("%fhPa",param.Get_Presion());
    ui->label_Presion->clear();
    ui->label_Presion->setText(cadena);
}


//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
void MainWindow::EnviarFecha (void)
{

    QTime time = QTime::currentTime();
    QDate fecha = QDate::currentDate();
    QByteArray b;

    if(Puerto_Null())
    {

        uint8_t aux = ((fecha.day()+fecha.month()+(fecha.year()>>8))+(fecha.year()&0xFF)+time.hour()+time.minute()+time.second())&0xFF;
        b.append(0xAA);
        b.append(0xA1);
        b.append(fecha.day());
        b.append(fecha.month());
        b.append(fecha.year()>>8);
        b.append(fecha.year()&0xFF);
        b.append(time.hour());
        b.append(time.minute());
        b.append(time.second());
        b.append(aux);

        puerto_write(b);



    }
}


//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
void MainWindow::Guardar (Parametro& param)
{
    QString Datos;
    QTime time = QTime::currentTime();
    QDate fecha = QDate::currentDate();
    QFile file("datos.txt");

    if (!file.open(QFile::Append | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Error al abrir el archivo");
    }

    QTextStream out(&file);
    out << Datos.sprintf("Fecha:%d/%d/%d Hora:%d:%d:%d Temperatura:%f°C Humedad:%d%% Presion:%fhPa\r\n", fecha.day(), fecha.month(), fecha.year(), time.hour(), time.minute(), time.second(), param.Get_Temperatura(), param.Get_Humedad(), param.Get_Presion());


    file.close ();
}

void MainWindow::Guardar_Memoria (uint8_t *datos)
{
    QString Datos;
    QFile file ("datos_memoria.txt");
    if (!file.open(QFile::Append | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Error al abrir el archivo");
    }

    QTextStream out(&file);
    out << Datos.sprintf("Fecha:%d/%d/%d Hora:%d:%d:%d Temperatura:%f°C Humedad:%d%% Presion:%fhPa\r\n", datos[3], datos[2], ((datos[0]<<8)|datos[1]), datos[4], datos[5], datos[6], ((float)((datos[7]<<8)|datos[8]))/10, datos[9], ((float)((datos[10]<<16)|(datos[11]<<8)|(datos[12])))/100);
    file.close ();
}


void MainWindow::Guardar_Memoria (Fecha& fech)
{
    QString Datos;
    QFile file ("datos_memoria.txt");
    if (!file.open(QFile::Append | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Error al abrir el archivo");
    }

    QTextStream out(&file);
    out << Datos.sprintf("Fecha:%d/%d/%d Hora:%d:%d:%d ", fech.Getdia(), fech.Getmes(), fech.GetAnio(), fech.Gethora(), fech.Getmin(), fech.Getseg());
    file.close ();
}

void MainWindow::Guardar_Memoria (Parametro& param)
{
    QString Datos;
    QFile file ("datos_memoria.txt");
    if (!file.open(QFile::Append | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Error al abrir el archivo");
    }

    QTextStream out(&file);
    out << Datos.sprintf("Temperatura:%f°C Humedad:%d%% Presion:%fhPa\r\n", param.Get_Temperatura(), param.Get_Humedad(), param.Get_Presion());
    file.close ();
}

//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//-----------------------------FUNCIONES CLASE PARAMETRO---------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//

void Parametro::Set_Datos (uint8_t Hum)
{
    Humedad = Hum;
}
void Parametro::Set_Datos (uint8_t Hum, float Temp, float Press)
{
    Humedad = Hum;
    Temperatura = Temp;
    Presion = Press;

}
void Parametro::Set_Temperatura (float Temp)
{
    Temperatura = Temp;
}
void Parametro::Set_Temperatura (uint8_t Temp_Byte1, uint8_t Temp_Byte2)
{
    float aux;

    aux = ((float)((Temp_Byte1<<8)|Temp_Byte2)/10);

    Temperatura = aux;
}

void Parametro::Set_Presion (float Press)
{
    Presion = Press;
}
void Parametro::Set_Presion (uint8_t Press_byte1, uint8_t Press_byte2, uint8_t Press_byte3)
{
    float aux;

    aux = ((float)((Press_byte1<<16)|Press_byte2<<8|Press_byte3)/100);

    Presion = aux;
}


float Parametro::Get_Temperatura ()
{
    return Temperatura;
}

float Parametro::Get_Presion ()
{
    return Presion;
}

uint8_t Parametro::Get_Humedad()
{
    return Humedad;
}

void Parametro::SetFrec (int frec)
{
    frecuencia = frec;
}

int Parametro::Get_Frec()
{
    return frecuencia;
}

void Fecha::SetDatos(uint8_t anio_byte1, uint8_t anio_byte2, uint8_t mes_, uint8_t dia_, uint8_t hora_, uint8_t min_, uint8_t seg_)
{
    anio = ((anio_byte1<<8) | anio_byte2);
    mes = mes_;
    dia = dia_;
    hora = hora_;
    min = min_;
    seg = seg_;
}

uint16_t Fecha::GetAnio (){
    return anio;
}

uint8_t Fecha::Getmes(){
    return mes;
}

uint8_t Fecha::Gethora ()
{
    return hora;
}

uint8_t Fecha::Getdia()
{
    return dia;
}

uint8_t Fecha::Getmin()
{
    return min;
}

uint8_t Fecha::Getseg()
{
    return seg;
}



void MainWindow::on_pushButton_PedirMemoria_clicked()
{
        QByteArray b;

        if (Puerto_Null())
        {
            b.append((char)0xF7);
            b.append((char)0xF6);
            puerto_write(b);
//            QMessageBox msgBox;
//            msgBox.setText("Cargando");
//            msgBox.setIcon(QMessageBox::Information);
//            msgBox.exec();

        }
        else
        {
            QMessageBox::warning(this, "Error", "Error al enviar mensaje");
        }

}
