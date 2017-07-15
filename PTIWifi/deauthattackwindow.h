#ifndef DEAUTHATTACKWINDOW_H
#define DEAUTHATTACKWINDOW_H

#include <QMainWindow>

namespace Ui {
class DeauthAttackWindow;
}

class DeauthAttackWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeauthAttackWindow(QWidget *parent = 0);
    ~DeauthAttackWindow();

private:
    Ui::DeauthAttackWindow *ui;
};

#endif // DEAUTHATTACKWINDOW_H
