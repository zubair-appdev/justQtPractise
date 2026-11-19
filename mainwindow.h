#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QMessageBox>

#include <QDebug>

#include <QStandardItemModel>
#include <sensortablemodel.h>

#include <QSerialPort>
#include <QSerialPortInfo>

#include <QFile>
#include <QStandardPaths>
#include <QDateTime>

#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_loadDataFromCSV_clicked();

    void on_pushButton_deleteRow_clicked();

    void on_pushButton_customData_clicked();

private:
    Ui::MainWindow *ui;

    QPushButton *btn;
    QLabel *label;

    QHBoxLayout *h1Layout;

    QSerialPort globalSerial;

    QByteArray buffer;

    QFile file;
    QTextStream out;

    QStandardItemModel *model = nullptr;

    SensorTableModel *modelC  = nullptr;

};
#endif // MAINWINDOW_H
