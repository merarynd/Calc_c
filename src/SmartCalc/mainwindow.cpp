#include "mainwindow.h"

#include "creditcalc.h"
#include "deposit_calc.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QPixmap pix(":/liga/img/Liga.jpeg");
      int w = ui->label_3->width();
      int h = ui->label_3->height();

      ui->label_3->setPixmap(pix.scaled(w ,h ,Qt::KeepAspectRatio));

  connect(ui->pushButton0, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton1, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton3, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton4, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton5, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton6, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton7, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton8, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton9, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(digits_num()));

  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButtonDegree, SIGNAL(clicked()), this, SLOT(operations()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(operation_func()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(operation_func()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(operation_func()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(operation_func()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(operation_func()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(operation_func()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(operation_func()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(operation_func()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(operation_func()));

  ui->widget->xAxis->setRange(-10, 10);
  ui->widget->yAxis->setRange(-10, 10);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_Credit_clicked() {
  CreditCalc window;
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_Depos_clicked() {
  deposit_calc window;
  window.setModal(true);
  window.exec();
}

void MainWindow::digits_num() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  QString buttonText = button->text();

  if (buttonText == "." && ui->label->text().contains(".")) {
    // Символ "." уже присутствует в тексте метки, поэтому игнорируем нажатие
    return;
  }

  if (ui->label->text() == "0" && buttonText != "0" && buttonText != ".")
    ui->label->setText("");

  if (!(ui->label->text() == "0" && buttonText == "0"))
    ui->label->setText(ui->label->text() + buttonText);
}

void MainWindow::on_pushButton_dot_clicked() {
  if (!(ui->label->text().endsWith('.')))
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::on_pushButton_Bspace_clicked() {
  QString ReturnText = ui->label->text();
  ui->label->setText(ReturnText.left(ReturnText.length() - 1));
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  int flag = 1;
  if (ui->label->text().endsWith("*") || ui->label->text().endsWith("/") ||
      ui->label->text().endsWith("+") || ui->label->text().endsWith("-") ||
      ui->label->text().endsWith("Mod") || ui->label->text().endsWith("^"))
    flag = 0;

  if (button->text() == "*" && flag == 1)
    ui->label->setText(ui->label->text() + button->text());
  if (button->text() == "/" && flag == 1)
    ui->label->setText(ui->label->text() + button->text());
  if (button->text() == "+" && flag == 1)
    ui->label->setText(ui->label->text() + button->text());
  if (button->text() == "-" && flag == 1)
    ui->label->setText(ui->label->text() + button->text());
  if (button->text() == "mod" && flag == 1)
    ui->label->setText(ui->label->text() + button->text());
  if (button->text() == "^" && flag == 1)
    ui->label->setText(ui->label->text() + button->text());
}

void MainWindow::operation_func() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "sin") {
    ui->label->setText(ui->label->text() + "sin(");
  } else if (button->text() == "cos") {
    ui->label->setText(ui->label->text() + "cos(");
  } else if (button->text() == "tan") {
    ui->label->setText(ui->label->text() + "tan(");
  } else if (button->text() == "asin") {
    ui->label->setText(ui->label->text() + "asin(");
  } else if (button->text() == "acos") {
    ui->label->setText(ui->label->text() + "acos(");
  } else if (button->text() == "atan") {
    ui->label->setText(ui->label->text() + "atan(");
  } else if (button->text() == "log") {
    ui->label->setText(ui->label->text() + "log(");
  } else if (button->text() == "ln") {
    ui->label->setText(ui->label->text() + "ln(");
  } else if (button->text() == "sqrt") {
    ui->label->setText(ui->label->text() + "sqrt(");
  }
}

void MainWindow::on_pushButton_equal_clicked() {
  int error = 0;
  double res = 0.0;
  double number_x = 0.0;
  if (ui->Enter_X->text() != "Enter x") {
    number_x = ui->Enter_X->text().toDouble();
  }
  std::string str1 = ui->label->text().toStdString();
  const char *str = str1.c_str();

  res = s21_smart_calc((char *)str, &error, number_x);
  if (error == 0) ui->label->setText(QString::number(res, 'g', 15));
  if (error == 1) ui->label->setText("can't divide by zero");
  if (error == 2) ui->label->setText("Error");
}

void MainWindow::on_pushButtonAC_clicked() {
  ui->label->setText("");
  ui->Enter_X->setText("");
}

void MainWindow::on_pushButton_Graph_clicked() {
  ui->widget->clearGraphs();

  std::string str1 = ui->label->text().toStdString();
  const char *str = str1.c_str();

  double x_begin = ui->line_minusX->text().toDouble();
  double x_end = ui->line_plusX->text().toDouble();
  double y_begin = ui->line_minusY->text().toDouble();
  double y_end = ui->line_plusY->text().toDouble();

  ui->widget->xAxis->setRange(x_begin, x_end);
  ui->widget->yAxis->setRange(y_begin, y_end);

  if (x_begin < x_end && y_begin < y_end) {
    double h = 0.01;
    int N = (x_end - x_begin) / h + 2;
    QVector<double> x(N), y(N);
    int i = 0;
    int error = 0;
    float X = 0.0;
    for (X = x_begin; X <= x_end; X += h) {
      double res = 0.0;
      res = s21_smart_calc((char *)str, &error, X);
      if (error == 0) {
        x[i] = X;
        y[i] = res;
        i++;
      }
    }
    if (error == 0) {
      ui->widget->addGraph();
      ui->widget->graph(0)->setData(x, y);

      ui->widget->graph(0)->setPen(QColor(33, 8, 150));
      ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
      ui->widget->graph(0)->setScatterStyle(
          QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
      ui->widget->replot();

      x.clear();
      y.clear();
    } else
      ui->label->setText("error");
  }
}
