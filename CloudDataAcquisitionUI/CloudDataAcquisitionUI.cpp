#include "CloudDataAcquisitionUI.h"

#include "TaskCardUi.h"
#include "TaskUi.h"
#include "CreateTaskUi.h"
#include<QApplication>
#include <QPushButton>  
#include <QVBoxLayout>  // ��ֱ����
#include <QHBoxLayout>  // ˮƽ����
#include <QStackedWidget>  // ��ֱ��ˮƽ����������ҳ�棬����ֻ����ʾ��ǰ���ҳ��
#include "ShowQRCode.h"

#define LENGTH 1200
#define HEIGHT 800

CloudDataAcquisitionUI& CloudDataAcquisitionUI::getInstance()
{
	static CloudDataAcquisitionUI cloudDataAcquisitionUI;
	return cloudDataAcquisitionUI;
}

CloudDataAcquisitionUI::CloudDataAcquisitionUI(QWidget* parent)
	: QWidget(parent)
{
	resize(LENGTH, HEIGHT);
	this->setWindowTitle(QString::fromLocal8Bit("����������ȡ������"));
	initUi();
}

CloudDataAcquisitionUI::~CloudDataAcquisitionUI()
{}

void CloudDataAcquisitionUI::initUi()
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	mainlayout->setSpacing(0);
	mainlayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainlayout);

	QWidget* topWidget = new QWidget;
	mainlayout->addWidget(topWidget);
	{
		QHBoxLayout* topLayout = new QHBoxLayout;
		topWidget->setLayout(topLayout);

		QWidget* taskWidget = new QWidget;
		taskWidget->setFixedSize(LENGTH, 100);
		taskWidget->setStyleSheet("#cloudDataAcquisitionUiWidget{border-bottom: 1px solid black;}");
		topLayout->addWidget(taskWidget);
		topLayout->setSpacing(0);
		topLayout->setContentsMargins(0, 0, 0, 0);
		{
			taskLayout = new QHBoxLayout;
			taskLayout->setContentsMargins(0, 0, 0, 0);
			taskWidget->setLayout(taskLayout);
			taskLayout->setSpacing(0);
			//taskLayout->setContentsMargins(0, 20, 40, 0);  // �� �� �� ��
			{
				pListBtn = new QPushButton;
				pListBtn->setFixedSize(100, 30);  // ���ð�ť����
				pListBtn->setText(QString::fromLocal8Bit("�����б�"));
				QFont f1("����", 12);
				pListBtn->setFont(f1);  // ���ð�ť����
				taskLayout->addWidget(pListBtn, 0, Qt::AlignLeft | Qt::AlignBottom); // ����ť��������ߵײ�
				taskLayout->addStretch();
				connect(pListBtn, &QPushButton::clicked, this, &CloudDataAcquisitionUI::showTaskList);
			}

			QHBoxLayout* createLayout = new QHBoxLayout;
			createLayout->setContentsMargins(0, 0, 0, 0);
			taskWidget->setLayout(taskLayout);
			taskLayout->setSpacing(0);
			{
				pAddBtn = new QPushButton();
				pAddBtn->setFixedSize(100, 30);
				pAddBtn->setText(QString::fromLocal8Bit("��������"));
				QFont f3("����", 12);
				pAddBtn->setFont(f3);
				topLayout->addWidget(pAddBtn, 0, Qt::AlignVCenter | Qt::AlignRight);
				connect(pAddBtn, &QPushButton::clicked, this, &CloudDataAcquisitionUI::createTask);
			}
		}
	}

	{
		stackedWidget = new QStackedWidget(this);
		CTaskCardUi* cTaskCardUi = new CTaskCardUi;  // �����б�չʾҳ��
		stackedWidget->addWidget(cTaskCardUi);  // ��ҳ����ӵ��ѵ�����
		stackedWidget->setFixedSize(LENGTH, HEIGHT - 100);
		mainlayout->addWidget(stackedWidget);
	}
}

void CloudDataAcquisitionUI::createTask()
{
	CreateTaskUi* createTaskUi = new CreateTaskUi;
	createTaskUi->show();
}

void CloudDataAcquisitionUI::showTaskList()
{
	stackedWidget->setCurrentIndex(0);
}

void CloudDataAcquisitionUI::showTask()
{
	stackedWidget->setCurrentWidget(ButtontoTaskUiMap[(QPushButton*)sender()]);
}

void CloudDataAcquisitionUI::addTask()
{


	//��һ���µ������л���ť
	QPushButton* taskBtn = new QPushButton(this);
	taskBtn->setFixedSize(100, 30);
	taskBtn->setText(QString::fromLocal8Bit("����"));
	taskBtn->setFont(QFont("����", 12));  // ���ð�ť����

	QLayoutItem* item = taskLayout->takeAt(taskLayout->count()-1);
	if (item)
	{
		delete item->widget(); // �ͷŵ�����ռ�õĿؼ��ڴ�
		delete item; // ɾ��������
	}

	// ���°�ť��ӵ�������
	taskLayout->addWidget(taskBtn, 0, Qt::AlignLeft | Qt::AlignBottom); // ����ť��������ߵײ�

	taskLayout->addStretch();

	//��ջ���ڲ���һ���µĽ���UI
	TaskUi* newTaskUi = new TaskUi(this);
	stackedWidget->addWidget(newTaskUi);
	ButtontoTaskUiMap.insert({ taskBtn ,newTaskUi });

	// ���ø����ڵĲ���Ϊ�´�����ˮƽ����
	connect(taskBtn, &QPushButton::clicked, this, &CloudDataAcquisitionUI::showTask);
}