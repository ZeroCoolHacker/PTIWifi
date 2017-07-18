#include "beaconsniffer.h"
#include <QTimer>
#include <QProcess>
#include <QStringList>
#include <QString>
#include <QDebug>

BeaconSniffer::BeaconSniffer( QObject *parent)
    : QObject(parent)
{
}

void BeaconSniffer::run(const string &interface) {
    iface = QString::fromStdString(interface);
    qDebug() << "Constructing the sniffer";
    SnifferConfiguration config;
    config.set_promisc_mode(true);
    qDebug() << "promisc mode on";
    config.set_filter("type mgt subtype beacon");
    config.set_rfmon(true);
    qDebug() << "monitor mode on";
    Sniffer sniffer(iface.toStdString(), config);
    qDebug() << "sniffer created";
    sniffer.sniff_loop(make_sniffer_handler(this, &BeaconSniffer::callback));
    emit scanStatusChanged();
    QTimer *channelTimer = new QTimer;
    connect(channelTimer, &QTimer::timeout, this, &BeaconSniffer::hopChannel);
    channelTimer->start(300);
}

bool BeaconSniffer::callback(PDU& pdu) {
    if(keepScanning == false) return false;
    // Get the Dot11 layer
    const Dot11Beacon& beacon = pdu.rfind_pdu<Dot11Beacon>();
    // All beacons must have from_ds == to_ds == 0
    if (!beacon.from_ds() && !beacon.to_ds()) {
        // Get the AP address
        address_type addr = beacon.addr2();
        // Look it up in our set
        ssids_type::iterator it = ssids.find(addr);
        if (it == ssids.end()) {
            // First time we encounter this BSSID.
            try {
                /* If no ssid option is set, then Dot11::ssid will throw
                 * a std::runtime_error.
                 */
                string ssid = beacon.ssid();
                // Save it so we don't show it again.
                ssids.insert(addr);
                // Emit the AP "address - ssid".
                AP ap;ap.bssid = addr;ap.ssid = ssid;
                emit APFound(ap);
            }
            catch (runtime_error&) {
                // No ssid, just ignore it.
            }
        }
    }
    return true;
}

void BeaconSniffer::hopChannel()
{
    if(channel == 14)
        setWifiChannel(iface, 0);
    setWifiChannel(iface, channel+1);
    emit channelChanged();
}

void BeaconSniffer::setWifiChannel(QString iface, unsigned short chan){
    QProcess iwconfig;
    QString program = "iwconfig";
    QStringList arguments;
    arguments << iface << "channel" << QString::number(chan);
    iwconfig.execute(program,arguments);
}

