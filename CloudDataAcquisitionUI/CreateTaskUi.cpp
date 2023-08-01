#include "CreateTaskUi.h"
#include "StartTaskUi.h"

#define LENGTH 600
#define HEIGHT 50

#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QString>
#include<public.h>
#include"CloudDataAcquisitionUI.h"
#include "ShowQRCode.h"
#include"service.h"
#include"qprocess.h"
CreateTaskUi::CreateTaskUi(QWidget* parent) :
	QWidget(parent)
{
	resize(LENGTH, 450);
	this->setWindowTitle(QString::fromLocal8Bit("��������"));
	initUi();
}

CreateTaskUi::~CreateTaskUi()
{}


void CreateTaskUi::initUi()
{
	// ���岼��Ϊ��ֱ���֣�������
	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(vLayout);

	// ��һ�㲼�֣���ֱ���֣������㣬ÿһ�����һ��Label��LineEdit
	{
		QWidget* firstQW = new QWidget;
		firstQW->setFixedSize(LENGTH, 300);
		vLayout->addWidget(firstQW);

		QVBoxLayout* vFirstLayout = new QVBoxLayout;
		vFirstLayout->setSpacing(0);
		vFirstLayout->setContentsMargins(0, 0, 0, 0);
		firstQW->setLayout(vFirstLayout);
		{
			// ��һ��Label��LineEdit
			{
				QWidget* secondQW_1 = new QWidget;
				secondQW_1->setFixedSize(LENGTH, HEIGHT);
				vFirstLayout->addWidget(secondQW_1);

				QHBoxLayout* hLayout_1 = new QHBoxLayout;
				secondQW_1->setLayout(hLayout_1);

				hLayout_1->addStretch();
				firstLayerLabel_1 = new QLabel(QString::fromLocal8Bit("�������ƣ�"));
				QFont f1("����", 12);
				firstLayerLabel_1->setFont(f1);
				hLayout_1->addWidget(firstLayerLabel_1);
				lineEdit_1 = new QLineEdit(QString::fromLocal8Bit("��������������"));
				lineEdit_1->setFixedWidth(300);
				hLayout_1->addWidget(lineEdit_1);
				hLayout_1->addStretch();
			}
			// �ڶ���Label��LineEdit
			{
				QWidget* secondQW_2 = new QWidget;
				secondQW_2->setFixedSize(LENGTH, HEIGHT);
				vFirstLayout->addWidget(secondQW_2);

				QHBoxLayout* hLayout_2 = new QHBoxLayout;
				secondQW_2->setLayout(hLayout_2);

				hLayout_2->addStretch();
				firstLayerLabel_2 = new QLabel(QString::fromLocal8Bit("������˭��"));
				QFont f2("����", 12);
				firstLayerLabel_2->setFont(f2);
				hLayout_2->addWidget(firstLayerLabel_2);
				lineEdit_2 = new QLineEdit(QString::fromLocal8Bit("�����봴��������"));
				lineEdit_2->setFixedWidth(300);
				hLayout_2->addWidget(lineEdit_2);
				hLayout_2->addStretch();
			}
			// ������Label��LineEdit
			{
				QWidget* secondQW_3 = new QWidget;
				secondQW_3->setFixedSize(LENGTH, HEIGHT);
				vFirstLayout->addWidget(secondQW_3);

				QHBoxLayout* hLayout_3 = new QHBoxLayout;
				secondQW_3->setLayout(hLayout_3);

				hLayout_3->addStretch();
				firstLayerLabel_3 = new QLabel(QString::fromLocal8Bit("�����ţ�"));
				QFont f3("����", 12);
				firstLayerLabel_3->setFont(f3);
				hLayout_3->addWidget(firstLayerLabel_3);
				lineEdit_3 = new QLineEdit(QString::fromLocal8Bit("������������"));
				lineEdit_3->setFixedWidth(300);
				hLayout_3->addWidget(lineEdit_3);
				hLayout_3->addStretch();
			}
		}
	}

	// �ڶ��㲼�֣�����һ����ť
	{
		QHBoxLayout* secondLayerLayout = new QHBoxLayout;
		QPushButton* confireBtn = new QPushButton(QString::fromLocal8Bit("ȷ��"));
		QFont f1("����", 12);
		confireBtn->setFont(f1);  // ���ð�ť����
		confireBtn->setFixedSize(100, 60);
		secondLayerLayout->addStretch();
		secondLayerLayout->addWidget(confireBtn);
		secondLayerLayout->addStretch();
		vLayout->addLayout(secondLayerLayout);

		connect(confireBtn, &QPushButton::clicked, this, &CreateTaskUi::saveToDB);
		connect(confireBtn, &QPushButton::clicked, this, &QWidget::close);
		connect(confireBtn, &QPushButton::clicked, this, &CreateTaskUi::sendUrl);
		connect(confireBtn, &QPushButton::clicked, this, &CreateTaskUi::addTask);
		connect(confireBtn, &QPushButton::clicked, this, &CreateTaskUi::startTask);

		connect(&Service::getInstance(), &Service::GET_QRCODE_MSG_ACK_Signal, this, &CreateTaskUi::GET_QRCODE_MSG_ACK_callback);
	}
}


void CreateTaskUi::GET_QRCODE_MSG_ACK_callback(QString image_path)
{
	CShowQRCode* cShowQRCode = new CShowQRCode(nullptr);
	cShowQRCode->showqrcode(image_path.toStdString());
}

void CreateTaskUi::sendUrl()
{
	std::string url = lineEdit_1->text().toStdString();
	Proxy::getInstance().send(MsgType::GET_QRCODE_MSG, url);
}

void CreateTaskUi::addTask()
{
	CloudDataAcquisitionUI::getInstance().addTask();
}

void CreateTaskUi::startTask()
{
	//�������߳� ִ���������   ���̺߳����̷ֱ߳�����redis�������������Ķ˿�   ��Ϣͨ�ţ���ֹ���߳�������Ϣ
	 
	CloudDataAcquisitionUI::getInstance().addTask();
}

void CreateTaskUi::saveToDB()
{
	QString TaskUrl = lineEdit_1->text();
	QString Creater = lineEdit_2->text();
	QString TaskId = lineEdit_3->text();
	// �������ݿ�
	QSqlDatabase database;
	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("MyDataBase.db");
	// �����ݿ�
	database.open();

	QSqlQuery sql_query;
	// ��һ����ӷ�ʽ
	QString insert_sql = "insert into CreateTaskTable values (?, ?, ?)";
	sql_query.prepare(insert_sql);
	sql_query.addBindValue(TaskUrl);
	sql_query.addBindValue(Creater);
	sql_query.addBindValue(TaskId);
	sql_query.exec();

//	QProcess p;
//	QStringList list;
//	list.push_back("xxxx\.exe");
//	list.push_back("1");
//	list.push_back("json");
//	p.setArguments(list);
//	p.start();
//	p.waitForStarted();
//	p.processId();
//
//cmd:  "taskkill /F /ID processname";
//
//	QStringList args;
//	args << "/F";
//	args << "/IM testApp.exe";
//	//taskkill /pid 2604 -t -f
//	QProcess::execute("taskkill", args); //Should be 'taskkill /IM testApp.exe /F'
}
//connect


//void func()
//{
//
//}
