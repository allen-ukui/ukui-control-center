#ifndef DEVICEINFOITEM_H
#define DEVICEINFOITEM_H

#include "config.h"


#include <KF5/BluezQt/bluezqt/device.h>

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QPixmap>
#include <QString>
#include <QIcon>
#include <QDebug>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QTimer>
#include <QString>

class DeviceInfoItem : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceInfoItem(QWidget *parent = nullptr);
    ~DeviceInfoItem();
    void initInfoPage(DEVICE_TYPE icon_type = DEVICE_TYPE::OTHER,QString d_name = "",DEVICE_STATUS status = DEVICE_STATUS::NOT,BluezQt::DevicePtr device = nullptr);
    QString get_dev_name();
    void changeDevStatus(bool);
    void setDevConnectedIcon(bool);
protected:
    void resizeEvent(QResizeEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
signals:
    void sendConnectDevice(QString);
    void sendDisconnectDeviceAddress(QString);
    void sendDeleteDeviceAddress(QString);
    void send_this_item_is_pair();
private slots:
    void onClick_Connect_Btn(bool);
    void onClick_Disconnect_Btn(bool);
    void onClick_Delete_Btn(bool);
    void updateDeviceStatus(DEVICE_STATUS status = DEVICE_STATUS::NOT);
private:
    QWidget *parent_widget;
    QLabel *device_icon;
    QLabel *device_name;
    QLabel *device_status;

    BluezQt::DevicePtr device_item;

    QPushButton *connect_btn;
    QPushButton *disconnect_btn;
    QPushButton *del_btn;

    DEVICE_STATUS d_status;

    QFrame *info_page;
    QTimer *icon_timer;
    int i = 7;
};

#endif // DEVICEINFOITEM_H
