#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    window_credit = new credit_calc();
    window_deposit = new deposit_calc();

    connect(window_deposit, &deposit_calc::firstWindow, this, &MainWindow::show);
    connect(window_credit, &credit_calc::firstWindow, this, &MainWindow::show);
    connect(window_deposit, &deposit_calc::secondWindow, window_credit, &credit_calc::show);
    connect(window_credit, &credit_calc::thirdWindow, window_deposit, &deposit_calc::show);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(label_process()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(label_process()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(label_process()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(label_process()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(label_process()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(label_process()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(label_process()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(label_process()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(label_process()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(label_process()));

    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operations()));

    ui->spinBox_minx->setRange(-100000, 100000);
    ui->spinBox_maxx->setRange(-100000, 100000);
    ui->spinBox_miny->setRange(-100000, 100000);
    ui->spinBox_maxy->setRange(-100000, 100000);
    ui->spinBox_minx->setValue(-10);
    ui->spinBox_maxx->setValue(10);
    ui->spinBox_miny->setValue(-10);
    ui->spinBox_maxy->setValue(10);
    draw_graph();
}

bool is_dotable = true;
int opened_brackets = 0;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_in_x(char *cstr, double X) {
    char temp[255] = {0};
    char new_arr[255] = {0};
    int z = 0;
    sprintf(temp, "%lf", X);
    for(size_t i = 0; i < strlen(cstr); i++) {
        if(cstr[i] == 'x') {
            if(cstr[i - 1] >= '0' && cstr[i - 1] <= '9') {
                new_arr[z] = '*';
                z++;
            }
                for(size_t y = 0; y < strlen(temp); y++) {
                    new_arr[z] = temp[y];
                    z++;
                }
            if(cstr[i + 1] == '(' || (cstr[i + 1] >= '0' && cstr[i + 1] <= '9')) {
                new_arr[z] = '*';
                z++;
            }
        } else {
            new_arr[z] = cstr[i];
            z++;
        }
    }
    calculation(new_arr);
    strcpy(cstr, new_arr);
}

void MainWindow::draw_graph() {
    ui->widget->clearPlottables();
    h = 0.1;
    xBegin = ui->spinBox_minx->value();
    xEnd = ui->spinBox_maxx->value();
    ui->widget->xAxis->setRange(ui->spinBox_minx->value(), ui->spinBox_maxx->value());
    ui->widget->yAxis->setRange(ui->spinBox_miny->value(), ui->spinBox_maxy->value());
    X = xBegin;
    N = (xEnd - xBegin)/h + 2;
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[255];
    char temp[255] = {0};
    strcpy(cstr, str.c_str());
    for(X = xBegin; X <= xEnd; X += h) {
        strcpy(temp, cstr);
        x.push_back(X);
        add_in_x(temp, X);
        y.push_back(atof(temp));
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    x.clear();
    y.clear();
    delete[] cstr;
}

void MainWindow::label_process()
{
    QPushButton *button = (QPushButton *)sender();

    QString str_numb;
    str_numb = (ui->result_show->text());
    std::string str = str_numb.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(strcmp(cstr, "ERROR") == 0 || strcmp(cstr, "DIV BY 0") == 0) {
        str_numb = (button->text());
    }else {
        if(cstr[strlen(cstr) - 1] == ')')
            ui->result_show->setText(ui->result_show->text() + "*");
        str_numb = (ui->result_show->text() + button->text());
    }
    ui->result_show->setText(str_numb);
    delete[] cstr;
}

void MainWindow::math_operations()
{
    QPushButton *button = (QPushButton *)sender();

    button->setChecked(true);
}

void MainWindow::on_pushButton_dot_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(is_dotable == true) {
        if(cstr[strlen(cstr) - 1] < 48 || cstr[strlen(cstr) - 1] > 57)
            ui->result_show->setText(ui->result_show->text() + "0.");
        else
            ui->result_show->setText(ui->result_show->text() + ".");
        is_dotable = false;
    }
    delete[] cstr;
}

void MainWindow::on_pushButton_equal_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[255];
    strcpy(cstr, str.c_str());
    QString input2 = ui->lineEdit_xvalue->text();
    std::string str2= input2.toStdString();
    char* cstr2 = new char[255];
    strcpy(cstr2, str2.c_str());
    if(strchr(cstr, 'x') == NULL && strcmp(cstr2, "") == 0) {
        if(strlen(cstr) == 0) {
            ui->result_show->setText("0");
        } else {
            calculation(cstr);
            std::string res_str(cstr);
            QString label = QString::fromStdString(res_str);
            if(strlen(cstr) > 36)
                ui->result_show->setText("inf");
            else
                ui->result_show->setText(label);
        }
    } else if(strchr(cstr, 'x') != NULL || strcmp(cstr2, "") != 0){
        if(strchr(cstr, 'x') != NULL && strcmp(cstr2, "") == 0)
            draw_graph();
        else {
            add_in_x(cstr, atof(cstr2));
            calculation(cstr);
            std::string res_str(cstr);
            QString label = QString::fromStdString(res_str);
            if(strlen(cstr) > 36)
                ui->result_show->setText("inf");
            else
                ui->result_show->setText(label);
        }
    }
    if(strchr(cstr, '.') != NULL)
        is_dotable = false;
    delete[] cstr;
    delete[] cstr2;
}


void MainWindow::on_pushButton_plus_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if((cstr[strlen(cstr) - 1] >= 48 && cstr[strlen(cstr) - 1] <= 57) || cstr[strlen(cstr) - 1] == ')' || cstr[strlen(cstr) - 1] == 'x') {
        ui->result_show->setText(ui->result_show->text() + "+");
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_clear_clicked()
{
    ui->result_show->setText("");
    is_dotable = true;
    opened_brackets = 0;
}


void MainWindow::on_pushButton_minus_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if((cstr[strlen(cstr) - 1] >= 48 && cstr[strlen(cstr) - 1] <= 57) || cstr[strlen(cstr) - 1] == ')' || cstr[strlen(cstr) - 1] == '(' || cstr[strlen(cstr) - 1] == 'x') {
        ui->result_show->setText(ui->result_show->text() + "-");
        is_dotable = true;
    }
    if(strlen(cstr) == 0) {
        ui->result_show->setText(ui->result_show->text() + "-");
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_mul_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if((cstr[strlen(cstr) - 1] >= 48 && cstr[strlen(cstr) - 1] <= 57) || cstr[strlen(cstr) - 1] == ')' || cstr[strlen(cstr) - 1] == 'x') {
        ui->result_show->setText(ui->result_show->text() + "*");
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_div_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if((cstr[strlen(cstr) - 1] >= 48 && cstr[strlen(cstr) - 1] <= 57) || cstr[strlen(cstr) - 1] == ')' || cstr[strlen(cstr) - 1] == 'x') {
        ui->result_show->setText(ui->result_show->text() + "/");
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_mod_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if((cstr[strlen(cstr) - 1] >= 48 && cstr[strlen(cstr) - 1] <= 57) || cstr[strlen(cstr) - 1] == ')' || cstr[strlen(cstr) - 1] == 'x') {
        ui->result_show->setText(ui->result_show->text() + "mod");
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_brackets_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(cstr[strlen(cstr) - 1] != '.') {
        if(opened_brackets > 0 && ((cstr[strlen(cstr) - 1] >= '0' && cstr[strlen(cstr) - 1] <= '9') || cstr[strlen(cstr) - 1] == ')' || cstr[strlen(cstr) - 1] == 'x')) {
            ui->result_show->setText(ui->result_show->text() + ")");
            opened_brackets--;
        }
        else if(opened_brackets == 0 || (cstr[strlen(cstr) - 1] < '0' || cstr[strlen(cstr) - 1] > '9')) {
            if((cstr[strlen(cstr) - 1] >= '0' && cstr[strlen(cstr) - 1] <= '9') || cstr[strlen(cstr) - 1] == ')')
                ui->result_show->setText(ui->result_show->text() + "*(");
            else
                ui->result_show->setText(ui->result_show->text() + "(");
            opened_brackets++;
            is_dotable = true;
        }
    }

    delete[] cstr;
}


void MainWindow::on_pushButton_sin_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(cstr[strlen(cstr) - 1] != '.') {
        if((cstr[strlen(cstr) - 1] < '0' || cstr[strlen(cstr) - 1] > '9') && cstr[strlen(cstr) - 1] != 'x' && cstr[strlen(cstr) - 1] != ')')
            ui->result_show->setText(ui->result_show->text() + "sin(");
        else
            ui->result_show->setText(ui->result_show->text() + "*sin(");
        opened_brackets++;
    is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_cos_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(cstr[strlen(cstr) - 1] != '.') {
        if((cstr[strlen(cstr) - 1] < '0' || cstr[strlen(cstr) - 1] > '9') && cstr[strlen(cstr) - 1] != 'x' && cstr[strlen(cstr) - 1] != ')')
            ui->result_show->setText(ui->result_show->text() + "cos(");
        else
            ui->result_show->setText(ui->result_show->text() + "*cos(");
        opened_brackets++;
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_tan_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(cstr[strlen(cstr) - 1] != '.') {
        if((cstr[strlen(cstr) - 1] < '0' || cstr[strlen(cstr) - 1] > '9') && cstr[strlen(cstr) - 1] != 'x' && cstr[strlen(cstr) - 1] != ')')
            ui->result_show->setText(ui->result_show->text() + "tan(");
        else
            ui->result_show->setText(ui->result_show->text() + "*tan(");
        opened_brackets++;
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_sqrt_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(cstr[strlen(cstr) - 1] != '.') {
        if((cstr[strlen(cstr) - 1] < '0' || cstr[strlen(cstr) - 1] > '9') && cstr[strlen(cstr) - 1] != 'x' && cstr[strlen(cstr) - 1] != ')')
            ui->result_show->setText(ui->result_show->text() + "sqrt(");
        else
            ui->result_show->setText(ui->result_show->text() + "*sqrt(");
        opened_brackets++;
        is_dotable = true;
    }

    delete[] cstr;
}


void MainWindow::on_pushButton_pow_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(cstr[strlen(cstr) - 1] != '.') {
        if((cstr[strlen(cstr) - 1] >= 48 && cstr[strlen(cstr) - 1] <= 57) || cstr[strlen(cstr) - 1] == ')' || cstr[strlen(cstr) - 1] == 'x') {
            ui->result_show->setText(ui->result_show->text() + "^");
            is_dotable = true;
        }
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_asin_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(cstr[strlen(cstr) - 1] != '.') {
        if((cstr[strlen(cstr) - 1] < '0' || cstr[strlen(cstr) - 1] > '9') && cstr[strlen(cstr) - 1] != 'x' && cstr[strlen(cstr) - 1] != ')')
            ui->result_show->setText(ui->result_show->text() + "asin(");
        else
            ui->result_show->setText(ui->result_show->text() + "*asin(");
        opened_brackets++;
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_acos_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(cstr[strlen(cstr) - 1] != '.') {
        if((cstr[strlen(cstr) - 1] < '0' || cstr[strlen(cstr) - 1] > '9') && cstr[strlen(cstr) - 1] != 'x' && cstr[strlen(cstr) - 1] != ')')
            ui->result_show->setText(ui->result_show->text() + "acos(");
        else
            ui->result_show->setText(ui->result_show->text() + "*acos(");
        opened_brackets++;
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_atan_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(cstr[strlen(cstr) - 1] != '.') {
        if((cstr[strlen(cstr) - 1] < '0' || cstr[strlen(cstr) - 1] > '9') && cstr[strlen(cstr) - 1] != 'x' && cstr[strlen(cstr) - 1] != ')')
            ui->result_show->setText(ui->result_show->text() + "atan(");
        else
            ui->result_show->setText(ui->result_show->text() + "*atan(");
        opened_brackets++;
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_ln_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(cstr[strlen(cstr) - 1] != '.') {
        if((cstr[strlen(cstr) - 1] < '0' || cstr[strlen(cstr) - 1] > '9') && cstr[strlen(cstr) - 1] != 'x' && cstr[strlen(cstr) - 1] != ')')
            ui->result_show->setText(ui->result_show->text() + "ln(");
        else
            ui->result_show->setText(ui->result_show->text() + "*ln(");
        opened_brackets++;
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_log_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(cstr[strlen(cstr) - 1] != '.') {
        if((cstr[strlen(cstr) - 1] < '0' || cstr[strlen(cstr) - 1] > '9') && cstr[strlen(cstr) - 1] != 'x' && cstr[strlen(cstr) - 1] != ')')
            ui->result_show->setText(ui->result_show->text() + "log(");
        else
            ui->result_show->setText(ui->result_show->text() + "*log(");
        opened_brackets++;
        is_dotable = true;
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_uno_clicked()
{
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    if(strcmp(cstr, "ERROR") == 0 || strcmp(cstr, "DIV BY 0") == 0) {
        on_pushButton_clear_clicked();
    } else {
        if(cstr[strlen(cstr) - 1] == '.')
            is_dotable = true;
        if(cstr[strlen(cstr) - 1] == ')')
            opened_brackets++;
        if(cstr[strlen(cstr) - 1] == '(')
            opened_brackets--;
        cstr[strlen(cstr) - 1] = '\0';
        std::string res_str(cstr);
        QString label = QString::fromStdString(res_str);
        ui->result_show->setText(label);
    }
    delete[] cstr;
}


void MainWindow::on_pushButton_x_clicked()
{
    ui->result_show->setText(ui->result_show->text() + "x");
}

void MainWindow::on_pushButton_10_clicked()
{
    window_credit->show();
    this->close();
}


void MainWindow::on_pushButton_11_clicked()
{
    window_deposit->show();
    this->close();
}

