#include "deauthattackwindow.h"
#include "ui_deauthattackwindow.h"

DeauthAttackWindow::DeauthAttackWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeauthAttackWindow)
{
    ui->setupUi(this);
}

DeauthAttackWindow::~DeauthAttackWindow()
{
    delete ui;
}
