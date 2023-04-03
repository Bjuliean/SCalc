#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

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
class credit_calc;
}

class credit_calc : public QDialog
{
    Q_OBJECT

public:
    explicit credit_calc(QWidget *parent = nullptr);
    ~credit_calc();

signals:
    void firstWindow();
    void thirdWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_count_clicked();

private:
    Ui::credit_calc *ui;
};

#endif // CREDIT_CALC_H
