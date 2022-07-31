#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::Error_Window() {
    QMessageBox messageBox;
    messageBox.critical(0, "Error", "Wrong input");
}


void MainWindow::Info_Window(std::string str) {
    QString Qstr = QString::fromUtf8(str);
    QMessageBox::warning(this, "X Value", Qstr);
}


bool MainWindow::Generic_Conversion() {
    QByteArray ba = ui->lineEdit->text().toLocal8Bit();
    char *str = ba.data();
    return Controller_->String_processing(str);
}

void MainWindow::Build_Graph(double xMin, double xMax, double yMin, double yMax) {
    ui->widget->clearGraphs();
    ui->widget->xAxis->setRange(xMin, xMax);
    ui->widget->yAxis->setRange(yMin, yMax);
    QVector<double> x, y;

    for (double i = xMin; i <= xMax; i += 0.01) {
        Controller_->Set_X_Value(i);
        double value = Controller_->Get_Digit();
        x.push_back(i);
        y.push_back(value);
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
}


void MainWindow::Start_Graph_Processing() {
    QByteArray ba = ui->lineEdit_2->text().toLocal8Bit();
    QByteArray ba1 = ui->lineEdit_3->text().toLocal8Bit();
    QByteArray ba2 = ui->lineEdit_4->text().toLocal8Bit();
    QByteArray ba3 = ui->lineEdit_5->text().toLocal8Bit();
    char *str = ba.data();
    char *str1 = ba1.data();
    char *str2 = ba2.data();
    char *str3 = ba3.data();
    if (Controller_->Validate_Func_parameters(str, str1, str2, str3)) {
        double val1 = strtod(str, nullptr);
        double val2 = strtod(str1, nullptr);
        double val3 = strtod(str2, nullptr);
        double val4 = strtod(str3, nullptr);
        if (val1 >= val2 || val3 >= val4 || val1 < -1000000 || val1 > 1000000 || val2 < -1000000
                || val2 > 1000000 || val3 < -1000000 || val3 > 1000000 || val4 < -1000000 || val4 > 1000000)
            Error_Window();
        else
            Build_Graph(val1, val2, val3, val4);
    } else {
        Error_Window();
    }
}
