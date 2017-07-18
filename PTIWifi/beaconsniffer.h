#ifndef BEACONSNIFFER_H
#define BEACONSNIFFER_H

#include <QObject>
#include "tins/tins.h"

using namespace std;
using namespace Tins;

class BeaconSniffer : public QObject{
    Q_OBJECT

public:
    explicit BeaconSniffer(QObject *parent = 0);
    void run(const std::string& iface);
    bool isScanning() {return keepScanning;}

    struct AP {
        Dot11::address_type bssid;
        std::string ssid;
    };
private:
    QString iface;
    typedef Dot11::address_type address_type;
    typedef set<address_type> ssids_type;
    ssids_type ssids;
    bool keepScanning = true; // tells the status of scan
    unsigned short channel = 1;

    bool callback(PDU& pdu);
    void hopChannel(); //changes the channel
    void setWifiChannel(QString iface, unsigned short chan);

signals:
    void APFound(AP ap);
    void scanStatusChanged();
    void channelChanged();
public slots:
    void stopScan() {keepScanning = false; }
};

#endif // BEACONSNIFFER_H
