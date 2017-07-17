#include "deauthattackwindow.h"
#include "ui_deauthattackwindow.h"

DeauthAttackWindow::DeauthAttackWindow(string interface, QWidget *parent) :
    QMainWindow(parent),iface(interface),
    ui(new Ui::DeauthAttackWindow)
{
    ui->setupUi(this);
    apListModel = new QStringListModel(this);
    setupConnections();
    sniffer.run(iface);
}

DeauthAttackWindow::~DeauthAttackWindow()
{
    delete ui;
}

void DeauthAttackWindow::setupConnections()
{
    connect(ui->stopScan_pushButton, &QPushButton::clicked, &sniffer, &BeaconSniffer::stopScan);
    connect(&sniffer, &BeaconSniffer::APFound, this, &DeauthAttackWindow::getAP);
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
