#include "credit_calc.h"
#include "ui_credit_calc.h"

credit_calc::credit_calc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::credit_calc)
{
    ui->setupUi(this);
    this->setWindowTitle("SmartCalc_v1.0");
    ui->doubleSpinBox_bet->setRange(1.4, 99);
    ui->doubleSpinBox_credit_sum->setRange(30000, 100000000);
    ui->doubleSpinBox_term->setRange(1, 600);
    ui->radioButton_an->setChecked(true);

}

credit_calc::~credit_calc()
{
    delete ui;
}

void credit_calc::on_pushButton_clicked()
{
    this->close();
    emit firstWindow();
}


void credit_calc::on_pushButton_3_clicked()
{
    this->close();
    emit thirdWindow();
}


void credit_calc::on_pushButton_count_clicked()
{
    double per_month = 0, over = 0, sum = 0, coef = 0, m = 0;
    double bet = ui->doubleSpinBox_bet->value();
    double total_payment = ui->doubleSpinBox_term->value();
    total_payment = floor(total_payment);
    double cr = ui->doubleSpinBox_credit_sum->value();
    char temp[255] = {0};
     if(ui->radioButton_an->isChecked()) {
         an_credit(&coef, &m, &total_payment, &per_month, &sum, &over, &bet, &cr);
         sprintf(temp, "%lf", per_month);
         ui->month_pay->setText(temp);
         memset(temp, 0, 255);
         sprintf(temp, "%lf", sum);
         ui->total_payout->setText(temp);
         memset(temp, 0, 255);
         sprintf(temp, "%lf", over);
         ui->overpayment->setText(temp);
         ui->month_pay_2->setText("");
     } else if(ui->radioButton_di->isChecked()) {
         double min_pay = 0, Q = 0, S = 30, Y = ui->doubleSpinBox_credit_sum->value(), payed = 0;
         double min = 0, max = 0;
         min_pay = ui->doubleSpinBox_credit_sum->value() / total_payment;
         min = ui->doubleSpinBox_credit_sum->value();
         df_credit(&min_pay, &total_payment, &Q, &S, &payed, &min, &max, &Y, &over, &bet, &per_month);
           sprintf(temp, "%lf ->", max);
           ui->month_pay->setText(temp);
           memset(temp, 0, 255);
           if(total_payment > 1) {
               sprintf(temp, "%lf", min);
               ui->month_pay_2->setText(temp);
               memset(temp, 0, 255);
           } else {
               ui->month_pay_2->setText("");
           }
           sprintf(temp, "%lf", payed);
           ui->total_payout->setText(temp);
           memset(temp, 0, 255);
           sprintf(temp, "%lf", over);
           ui->overpayment->setText(temp);
     }
}

