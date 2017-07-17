#ifndef DEAUTHATTACKWINDOW_H
#define DEAUTHATTACKWINDOW_H

#include <QMainWindow>
#include "beaconsniffer.h"
#include <vector>
#include <QStringListModel>
#include <string>

using namespace std;
using namespace Tins;

namespace Ui {
class DeauthAttackWindow;
}

class DeauthAttackWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeauthAttackWindow( std::string interface, QWidget *parent = 0);
    ~DeauthAttackWindow();

private:
    Ui::DeauthAttackWindow *ui;
    BeaconSniffer sniffer;
    QStringList ssidList;
    std::string iface;
    QStringListModel* apListModel;
    vector<BeaconSniffer::AP> vecAP;


    void setupConnections();
    void setupAPListModel();

public slots:
    void getAP(BeaconSniffer::AP ap);
};

#endif // DEAUTHATTACKWINDOW_H
