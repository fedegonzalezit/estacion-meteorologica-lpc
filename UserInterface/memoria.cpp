#include "memoria.h"
#include "ui_memoria.h"

Memoria::Memoria(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Memoria)
{
    ui->setupUi(this);
    file_read();
    this->setWindowTitle("Memoria");
}

Memoria::~Memoria()
{
    delete ui;
}

void Memoria:: file_read()
{
    QString Datos;
    QFile file("datos_memoria.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Error al abrir el archivo");
    }

    QTextStream in(&file);
    Datos = in.readAll();
    ui->textBrowser->setText(Datos);
    file.close ();
}
