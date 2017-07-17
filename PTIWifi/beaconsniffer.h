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
    void run(const string& iface);
    struct AP {
        Dot11::address_type bssid;
        std::string ssid;
    };
private:
    typedef Dot11::address_type address_type;
    typedef set<address_type> ssids_type;

    bool callback(PDU& pdu);

    ssids_type ssids;


    bool keepScanning = true;
signals:
    void APFound(AP ap);

public slots:
    void stopScan() {keepScanning = false; }
};

#endif // BEACONSNIFFER_H
