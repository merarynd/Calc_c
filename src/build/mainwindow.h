#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

extern "C" {
#include "../s21_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_Credit_clicked();
  void on_pushButton_Depos_clicked();

  void digits_num();
  void operations();
  void operation_func();
  void on_pushButton_dot_clicked();

  void on_pushButton_Bspace_clicked();
  void on_pushButtonAC_clicked();

  void on_pushButton_equal_clicked();

  void on_pushButton_Graph_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
