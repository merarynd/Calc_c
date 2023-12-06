#include "deposit_calc.h"

#include "ui_deposit_calc.h"

deposit_calc::deposit_calc(QWidget *parent)
    : QDialog(parent), ui(new Ui::deposit_calc) {
  ui->setupUi(this);
}

deposit_calc::~deposit_calc() { delete ui; }

void deposit_calc::on_rashet_clicked() {
  double sum = ui->sum_vklad->text().toDouble();
  double srok = ui->srok->text().toDouble();
  double stavka = ui->stavka->text().toDouble();
  double nalog = ui->nalog->text().toDouble();

  double sum_popolnenie = ui->sum_popolnenie->text().toDouble();
  double sum_sniatie = ui->sum_sniatie->text().toDouble();

  int month_popolnenie = ui->month_popolnenie->text().toInt();
  int month_sniatie = ui->month_sniatie->text().toInt();

  int capital = check_cap();
  int period_viplat = period_to_pay();
  double proc = 0.0;
  double sum_nalog = 0.0;
  double proc_month = 0.0;
  double proc_year = 0.0;
  double ostatok_proc = 0.0;
  int count_years = 0;
  int div = div_rate(&period_viplat, &srok);  // деление проц
  if (sum > 0 && srok > 0 && stavka > 0 && nalog > 0) {
    for (int i = 1; i <= srok; i++) {
      proc_month = sum * (stavka / 100 / div);
      proc += proc_month;
      if (month_popolnenie > 0 && sum_popolnenie > 0) {
        sum += sum_popolnenie;
        month_popolnenie--;
      }
      if (month_sniatie > 0 && sum_sniatie > 0) {
        sum -= month_sniatie;
        month_sniatie--;
      }
      if (capital) sum += proc_month;
      annual_tax_calc(period_viplat, proc, &count_years, i, &proc_year);
    }
    sum_nalog = tax_calc(proc_year, proc, ostatok_proc, count_years, nalog);
    ui->res_full->setText(QString::number(sum + proc, 'f', 2));
    ui->res_proc->setText(QString::number(proc, 'f', 2));
    ui->res_sum->setText(QString::number(sum_nalog, 'f', 2));
  }
}

int deposit_calc::check_cap() {
  int res = 0;
  if (ui->kapitalization->isChecked()) res = 1;
  return res;
}

int deposit_calc::period_to_pay() {
  int count_paym = 0;
  int count = ui->period->currentIndex();
  if (count == 0)
    count_paym = 1;
  else if (count == 1)
    count_paym = 2;
  else if (count == 2)
    count_paym = 3;
  return count_paym;
}

int deposit_calc::div_rate(int *period_viplat, double *deposit_term) {
  int div_rate = 0;
  if (*period_viplat == 1) {
    (*deposit_term) *= 30.45;
    div_rate = 365;
  } else if (*period_viplat == 2) {
    (*deposit_term) *= 4.33;
    div_rate = 52;
  } else if (*period_viplat == 3) {
    (*deposit_term) *= 1;
    div_rate = 12;
  }
  return div_rate;
}

void deposit_calc::annual_tax_calc(int period_viplat, double accrued_interest,
                                   int *count_tax, int i, double *tax_buffer) {
  if (i % 365 == 0 && period_viplat == 1) {
    *tax_buffer = *tax_buffer == 0 ? accrued_interest : *tax_buffer;
    (*count_tax)++;
  } else if (i % 52 == 0 && period_viplat == 2) {
    *tax_buffer = *tax_buffer == 0 ? accrued_interest : *tax_buffer;
    (*count_tax)++;
  } else if (i % 12 == 0 && period_viplat == 3) {
    *tax_buffer = *tax_buffer == 0 ? accrued_interest : *tax_buffer;
    (*count_tax)++;
  }
}

double deposit_calc::tax_calc(double tax_buffer, double accrued_interest,
                              double interest_edge, int count_tax,
                              double nalog_stavka) {

//    tax_buffer - буфер налога.
//    accrued_interest - накопленные проценты.
//    interest_edge - предельное значение процентов.
//    count_tax - количество налоговых ставок.
//    nalog_stavka - ставка налога.
  double tax_amount = 0;
  if (tax_buffer == 0) {
    if (accrued_interest > 75000)
      tax_amount = (accrued_interest - 75000) * (nalog_stavka / 100);
  } else {
    interest_edge = accrued_interest - (tax_buffer * count_tax);
    if (interest_edge > 75000)
      interest_edge = (interest_edge - 75000) * (nalog_stavka / 100);
    else
      interest_edge = 0;
    if (tax_buffer > 75000)
      tax_amount = (tax_buffer - 75000) * (nalog_stavka / 100) * count_tax +
                   interest_edge;
  }
  return tax_amount;
}
