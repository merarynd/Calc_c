#include "creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_raschet_clicked() {
  double total_pay = 0.0;
  double pereplata = 0.0;
  double month_pay = 0.0;
  if (ui->ann->isChecked() || ui->diff->isChecked()) {
    if (ui->sum->text() != "" && ui->percent->text() != "" &&
        ui->srok->text() != "") {
      double summa_kredita = 0.0, percent = 0.0, srok = 0.0, month_stavka = 0.0;
      summa_kredita = ui->sum->text().toDouble();
      percent = ui->percent->text().toDouble();
      srok = ui->srok->text().toDouble();
      if (ui->ann->isChecked() && summa_kredita > 0 && percent > 0 &&
          srok > 0) {
        month_stavka = percent / 12 / 100;
        month_pay = summa_kredita *
                    (month_stavka +
                     (month_stavka / (pow((1 + month_stavka), srok) - 1)));
        total_pay = month_pay * srok;
        pereplata = total_pay - summa_kredita;
        ui->res_platej->setText(QString::number(month_pay, 'f', 2));
        ui->res_viplata->setText(QString::number(total_pay, 'f', 2));
        ui->res_pereplata->setText(QString::number(pereplata, 'f', 2));
      }
      if (ui->diff->isChecked() && summa_kredita > 0 && percent > 0 &&
          srok > 0) {
        double res = 0.0;
        double month = 0.0;
        month_stavka = percent / 12 / 100;
        for (int i = 0; i < srok; i++) {
          month = summa_kredita / srok +
                  (summa_kredita - (summa_kredita / srok) * i) * month_stavka;
          if (i == 0) res = month;
          total_pay += month;
        }
        pereplata = total_pay - summa_kredita;
        ui->res_platej->setText(QString::number(res, 'f', 2) + "..." +
                                QString::number(month, 'f', 2));
        ui->res_viplata->setText(QString::number(total_pay, 'f', 2));
        ui->res_pereplata->setText(QString::number(pereplata, 'f', 2));
      }
    }
  }
}
