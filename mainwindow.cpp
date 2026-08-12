#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //1. Basic Layout
    QWidget *topWidget = new QWidget(centralWidget());

    btn = new QPushButton("Click",topWidget);

    label = new QLabel("Status",topWidget);

    h1Layout = new QHBoxLayout(topWidget);
    h1Layout->addWidget(btn);
    h1Layout->addSpacing(200);
    h1Layout->addWidget(label);

    connect(btn,&QPushButton::clicked,label,[this](){
        label->setText("Hello");
    });

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget());

    mainLayout->addWidget(topWidget, 3);   // 30%
    mainLayout->addStretch(7);             // 70%

    //2. TableWidget and TableView
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Name","Age"});
    ui->tableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch
    );

    ui->tableView->setModel(model);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->pushButton_add,&QPushButton::clicked,this,[this,model](){
        QString name = ui->lineEdit_name->text();
        QString ageStr = ui->lineEdit_age->text();

        int row = ui->tableWidget->rowCount();

        bool ok;
        int age = ageStr.toInt(&ok);

        if(!ok)
        {
            QMessageBox::warning(this,"Error","Age should be an integer");
            qDebug()<<age<<" :not a integer";
            return;
        }

        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(name));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(ageStr));

        model->setItem(row,0,new QStandardItem(name));
        model->setItem(row,1,new QStandardItem(ageStr));


        row++;
    });

    connect(ui->pushButton_delete,&QPushButton::clicked,this,[this,model](){
       int delRow = ui->tableWidget->currentRow();
       ui->tableWidget->removeRow(delRow);

       model->removeRow(delRow);
    });

    //3 CSV File
    QString timeStamp = QDateTime::currentDateTime().toString("hh-mm-ss_dd-MM-yyyy");
    QString location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QString filePath = location+"/data_"+timeStamp+".csv";
    qDebug()<<filePath;

    file.setFileName(filePath);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(
               this,
               "Error",
               "Could not open file:\n" + file.errorString()
           );

           qDebug() << "OPEN FAILED:" << file.errorString();
           return;
    }

    out.setDevice(&file);


    //4 QSerialPort
    QSerialPort *serial = new QSerialPort(this);

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for(auto port : ports)
    {
        qDebug()<<port.portName();
        ui->comboBox_ports->addItem(port.portName());
    }

    connect(ui->comboBox_ports,&QComboBox::textActivated,this,[serial](const QString &portName){
        serial->setPortName(portName);
        serial->setBaudRate(115200);
        serial->setParity(QSerialPort::NoParity);
        serial->setDataBits(QSerialPort::Data8);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->setStopBits(QSerialPort::OneStop);

        serial->open(QIODevice::ReadWrite);
    });

    connect(serial,&QSerialPort::readyRead,this,[this,serial](){
        buffer = serial->readAll();
        qDebug()<<buffer.toHex(' ').toUpper();

        out<< buffer <<"\n";
        out.flush();
    });

    QFuture<int> task = QtConcurrent::run([](){

        for(int i=0; i<100000; i++)
        {

        }
        return 100;
    });

    QFutureWatcher<int> *watcher = new QFutureWatcher<int>(this);

    connect(watcher,&QFutureWatcher<int>::finished,this,[watcher](){
        qDebug()<<watcher->result();
    });

    watcher->setFuture(task);

    qDebug()<<200;

}

MainWindow::~MainWindow()
{
    out.flush();
    file.close();
    delete ui;
}

