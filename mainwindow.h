#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QFile>
#include <QTimer>
#include <QByteArray>

#define	SYNCHRO                                 0x02
#define UART_ADDR                               0x0A
#define SERVICE_BITS_LEN                        0x06

#define ECHO                                    0x00
#define SUPPLY_CTRL                             0x01
#define ATT_CTRL                                0x02
#define DAC_REVISION                            0x03
#define	DAC_CTRL                                0x04
#define POWER_AMP_EN                            0x05
#define UM78_SUPPLY_CTRL                        0x06
#define UM78_AMP_EN                             0x07
#define UM78_DAC_CTRL                           0x08
#define STROBE_CTRL                             0x09
#define GET_POWER                               0x0A
#define CAL_POWER                               0x0B
#define COMP_DAC                                0x0C
#define STOP_CAL                                0x0D

#define ON                                      0x01
#define OFF                                     0x00

typedef union{
    uint16_t    istd;
    uint8_t 	cstd[2];
}std_union;

typedef union{
    uint32_t 	listd;
    uint16_t 	istd[2];
    uint8_t 	cstd[4];
}long_std_union;

typedef union{
    uint64_t 	llistd;
    uint32_t 	listd[2];
    uint16_t 	istd[4];
    uint8_t 	cstd[8];
}long_long_std_union;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QSerialPort             *COM;
    QFile                   *File;
    QTimer                  *timer_echo;
    uint8_t                 com_mode;
    uint8_t                 uart_command;
    QByteArray              ba;
    char                    CRC = 0;

private slots:
    void getEcho();
    void connectCOM();
    void readData();
    void on_com_refresh_button_clicked();
    void timer_echo_timeout();
};
#endif // MAINWINDOW_H
