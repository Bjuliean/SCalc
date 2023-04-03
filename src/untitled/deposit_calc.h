#ifndef DEPOSIT_CALC_H
#define DEPOSIT_CALC_H

#include <QDialog>
#ifdef __cplusplus
extern "C"
{
#endif
#include "../calc_engine.h"
#ifdef __cpluplus
}
#endif

namespace Ui {
class deposit_calc;
}

class deposit_calc : public QDialog
{
    Q_OBJECT

public:
    explicit deposit_calc(QWidget *parent = nullptr);
    ~deposit_calc();

signals:
    void firstWindow();
    void secondWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_payments_currentIndexChanged(int index);

    void on_pushButton_count_clicked();

private:
    Ui::deposit_calc *ui;
};

#endif // DEPOSIT_CALC_H
