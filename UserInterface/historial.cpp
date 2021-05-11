#include "historial.h"
#include "ui_historial.h"

Historial::Historial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Historial)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window|Qt::MSWindowsFixedSizeDialogHint|Qt::WindowMinMaxButtonsHint);
    file_read();
    this->setWindowTitle("Historial");
}

Historial::~Historial()
{
    delete ui;
}


void Historial:: file_read()
{
    QString Datos;
    QFile file("datos.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Error al abrir el archivo");
    }

    QTextStream in(&file);
    Datos = in.readAll();
    ui->textBrowser->setText(Datos);
    file.close ();
}


