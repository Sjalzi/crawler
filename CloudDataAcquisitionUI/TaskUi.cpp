#include "TaskUi.h"
#include "StartTaskUi.h"
#define LENGTH 740
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include<proxy.h>
#include <QtWidgets/qmessagebox.h>

TaskUi::TaskUi(QWidget* parent) :
	QWidget(parent)
{
	resize(LENGTH, 600);
	initUi();
}

TaskUi::~TaskUi()
{}


void TaskUi::initUi()
{
	// ���岼�֣���ֱ���֣��������㲼��
	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);  // ���ϡ��ҡ���
	this->setLayout(vLayout);

	// 1����һ�㲼�֣����QWidget���
	{
		QWidget* totalQW = new QWidget;
		totalQW->setFixedSize(LENGTH, 400);
		vLayout->addWidget(totalQW);

		QVBoxLayout* totalLayout = new QVBoxLayout;
		totalLayout->setSpacing(0);
		totalLayout->setContentsMargins(0, 0, 0, 10);  // ���ϡ��ҡ���
		totalQW->setLayout(totalLayout);
		// ÿһ��QWidget��ɣ���ֱ���֣����沿�ְ��������չʾһ��ͼƬ���Ҳ��Ǵ�ֱ���֣�����������Ϣ��Ӧ�����ơ��˺š�����
		{
			QWidget* firstQW = new QWidget;
			// ����QW�����ԣ���ʽ
			firstQW->setFixedSize(LENGTH, 300);
			firstQW->setObjectName("taskCardUiFirstQW");
			// firstQW->setStyleSheet("#taskCardUiFirstQW{border: 1px solid blue;}");
			totalLayout->addWidget(firstQW);

			QHBoxLayout* hLayout_1 = new QHBoxLayout;
			hLayout_1->setSpacing(0);
			hLayout_1->setContentsMargins(10, 0, 10, 0);  // ���ϡ��ҡ���
			firstQW->setLayout(hLayout_1);
			// չʾ���ͼƬ
			{
				firstLayerLabel_1 = new QLabel("picture");  // ����label�ĳ�ʼ��ʾ����Ϊpicture
				firstLayerLabel_1->setObjectName("taskCardUiLabel_1");
				firstLayerLabel_1->setFixedSize(350, 250);  // ���ñ�ǩ�Ĵ�С
				firstLayerLabel_1->setStyleSheet("#taskCardUiLabel_1 { border: 1px solid red; }");  // ���ñ�ǩ����ʽ
				// ����ͼƬ
				// QPixmap pixmap("./pic1.png");
				QPixmap pixmap("C:/Users/32447/Pictures/Saved Pictures/test.png");
				QPixmap scaledPixmap = pixmap.scaled(QSize(250, 250), Qt::KeepAspectRatio);  // ����ͼƬ�Ĵ�С
				firstLayerLabel_1->setPixmap(scaledPixmap);
				hLayout_1->addWidget(firstLayerLabel_1);
				hLayout_1->setAlignment(firstLayerLabel_1, Qt::AlignLeft);  // ��ͼƬ�������У�����Ҫ��Ч�����˴���������addWidget()֮��	
			}
			// �Ҳ��Ǵ�ֱ���֣�����������Ϣ��Ӧ�����ơ��˺š�����
			{
				QWidget* firstRightQW = new QWidget;
				// ����QW�����ԣ���ʽ
				firstRightQW->setFixedHeight(250);
				firstRightQW->setFixedWidth(350);
				firstRightQW->setObjectName("taskCardUiFirstRightQW");
				// firstRightQW->setStyleSheet("#taskCardUiFirstRightQW{border: 1px solid black;}");
				hLayout_1->addWidget(firstRightQW);

				QVBoxLayout* vLayout_1 = new QVBoxLayout;
				vLayout_1->setSpacing(0);
				vLayout_1->setContentsMargins(10, 0, 40, 0);  // ���ϡ��ҡ���
				firstRightQW->setLayout(vLayout_1);
				// ÿһ��label��LineEdit��ˮƽ����
				// ��һ��label��LineEdit
				{
					QWidget* firstRightQW_1 = new QWidget;
					vLayout_1->addWidget(firstRightQW_1);

					QHBoxLayout* hLayout_11 = new QHBoxLayout;
					hLayout_11->setSpacing(20);
					firstRightQW_1->setLayout(hLayout_11);

					hLayout_11->addStretch();
					secondLayerLabel_1 = new QLabel(QString::fromLocal8Bit("Ӧ�����ƣ�"));
					QFont f11("����", 12);
					secondLayerLabel_1->setFont(f11);
					hLayout_11->addWidget(secondLayerLabel_1);

					lineEdit_1 = new QLineEdit(QString::fromLocal8Bit("XXXXXXXX"));
					lineEdit_1->setFixedSize(200, 30);
					hLayout_11->addWidget(lineEdit_1);
					hLayout_11->addStretch();
				}
				// �ڶ���label��LineEdit
				{
					QWidget* firstRightQW_2 = new QWidget;
					vLayout_1->addWidget(firstRightQW_2);

					QHBoxLayout* hLayout_12 = new QHBoxLayout;
					hLayout_12->setSpacing(20);
					firstRightQW_2->setLayout(hLayout_12);

					hLayout_12->addStretch();
					secondLayerLabel_2 = new QLabel(QString::fromLocal8Bit("�˺ţ�"));
					QFont f12("����", 12);
					secondLayerLabel_2->setFont(f12);
					hLayout_12->addWidget(secondLayerLabel_2);

					lineEdit_2 = new QLineEdit;
					lineEdit_2->setFixedSize(200, 30);
					hLayout_12->addWidget(lineEdit_2);
					hLayout_12->addStretch();
				}
				// ������label��LineEdit
				{
					QWidget* firstRightQW_3 = new QWidget;
					vLayout_1->addWidget(firstRightQW_3);

					QHBoxLayout* hLayout_13 = new QHBoxLayout;
					hLayout_13->setSpacing(20);
					firstRightQW_3->setLayout(hLayout_13);

					hLayout_13->addStretch();
					secondLayerLabel_3 = new QLabel(QString::fromLocal8Bit("���룺"));
					QFont f13("����", 12);
					secondLayerLabel_3->setFont(f13);
					hLayout_13->addWidget(secondLayerLabel_3);

					lineEdit_3 = new QLineEdit;
					lineEdit_3->setFixedSize(200, 30);
					hLayout_13->addWidget(lineEdit_3);
					hLayout_13->addStretch();
				}
			}
		}
		// ÿһ��QWidget�����沿�֣��������ĸ���ѡ��
		{
			// �����ĸ���ѡ��
			QCheckBox* userInformationBox = new QCheckBox(QString::fromLocal8Bit("�û���Ϣ"));
			QCheckBox* contactsInformationBox = new QCheckBox(QString::fromLocal8Bit("��ϵ��"));
			QCheckBox* messageInformationBox = new QCheckBox(QString::fromLocal8Bit("����"));
			QCheckBox* otherInformationBox = new QCheckBox(QString::fromLocal8Bit("����"));

			QFont f("����", 12);
			userInformationBox->setFont(f);
			contactsInformationBox->setFont(f);
			messageInformationBox->setFont(f);
			otherInformationBox->setFont(f);

			QWidget* secondQW = new QWidget;
			secondQW->setObjectName("taskCardUisecondQW");
			secondQW->setStyleSheet("#taskCardUisecondQW{border: 1px solid black;}");
			secondQW->setFixedSize(LENGTH, 100);
			totalLayout->addWidget(secondQW);

			QVBoxLayout* vLayout_2 = new QVBoxLayout;
			{
				{
					QHBoxLayout* hLayout_21 = new QHBoxLayout;
					hLayout_21->addWidget(userInformationBox);
					hLayout_21->addWidget(contactsInformationBox);
					vLayout_2->addLayout(hLayout_21);
				}
				{
					QHBoxLayout* hLayout_22 = new QHBoxLayout;
					hLayout_22->addWidget(messageInformationBox);
					hLayout_22->addWidget(otherInformationBox);
					vLayout_2->addLayout(hLayout_22);
				}
			}
			secondQW->setLayout(vLayout_2);
		}
	}

	// �ڶ��㲼�֣�ˮƽ���֣�����һ����ť
	{
		QWidget* secondQW = new QWidget;
		// ����QW�����ԣ���ʽ
		secondQW->setFixedHeight(100);
		secondQW->setFixedWidth(LENGTH);
		secondQW->setObjectName("taskCardUisecondQW");
		secondQW->setStyleSheet("#taskCardUisecondQW{border-top: 1px solid black;}");
		vLayout->addWidget(secondQW);

		QHBoxLayout* hLayout_3 = new QHBoxLayout;
		hLayout_3->setSpacing(0);
		hLayout_3->setContentsMargins(10, 0, 40, 0);  // ���ϡ��ҡ���
		secondQW->setLayout(hLayout_3);
		// ��ʼ����ť
		{
			startButton = new QPushButton(QString::fromLocal8Bit("��ʼ����"));
			startButton->setObjectName("taskCardUiStartButton");
			startButton->setFixedSize(100, 30);
			startButton->setStyleSheet("#taskCardUiStartButton{background-color:blue;color:red}");
			QFont f31("����", 12);
			startButton->setFont(f31);
			hLayout_3->addWidget(startButton);

			connect(startButton, &QPushButton::clicked, this, &TaskUi::startTaskBtn);
			connect(startButton, &QPushButton::clicked, this, &QWidget::close);
		}
	}
	vLayout->addStretch();

}

void TaskUi::startTaskBtn()
{
	//֪ͨ���濪ʼ��ȡ����
	std::string s = "";
	Proxy::getInstance().send(MsgType::START_CRAWL_MSG, s);
	CStartTaskUi* StartTaskUi = new CStartTaskUi(nullptr);
	StartTaskUi->show();
}
