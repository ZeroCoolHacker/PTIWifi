#include "deauthattackwindow.h"
#include "ui_deauthattackwindow.h"
#include <QDebug>

DeauthAttackWindow::DeauthAttackWindow(string interface, QWidget *parent) :
    QMainWindow(parent),iface(interface),
    ui(new Ui::DeauthAttackWindow)
{
    ui->setupUi(this);
    qDebug() << "Attack window constructed" << QString::fromStdString(interface);
    apListModel = new QStringListModel(this);
    setupConnections();
    qDebug() << "Running sniffer...";
    sniffer.run(iface);
}

DeauthAttackWindow::~DeauthAttackWindow()
{
    delete ui;
}

void DeauthAttackWindow::setupConnections()
{
    qDebug() << "Setting up connections";
    connect(ui->stopScan_pushButton, &QPushButton::clicked, &sniffer, &BeaconSniffer::stopScan);
    connect(&sniffer, &BeaconSniffer::APFound, this, &DeauthAttackWindow::getAP);
    connect(&sniffer, &BeaconSniffer::scanStatusChanged, this, &DeauthAttackWindow::showScanStatus);
}

void DeauthAttackWindow::setupAPListModel()
{
    apListModel->setStringList(ssidList);
    ui->AP_listView->setModel(apListModel);
}

void DeauthAttackWindow::getAP(BeaconSniffer::AP ap)
{
    vecAP.push_back(ap);
    ssidList << QString::fromStdString(ap.ssid);
    setupAPListModel();
}

void DeauthAttackWindow::showScanStatus()
{
    if(sniffer.isScanning())
        ui->status_label->setText("Scanning...");
    ui->status_label->setText("Stopped Scanning");
}
