/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *com_groupbox;
    QPushButton *com_button;
    QComboBox *com_combobox;
    QLabel *comstate_label;
    QLabel *service_message;
    QPushButton *com_refresh_button;
    QPushButton *echo_button;
    QLineEdit *uartMessage;
    QPushButton *sendButton;
    QLabel *label;
    QLabel *service_message_3;
    QGroupBox *com_groupbox_2;
    QPushButton *setSocketButton;
    QLineEdit *ip4LineEdit_3;
    QLabel *ip4label;
    QLabel *dot_1;
    QLineEdit *ip4LineEdit_2;
    QLineEdit *ip4LineEdit_1;
    QLabel *dot_2;
    QLineEdit *ip4LineEdit_0;
    QLabel *dot_3;
    QLabel *portUDPLabel;
    QLineEdit *udpPortLineEdit;
    QPushButton *udpSendButton;
    QLabel *udpDataLabel;
    QLabel *recMessageLabel_1;
    QLineEdit *udpDataLineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        com_groupbox = new QGroupBox(centralwidget);
        com_groupbox->setObjectName(QString::fromUtf8("com_groupbox"));
        com_groupbox->setGeometry(QRect(10, 10, 681, 121));
        com_button = new QPushButton(com_groupbox);
        com_button->setObjectName(QString::fromUtf8("com_button"));
        com_button->setGeometry(QRect(100, 30, 91, 21));
        com_combobox = new QComboBox(com_groupbox);
        com_combobox->setObjectName(QString::fromUtf8("com_combobox"));
        com_combobox->setGeometry(QRect(10, 30, 81, 22));
        comstate_label = new QLabel(com_groupbox);
        comstate_label->setObjectName(QString::fromUtf8("comstate_label"));
        comstate_label->setGeometry(QRect(10, 60, 181, 16));
        comstate_label->setAlignment(Qt::AlignCenter);
        service_message = new QLabel(com_groupbox);
        service_message->setObjectName(QString::fromUtf8("service_message"));
        service_message->setGeometry(QRect(200, 80, 71, 21));
        service_message->setAlignment(Qt::AlignCenter);
        com_refresh_button = new QPushButton(com_groupbox);
        com_refresh_button->setObjectName(QString::fromUtf8("com_refresh_button"));
        com_refresh_button->setGeometry(QRect(10, 80, 181, 21));
        echo_button = new QPushButton(com_groupbox);
        echo_button->setObjectName(QString::fromUtf8("echo_button"));
        echo_button->setGeometry(QRect(210, 30, 51, 21));
        uartMessage = new QLineEdit(com_groupbox);
        uartMessage->setObjectName(QString::fromUtf8("uartMessage"));
        uartMessage->setGeometry(QRect(290, 30, 181, 25));
        sendButton = new QPushButton(com_groupbox);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(290, 80, 181, 21));
        label = new QLabel(com_groupbox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(500, 30, 161, 31));
        service_message_3 = new QLabel(com_groupbox);
        service_message_3->setObjectName(QString::fromUtf8("service_message_3"));
        service_message_3->setGeometry(QRect(550, 80, 71, 21));
        service_message_3->setAlignment(Qt::AlignCenter);
        com_groupbox_2 = new QGroupBox(centralwidget);
        com_groupbox_2->setObjectName(QString::fromUtf8("com_groupbox_2"));
        com_groupbox_2->setGeometry(QRect(10, 150, 681, 141));
        setSocketButton = new QPushButton(com_groupbox_2);
        setSocketButton->setObjectName(QString::fromUtf8("setSocketButton"));
        setSocketButton->setGeometry(QRect(20, 100, 231, 21));
        ip4LineEdit_3 = new QLineEdit(com_groupbox_2);
        ip4LineEdit_3->setObjectName(QString::fromUtf8("ip4LineEdit_3"));
        ip4LineEdit_3->setGeometry(QRect(10, 60, 31, 25));
        ip4label = new QLabel(com_groupbox_2);
        ip4label->setObjectName(QString::fromUtf8("ip4label"));
        ip4label->setGeometry(QRect(20, 30, 161, 20));
        ip4label->setAlignment(Qt::AlignCenter);
        dot_1 = new QLabel(com_groupbox_2);
        dot_1->setObjectName(QString::fromUtf8("dot_1"));
        dot_1->setGeometry(QRect(40, 60, 21, 31));
        dot_1->setAlignment(Qt::AlignCenter);
        ip4LineEdit_2 = new QLineEdit(com_groupbox_2);
        ip4LineEdit_2->setObjectName(QString::fromUtf8("ip4LineEdit_2"));
        ip4LineEdit_2->setGeometry(QRect(60, 60, 31, 25));
        ip4LineEdit_1 = new QLineEdit(com_groupbox_2);
        ip4LineEdit_1->setObjectName(QString::fromUtf8("ip4LineEdit_1"));
        ip4LineEdit_1->setGeometry(QRect(110, 60, 31, 25));
        dot_2 = new QLabel(com_groupbox_2);
        dot_2->setObjectName(QString::fromUtf8("dot_2"));
        dot_2->setGeometry(QRect(90, 60, 21, 31));
        dot_2->setAlignment(Qt::AlignCenter);
        ip4LineEdit_0 = new QLineEdit(com_groupbox_2);
        ip4LineEdit_0->setObjectName(QString::fromUtf8("ip4LineEdit_0"));
        ip4LineEdit_0->setGeometry(QRect(160, 60, 31, 25));
        dot_3 = new QLabel(com_groupbox_2);
        dot_3->setObjectName(QString::fromUtf8("dot_3"));
        dot_3->setGeometry(QRect(140, 60, 21, 31));
        dot_3->setAlignment(Qt::AlignCenter);
        portUDPLabel = new QLabel(com_groupbox_2);
        portUDPLabel->setObjectName(QString::fromUtf8("portUDPLabel"));
        portUDPLabel->setGeometry(QRect(220, 30, 51, 20));
        portUDPLabel->setAlignment(Qt::AlignCenter);
        udpPortLineEdit = new QLineEdit(com_groupbox_2);
        udpPortLineEdit->setObjectName(QString::fromUtf8("udpPortLineEdit"));
        udpPortLineEdit->setGeometry(QRect(230, 60, 31, 25));
        udpSendButton = new QPushButton(com_groupbox_2);
        udpSendButton->setObjectName(QString::fromUtf8("udpSendButton"));
        udpSendButton->setGeometry(QRect(290, 100, 181, 21));
        udpDataLabel = new QLabel(com_groupbox_2);
        udpDataLabel->setObjectName(QString::fromUtf8("udpDataLabel"));
        udpDataLabel->setGeometry(QRect(490, 60, 171, 31));
        udpDataLabel->setAlignment(Qt::AlignCenter);
        recMessageLabel_1 = new QLabel(com_groupbox_2);
        recMessageLabel_1->setObjectName(QString::fromUtf8("recMessageLabel_1"));
        recMessageLabel_1->setGeometry(QRect(490, 100, 171, 21));
        recMessageLabel_1->setAlignment(Qt::AlignCenter);
        udpDataLineEdit = new QLineEdit(com_groupbox_2);
        udpDataLineEdit->setObjectName(QString::fromUtf8("udpDataLineEdit"));
        udpDataLineEdit->setGeometry(QRect(290, 60, 181, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        com_groupbox->setTitle(QCoreApplication::translate("MainWindow", "COM Port", nullptr));
        com_button->setText(QCoreApplication::translate("MainWindow", "Open port", nullptr));
        comstate_label->setText(QCoreApplication::translate("MainWindow", "Closed", nullptr));
        service_message->setText(QCoreApplication::translate("MainWindow", "Empty", nullptr));
        com_refresh_button->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        echo_button->setText(QCoreApplication::translate("MainWindow", "Echo", nullptr));
        uartMessage->setText(QString());
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "blank", nullptr));
        service_message_3->setText(QCoreApplication::translate("MainWindow", "Received", nullptr));
        com_groupbox_2->setTitle(QCoreApplication::translate("MainWindow", "UDP Parameters", nullptr));
        setSocketButton->setText(QCoreApplication::translate("MainWindow", "Set socket", nullptr));
        ip4LineEdit_3->setText(QString());
        ip4label->setText(QCoreApplication::translate("MainWindow", "IP4 adress", nullptr));
        dot_1->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        ip4LineEdit_2->setText(QString());
        ip4LineEdit_1->setText(QString());
        dot_2->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        ip4LineEdit_0->setText(QString());
        dot_3->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        portUDPLabel->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        udpPortLineEdit->setText(QString());
        udpSendButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        udpDataLabel->setText(QCoreApplication::translate("MainWindow", "blank", nullptr));
        recMessageLabel_1->setText(QCoreApplication::translate("MainWindow", "Received", nullptr));
        udpDataLineEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
