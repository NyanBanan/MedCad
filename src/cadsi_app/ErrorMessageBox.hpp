//
// Created by nyanbanan on 30.04.2024.
//

#ifndef CADSI_ERRORMESSAGEBOX_HPP
#define CADSI_ERRORMESSAGEBOX_HPP

#include <QMessageBox>

class ErrorMessageBox : public QObject{
    Q_OBJECT
public slots:
    void showMessage(const QString& message);
private:
    QMessageBox _msg_box;
};

#endif    //CADSI_ERRORMESSAGEBOX_HPP
