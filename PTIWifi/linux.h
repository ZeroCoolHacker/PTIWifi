#ifndef LINUX_H
#define LINUX_H

#include <QProcess>
#include <QString>
#include <QStringList>

void setWifiChannel(QString iface, unsigned short chan){
    QProcess iwconfig;
    QString program = "iwconfig";
    QStringList arguments;
    arguments << iface << "channel" << QString::number(chan);
    iwconfig.execute(program,arguments);
}

#endif // LINUX_H
