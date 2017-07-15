#ifndef INTERFACEDIALOG_H
#define INTERFACEDIALOG_H

#include <QDialog>
#include <vector>
#include "tins/tins.h"
#include "tins/network_interface.h"
#include <QStringListModel>

using namespace std;
using namespace Tins;

namespace Ui {
class InterfaceDialog;
}

class InterfaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceDialog(QWidget *parent = 0);
    ~InterfaceDialog();

private slots:
    void on_go_pushButton_clicked();

private:
    Ui::InterfaceDialog *ui;
    QStringListModel *interfaceComboBoxModel;
    //network variables
    vector<Tins::NetworkInterface> IFaceVec;//holds the interfaces
    //private functions
    void initializeModels();
    void populateInterfaceCombobox();
};

#endif // INTERFACEDIALOG_H
