#include "ShowQRCode.h"
#include<proxy.h>
#include <iostream>
#include "StartTaskUi.h"
#include "TaskUi.h"
#include<qdebug.h>
#include"service.h"
using namespace std;

CShowQRCode::CShowQRCode(QWidget* parent)
	: QWidget(parent)
{
	this->setWindowTitle(QString::fromLocal8Bit("ɨ���ά��"));
	resize(600 + 30, 700 + 30);

	auto layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);

	// ����������
	mainWidget = new QWidget;
	mainWidget->resize(400, 500);
	layout->addWidget(mainWidget);

	// ���� QLabel ����ʾͼƬ
	imagelabel = new QLabel;
	AttentionLabel = new QLabel;
	Label1 = new QLabel;
	Label2 = new QLabel;

	// ������ť
	commitButton = new QPushButton(QString::fromLocal8Bit("ȷ��"));
	commitButton->setFixedSize(100, 30);

	// ����������Ϣ
	AttentionLabel->setText(QString::fromLocal8Bit("ע�⣺"));
	Label1->setText(QString::fromLocal8Bit("1.��ʹ���ֻ�QQɨ���ά�벢ȷ�ϣ�"));
	Label2->setText(QString::fromLocal8Bit("2.��������ϵ�ȷ����ť"));



	// ������ʽ
	mainWidget->setStyleSheet(
		"QWidget {"
		"background-color: #f0f0f0;"
		"}"
	); // ���ñ�����ɫΪǳ��ɫ

	AttentionLabel->setStyleSheet(
		"QLabel {"
		"font-weight: bold;"
		"color: #007bff;" // ����������ɫΪ��ɫ
		"}"
	);

	commitButton->setStyleSheet(
		// ��ͨ״̬�µ���ʽ
		"QPushButton {"
		"font-family: \"Microsoft YaHei\";" // ����Ϊ΢���ź�
		"font-style: normal;" // ������Ϊ��ͨ
		"font-weight: 400;" // �����ϸΪ����
		"font-size: 14px;" // �����СΪ14px
		"text-decoration: none;" // �ı�װ��Ϊ��
		"color: #ffffff;" // �ı���ɫΪ��ɫ
		"border: none;" // ȥ����ť�߿�
		"border-radius: 4px;" // ���ð�ť�߿��Բ�ǰ뾶Ϊ4px
		"background-color: #2074f3;" // ���ð�ť����ɫΪ��ɫ
		"}"

		// �����ͣʱ����ʽ
		"QPushButton:hover {"
		"background-color: #629df7;" // ���������ͣʱ��ť����ɫΪ����ɫ
		"}"

		// ��ť����ʱ����ʽ
		"QPushButton:pressed {"
		"background-color: #1a5dc2;" // ���ð�ť����ʱ����ɫΪ�������ɫ
		"}"
	);


	// ��ֱ����
	mainLayout = new QVBoxLayout;
	mainLayout->setAlignment(Qt::AlignCenter); // �������������Ķ���

	// ����ˮƽ�������ھ��а�ť
	buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch(); // ��������ʹ��ť����
	buttonLayout->addWidget(commitButton);
	buttonLayout->addStretch(); // ��������ʹ��ť����

	// ��ӿؼ���������
	mainLayout->addWidget(imagelabel);
	mainLayout->addWidget(AttentionLabel);
	mainLayout->addWidget(Label1);
	mainLayout->addWidget(Label2);
	mainLayout->addSpacing(20); // �ڴ�ֱ�����У���Ӹ߶�Ϊ20�ļ��
	mainLayout->addLayout(buttonLayout);

	// ���ñ߾�ͼ��
	mainLayout->setContentsMargins(30, 30, 30, 30); // ���ñ߾�
	mainLayout->setSpacing(20); // ���ò����еļ��

	// ������������Ϊ�����ڵĲ���
	mainWidget->setLayout(mainLayout);

	// ���Ӱ�ť����ź���ۺ���
	connect(commitButton, &QPushButton::clicked, this, &CShowQRCode::Popup_Scan);
	connect(commitButton, &QPushButton::clicked, this, &QWidget::close);

	connect(&Service::getInstance(), &Service::QRCODE_CONFIRM_MSG_ACK_Signal, this, &CShowQRCode::QRCODE_CONFIRM_MSG_ACK_callback);
}

CShowQRCode::~CShowQRCode()
{}

// ɨ���ά��ۺ���
void CShowQRCode::Popup_Scan()
{
	std::string s = "";
	Proxy::getInstance().send(MsgType::QRCODE_CONFIRM_MSG, s);
}

void CShowQRCode::showqrcode(std::string image_path)
{
	// ���� QPixmap ���󲢼���ͼƬ
	QrCode = new QPixmap(image_path.c_str());
	// ����Ƿ�ɹ�����ͼƬ
	if (QrCode->isNull()) {
		LOG_ERROR("�޷�����ͼƬ:%s!", image_path.c_str());
		return;
	}

	// ����ͼƬ��С����Ӧ�߿��С
	QSize imageSize(300, 300); // ����Ŀ���Ⱥ͸߶�
	*QrCode = QrCode->scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

	// �� QPixmap ��������Ϊ QLabel ������
	imagelabel->setPixmap(*QrCode);
	//show();open();//exec()
	this->show();
}

void CShowQRCode::QRCODE_CONFIRM_MSG_ACK_callback(QString qloginres)
{
	/*QMessageBox::information(this, " ", QString::fromLocal8Bit("��ȡ�ɹ�!"), QString::fromLocal8Bit("ȷ��"));
	CStartTaskUi StarTtask;
	StarTtask.exec();
	this->accept();*/
	std::string loginres = qloginres.toStdString();
	if (loginres == "true")
	{
		QMessageBox::information(this, " ", QString::fromLocal8Bit("��¼�ɹ�!"), QString::fromLocal8Bit("ȷ��"));
		TaskUi * FirstTask = new TaskUi(nullptr);
		FirstTask->show();
	}
	else
	{
		QMessageBox::information(this, " ", QString::fromLocal8Bit("��¼ʧ��!"), QString::fromLocal8Bit("ȷ��"));
	}
}