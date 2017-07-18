#include "interfacedialog.h"
#include "ui_interfacedialog.h"
#include <unistd.h>
#include <QMessageBox>
#include <QDebug>
#include "deauthattackwindow.h"

InterfaceDialog::InterfaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterfaceDialog)
{
    ui->setupUi(this);
    //check root
    if(getuid()){
        QMessageBox::critical(this, "Root Required",
                              "Run this program as root!.");
        exit(101);
    }

    //load interfaces
    initializeModels();//initializes all the model variables once
    populateInterfaceCombobox();
}

InterfaceDialog::~InterfaceDialog()
{
    delete ui;
}

void InterfaceDialog::initializeModels()
{
    interfaceComboBoxModel = new QStringListModel(this);
}

//set the model of Interface_combobox
void InterfaceDialog::populateInterfaceCombobox()
{
    ui->status_label->setText("Scanning for interfaces...");
    qDebug() << "Scanning for interfaces...";
    IFaceVec = Tins::NetworkInterface::all();
    qDebug() << "Scan Complete";
    if(IFaceVec.size() == 0){
        ui->status_label->setText("No Interfaces found!");
        return;
    }
    //otherwise populate the combobox
    QStringList ifaceList;
    for(Tins::NetworkInterface iface : IFaceVec){
        qDebug() << QString::fromStdString(iface.name());
        ifaceList.append(QString::fromStdString(iface.name()));
    }
    interfaceComboBoxModel->setStringList(ifaceList);
    ui->Interface_comboBox->setModel(interfaceComboBoxModel);
    ui->status_label->setText("Interfaces loaded!");

    //select default interface
    try{
        qDebug() << "getting default interface";
        QString default_iface = QString::fromStdString(Tins::NetworkInterface::default_interface().name());
        ui->Interface_comboBox->setCurrentText(default_iface);
    } catch(Tins::invalid_interface& a){
        qDebug() << a.what();
    }


}

void InterfaceDialog::on_go_pushButton_clicked()
{
    if(ui->Interface_comboBox->currentText().isEmpty()) return;
    qDebug() << "Creating Attack Dialog";
    DeauthAttackWindow * window = new DeauthAttackWindow(ui->Interface_comboBox->currentText().toStdString());
    qDebug() << "Created the window instance";
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->showMaximized();

    this->hide();
}
