#ifndef MEMORIA_H
#define MEMORIA_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessagebox>
#include "mainwindow.h"

namespace Ui {
class Memoria;
}

class Memoria : public QDialog
{
    Q_OBJECT

public:
    explicit Memoria(QWidget *parent = 0);
    ~Memoria();
    void file_read ();

private:
    Ui::Memoria *ui;
};

#endif // MEMORIA_H
