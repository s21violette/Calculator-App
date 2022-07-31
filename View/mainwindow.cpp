#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    Controller_ = new s21::Calc_Controller();
}

MainWindow::~MainWindow() {
    delete ui;
    delete Controller_;
}

void MainWindow::on_pushButton_28_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "(");
}

void MainWindow::on_pushButton_18_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + ")");
}


void MainWindow::on_pushButton_31_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "e");
}


void MainWindow::on_pushButton_11_clicked() {
    QString tmp = ui->lineEdit->text();
    if (tmp.size() > 0) {
        auto iter_begin = tmp.end(), iter_end = tmp.end();
        iter_begin--;
        tmp.erase(iter_begin, iter_end);
    }
    ui->lineEdit->setText(tmp);
}


void MainWindow::on_pushButton_7_clicked() {
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
}


void MainWindow::on_pushButton_6_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "-");
}


void MainWindow::on_pushButton_5_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "+");
}


void MainWindow::on_pushButton_25_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "log(");
}


void MainWindow::on_pushButton_19_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "sin(");
}


void MainWindow::on_pushButton_12_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "cos(");
}


void MainWindow::on_pushButton_26_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "ln(");
}


void MainWindow::on_pushButton_21_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "asin(");
}


void MainWindow::on_pushButton_13_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "acos(");
}


void MainWindow::on_pushButton_14_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "atan(");
}


void MainWindow::on_pushButton_20_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "tan(");
}


void MainWindow::on_pushButton_34_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "sqrt(");
}


void MainWindow::on_pushButton_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "x");
}


void MainWindow::on_pushButton_2_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "1");
}


void MainWindow::on_pushButton_8_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "2");
}


void MainWindow::on_pushButton_9_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "3");
}


void MainWindow::on_pushButton_3_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "4");
}


void MainWindow::on_pushButton_15_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "5");
}


void MainWindow::on_pushButton_16_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "6");
}


void MainWindow::on_pushButton_4_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "7");
}


void MainWindow::on_pushButton_22_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "8");
}


void MainWindow::on_pushButton_23_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "9");
}


void MainWindow::on_pushButton_27_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "0");
}


void MainWindow::on_pushButton_29_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + ".");
}


void MainWindow::on_pushButton_10_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "*");
}


void MainWindow::on_pushButton_17_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "/");
}


void MainWindow::on_pushButton_24_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "mod");
}


void MainWindow::on_pushButton_33_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "^");
}


void MainWindow::on_pushButton_30_clicked() {
    if (!Generic_Conversion()) {
        QByteArray ba = ui->lineEdit_6->text().toLocal8Bit();
        char *str = ba.data();
        if (Controller_->Contains_X() && strlen(str) > 0) {
            double val_x = strtod(str, nullptr);
            Controller_->Set_X_Value(val_x);
        }
        if (Controller_->Contains_X() && strlen(str) == 0) {
            Info_Window("String contains uninitialized x");
        } else {
            double value = Controller_->Get_Digit();
            ui->lineEdit->setText(QString::number(value));
        }
    } else {
        Error_Window();
    }
}


void MainWindow::on_pushButton_32_clicked() {
    if (!Generic_Conversion()) {
        if (Controller_->Contains_X()) {
            Start_Graph_Processing();
        } else {
            Info_Window("String must contain x in order to print graph");
        }
    } else {
        Error_Window();
    }
}
