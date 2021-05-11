#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <QDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class Historial;
}

class Historial : public QDialog
{
    Q_OBJECT

public:
    explicit Historial(QWidget *parent = 0);
    ~Historial();



private:
    Ui::Historial *ui;

private slots:
    void file_read(void);

};

#endif // HISTORIAL_H
