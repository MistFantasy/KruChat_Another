#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
private:
  QString * user;
  int * SyncMethod;

public:
    QString getUser();
    void setUser(QString str);
    explicit Dialog(QString * user, int * SyncMethod,
                    QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
