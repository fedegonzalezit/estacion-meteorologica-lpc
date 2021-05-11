#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QDialog>

namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QDialog
{
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = 0);
    ~VentanaPrincipal();

private:
    Ui::VentanaPrincipal *ui;
};

#endif // VENTANAPRINCIPAL_H
