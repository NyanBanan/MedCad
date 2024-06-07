//
// Created by nyanbanan on 30.04.2024.
//

#include "ErrorMessageBox.hpp"

void ErrorMessageBox::showMessage(const QString& message) {
    _msg_box.setText(message);
    _msg_box.exec();
}
