#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_btnForget_clicked();

    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
