#include "interfacedialog.h"
#include "ui_interfacedialog.h"
#include <unistd.h>
#include <QMessageBox>

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
    IFaceVec = Tins::NetworkInterface::all();
    if(IFaceVec.size() == 0){
        ui->status_label->setText("No Interfaces found!");
        return;
    }
    //otherwise populate the combobox
    QStringList ifaceList;
    for(Tins::NetworkInterface iface : IFaceVec){
        ifaceList.append(QString::fromStdString(iface.name()));
    }
    interfaceComboBoxModel->setStringList(ifaceList);
    ui->Interface_comboBox->setModel(interfaceComboBoxModel);
    ui->status_label->setText("Interfaces loaded!");
}
