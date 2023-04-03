#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <qcustomplot.h>
#include <credit_calc.h>
#include <deposit_calc.h>

#ifdef __cplusplus
extern "C"
{
#endif
#include "../calc_engine.h"
#ifdef __cpluplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    credit_calc *window_credit;
    deposit_calc *window_deposit;
    double xBegin, xEnd, h, X;
    int N;
    QVector<double> x, y;

private slots:
    void add_in_x(char *cstr, double X);
    void draw_graph();
    void label_process();
    void on_pushButton_dot_clicked();
    void on_pushButton_equal_clicked();
    void math_operations();
    void on_pushButton_plus_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_mul_clicked();
    void on_pushButton_div_clicked();
    void on_pushButton_mod_clicked();
    void on_pushButton_brackets_clicked();
    void on_pushButton_sin_clicked();
    void on_pushButton_cos_clicked();
    void on_pushButton_tan_clicked();
    void on_pushButton_sqrt_clicked();
    void on_pushButton_pow_clicked();
    void on_pushButton_asin_clicked();
    void on_pushButton_acos_clicked();
    void on_pushButton_atan_clicked();
    void on_pushButton_ln_clicked();
    void on_pushButton_log_clicked();
    void on_pushButton_uno_clicked();
    void on_pushButton_x_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
};
#endif // MAINWINDOW_H
