#include "bluetoothnamelabel.h"

BluetoothNameLabel::BluetoothNameLabel(QWidget *parent, int x, int y):
    QWidget(parent)
{
//    qDebug() << Q_FUNC_INFO << x << y;

    this->setAutoFillBackground(true);
    this->setStyleSheet("QWidget{border: none;border-radius:2px;}");
    this->setFixedSize(x,y);

    m_label = new QLabel(this);
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setGeometry(2,2,this->width()-3,this->height()-3);
    m_label->setStyleSheet("QLabel{\
                             width: 214px;\
                             height: 20px;\
                             font-size: 14px;\
                             font-family: PingFangSC-Regular, PingFang SC;\
                             font-weight: 400;\
                             color: rgba(0, 0, 0, 0.85);\
                             line-height: 20px;}");

    m_lineedit = new QLineEdit(this);
    m_lineedit->setEchoMode(QLineEdit::Normal);
    connect(m_lineedit,&QLineEdit::editingFinished,this,&BluetoothNameLabel::LineEdit_Input_Complete);
    m_lineedit->setGeometry(2,2,this->width()-3,this->height()-3);
    m_lineedit->setVisible(false);
}

BluetoothNameLabel::~BluetoothNameLabel()
{

}

void BluetoothNameLabel::set_dev_name(const QString &dev_name)
{
    m_label->setText(tr("Can now be found as ")+"\""+dev_name+"\"");
    m_label->update();

    device_name = dev_name;
}

void BluetoothNameLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_label->setVisible(false);

    m_lineedit->setText(device_name);
    m_lineedit->setVisible(true);
    m_lineedit->setFocus();
}

void BluetoothNameLabel::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    if(!m_lineedit->isVisible())
        this->setStyleSheet("QWidget{border:none;border-radius:2px;}");
}

void BluetoothNameLabel::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
//    QPalette palette;
//    palette.setColor(QPalette::Background, QColor(Qt::white));
//    this->setPalette(palette);
//    this->update();
    this->setStyleSheet("QWidget{background-color:white;border:none;border-radius:2px;}");
}

void BluetoothNameLabel::LineEdit_Input_Complete()
{
    emit this->send_adapter_name(m_lineedit->text());
    this->setStyleSheet("QWidget{border:none;border-radius:2px;}");
}

void BluetoothNameLabel::set_label_text(const QString &value)
{
    m_lineedit->setVisible(false);

    m_label->setText(tr("Can now be found as ")+"\""+m_lineedit->text()+"\"");
    m_label->setVisible(true);
}

