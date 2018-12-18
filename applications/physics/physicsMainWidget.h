#ifndef PHYSICSMAINWIDGET_H
#define PHYSICSMAINWIDGET_H

#include <QWidget>
#include "clientsender.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <linux/joystick.h>
#include <fcntl.h>

namespace Ui {
class PhysicsMainWidget;
}

class PhysicsMainWidget : public QWidget
{
    Q_OBJECT
 public:
    explicit PhysicsMainWidget(QWidget *parent = 0);
    QSerialPort serialPort;
    ~PhysicsMainWidget();
     QByteArray *FlyCommandWriteData;
     QByteArray GetDataFromStics();
     int Current_mode=0;
     bool RealModeActive = false;
     bool VirtualModeActive = false;
     struct axis_state {       short x, y;    };

     void disconnect_from_copter();
public slots:
    void keepAlive();
private slots:
    void yawChange(int i);
    void rollChange(int i);
    void pitchChange(int i);
    void throttleChange(int i);
    void StartJoyStickMode();
    void Bind();
    void on_pushButton_released();
    void SendJoyValues();
    void StartRealMode();
    void BindToRealDrone();
    void STOP();
    void on_pushButton_2_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::PhysicsMainWidget *ui;
    int yaw_value;
    int roll_value;
    int pitch_value;
    int throttle_value;
    int throttle_value_from_JS;
    int fifth_CH;
    int sixth_CH;
    int seventh_CH;
    int eighth_CH;
    int mid_Throttle=1350;

    int counter;
    int sign(int val);
    clock_t start_time;
    void ShowValues( );
    void FrameValuesUpdate();
    bool created=false;
    bool bind=false;
    bool Arming=false;
    bool startFly=false;   //to set mid throttle after arming

    bool rt_pressed=false;
    bool lt_pressed=false;

    void SendOurValues(std::vector<uint8_t> OurValues);
    void usial_buttons(js_event event);
    void usial_sticks(js_event event);

    void inertial_buttons(js_event event);
    void inertial_sticks(js_event event);

    void casual_buttons(js_event event);
    void casual_sticks(js_event event);

    struct axis_state axes[3] ;

    void Start_arming(bool pressed);
    ClientSender VirtualSender;

    //size_t get_button_count(int fd);
};

#endif // PHYSICSMAINWIDGET_H