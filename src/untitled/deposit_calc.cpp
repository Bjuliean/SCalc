#include "deposit_calc.h"
#include "ui_deposit_calc.h"

deposit_calc::deposit_calc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deposit_calc)
{
    ui->setupUi(this);
    this->setWindowTitle("SmartCalc_v1.0");
    ui->doubleSpinBox_deposit_sum->setRange(1, 100000000);
    ui->doubleSpinBox_term->setRange(1, 600);
    ui->doubleSpinBox_bet->setRange(0.01, 99.99);
    ui->doubleSpinBox_tax->setRange(0, 99.99);
    ui->doubleSpinBox_adds->setRange(0, 100000000);
    ui->doubleSpinBox_cuts->setRange(0, 100000000);
    ui->comboBox_capital->hide();
    ui->label_capital->hide();

}

deposit_calc::~deposit_calc()
{
    delete ui;
}

void deposit_calc::on_pushButton_clicked()
{
    this->close();
    emit firstWindow();
}


void deposit_calc::on_pushButton_2_clicked()
{
    this->close();
    emit secondWindow();
}


void deposit_calc::on_comboBox_payments_currentIndexChanged(int index)
{
    if(index == 3) {
        ui->label_capital->show();
        ui->comboBox_capital->show();
    } else {
        ui->label_capital->hide();
        ui->comboBox_capital->hide();
    }
}


void deposit_calc::on_pushButton_count_clicked()
{
    double dep_sum = ui->doubleSpinBox_deposit_sum->value();
    double term = ui->doubleSpinBox_term->value() * 30;
    double bet = ui->doubleSpinBox_bet->value();
    double tax = ui->doubleSpinBox_tax->value();
    double total_sum = dep_sum;
    double added = 0, added_buf = 0;
    double adds = ui->doubleSpinBox_adds->value(), adds_buf = 0;
    int adds_indx = ui->comboBox_adds->currentIndex();
    double cuts = ui->doubleSpinBox_cuts->value(), cuts_buf = 0;
    int cuts_indx = ui->comboBox_cuts->currentIndex();
    int cap_indx = 0;
    if(ui->comboBox_payments->currentIndex() == 3)
        cap_indx = ui->comboBox_capital->currentIndex();
    else
        cap_indx = -1;
    if(adds_indx == 1)
        adds_indx = 30;
    else if(adds_indx == 2)
        adds_indx = 90;
    else if(adds_indx == 0)
        adds_indx = 1;
    else if(adds_indx == 3)
        adds_indx = 360;
    else
        adds_indx = 0;

    if(cuts_indx == 1)
        cuts_indx = 30;
    else if(cuts_indx == 2)
        cuts_indx = 90;
    else if(cuts_indx == 0)
        cuts_indx = 1;
    else if(cuts_indx == 3)
        cuts_indx = 360;
    else
        cuts_indx = 0;

    if(cap_indx == 1)
        cap_indx = 30;
    else if(cap_indx == 2)
        cap_indx = 90;
    else if(cap_indx == 0)
        cap_indx = 1;
    else if(cap_indx == 3)
        cap_indx = 360;
    else
        cap_indx = -1;
    char temp[255] = {0};
    if(cap_indx == -1) {
        deposit(&term, &added, &dep_sum, &bet, &total_sum, &added_buf, &adds, &adds_buf, &adds_indx, &cuts_indx, &cuts, &cuts_buf);
    } else {
        deposit_cap(&term, &cap_indx, &total_sum, &bet, &added_buf, &adds_indx, &adds, &cuts_indx, &cuts_buf, &cuts, &adds_buf);
    }
    total_sum += adds_buf;
    if(cap_indx == -1) {
        total_sum -= cuts_buf;
        added_buf = total_sum - dep_sum;
    }
    tax = added_buf * (tax / 100);
    total_sum -= tax;
    sprintf(temp, "%lf", total_sum);
    ui->label_total_sum->setText(temp);
    memset(temp, 0, 255);
    sprintf(temp, "%lf", tax);
    ui->label_tax_added->setText(temp);
    memset(temp, 0, 255);
    sprintf(temp, "%lf", added_buf);
    ui->label_bet_added->setText(temp);

}

