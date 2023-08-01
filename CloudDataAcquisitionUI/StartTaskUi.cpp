#include "StartTaskUi.h"
#include "DisplayProgressUi.h"
#include "ShowResultsUi.h"
#define LENGTH 800

#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QCoreApplication>
#include<db.h>
#include<proxy.h>
#include"service.h"
CStartTaskUi::CStartTaskUi(QWidget* parent) :
	QWidget(parent)
{

	resize(LENGTH, 700);
	//setDialogTitle(QString::fromLocal8Bit("���ݲɼ�����"));
	initUi();
	this->show();
}

CStartTaskUi::~CStartTaskUi()
{
}

void CStartTaskUi::paintEvent(QPaintEvent* event)
{
	/*QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);*/
}

void CStartTaskUi::initUi()
{
	// ���岼��Ϊ��ֱ���֣�������
	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);
	//this->setClientLayout(vLayout);

	// ��һ�㣬�ܵ���ˮƽ���֣������Ҳ࣬���Ϊ��ֱ���֣��Ҳ���һ����ť
	{
		QWidget* firstLayerQW = new QWidget;
		firstLayerQW->setObjectName("StrtTaskUiFirstLayerQW");
		firstLayerQW->setStyleSheet("#StrtTaskUiFirstLayerQW{border-bottom:1px solid red;}");
		firstLayerQW->setFixedSize(LENGTH, 150);
		vLayout->addWidget(firstLayerQW, 0, Qt::AlignTop);

		QHBoxLayout* hLayout_1 = new QHBoxLayout;
		hLayout_1->setSpacing(0);
		hLayout_1->setContentsMargins(0, 0, 90, 0);
		firstLayerQW->setLayout(hLayout_1);
		// ��ഹֱ����
		{
			QWidget* firstLeftQW = new QWidget;

			firstLeftQW->setFixedSize(LENGTH - 200, 150);
			hLayout_1->addWidget(firstLeftQW, 0, Qt::AlignLeft);

			QVBoxLayout* vLayout_1 = new QVBoxLayout;
			firstLeftQW->setLayout(vLayout_1);
			{
				// �ܽ��ȱ�ǩ
				QLabel* totalProgressLabel = new QLabel(QString::fromLocal8Bit("�ܽ���"));
				QFont f11("����", 12);
				totalProgressLabel->setFont(f11);
				vLayout_1->addWidget(totalProgressLabel);

				// ������
				firstLayerProgressBar = new QProgressBar(this);
				firstLayerProgressBar->setFixedWidth(550);
				firstLayerProgressBar->setRange(0, 100); // ���ý������ķ�Χ
				firstLayerProgressBar->setValue(0); // ���ý������ĳ�ʼֵ
				for (int i = 0; i <= 100; ++i) {
					firstLayerProgressBar->setValue(i);
					QCoreApplication::processEvents(); // �����¼�ѭ�����Ա��������ʾ����

					// ������������
				}
				vLayout_1->addWidget(firstLayerProgressBar);

				// ����ɼ�����ʱ��
				QHBoxLayout* hLayout_11 = new QHBoxLayout;
				vLayout_1->addLayout(hLayout_11);
				{
					QLabel* timeLabel = new QLabel(QString::fromLocal8Bit("����ɼ�����ʱ�䣺"));
					QFont f21("����", 12);
					timeLabel->setFont(f21);
					hLayout_11->addWidget(timeLabel);

					QLabel* showTimeLabel = new QLabel("30min");
					QFont f22("����", 12);
					showTimeLabel->setFont(f22);
					hLayout_11->addWidget(showTimeLabel);
				}

				// �ɼ���������
				QHBoxLayout* hLayout_12 = new QHBoxLayout;
				vLayout_1->addLayout(hLayout_12);
				{
					QLabel* dataLabel = new QLabel(QString::fromLocal8Bit("�ɼ�����������"));
					QFont f31("����", 12);
					dataLabel->setFont(f31);
					hLayout_12->addWidget(dataLabel);

					QLabel* showDataLabel = new QLabel("100");
					QFont f32("����", 12);
					showDataLabel->setFont(f32);
					hLayout_12->addWidget(showDataLabel);
				}

			}
		}
		// �Ҳ�İ�ť
		{
			QPushButton* viewResultsBtn = new QPushButton(QString::fromLocal8Bit("�鿴���"));
			QFont f12("����", 12);
			viewResultsBtn->setFont(f12);
			viewResultsBtn->setFixedWidth(100);
			hLayout_1->addWidget(viewResultsBtn);

			connect(viewResultsBtn, &QPushButton::clicked, this, &CStartTaskUi::showResults);
			connect(viewResultsBtn, &QPushButton::clicked, this, &QWidget::close);
		}
	}

	// �ڶ���, �ܵ���ˮƽ���֣������չʾ�б��Ҳ��ǻ�������
	{
		QWidget* secondTotalLayerQW = new QWidget;  // �ڶ����ܵĲ��֣�����չʾ�б�͹�������
		vLayout->addWidget(secondTotalLayerQW);

		QHBoxLayout* hSecondTotalLayout = new QHBoxLayout;
		secondTotalLayerQW->setLayout(hSecondTotalLayout);
		hSecondTotalLayout->setSpacing(0);
		hSecondTotalLayout->setContentsMargins(0, 0, 0, 0);
		{
			QListWidget* listView = new QListWidget(this);
			listView->setFlow(QListView::TopToBottom);

			hSecondTotalLayout->addWidget(listView);

			for (int i = 0; i < 10; ++i)
			{
				int iCount = listView->count();
				listView->insertItem(iCount + 1, "");

				QListWidgetItem* item = new QListWidgetItem;
				item->setSizeHint(QSize(LENGTH, 120));
				listView->addItem(item);

				CDisplayProgressUi* cDisplayProgressUi = new CDisplayProgressUi();
				listView->setItemWidget(item, cDisplayProgressUi);
			}
		}
	}

	connect(&Service::getInstance(), &Service::START_CRAWL_MSG_ACK_Signal, this, &CStartTaskUi::START_CRAWL_MSG_ACK_callback);
}

void CStartTaskUi::showResults()
{
	CShowResults *showresults = new CShowResults(this,dbname);
}


void CStartTaskUi::START_CRAWL_MSG_ACK_callback(QString qdbname)
{
	dbname = qdbname.toStdString();
	if (dbname.size())
	{
		LOG_INFO("��ȡ���ݳɹ�!");
		QMessageBox::information(this, " ", QString::fromLocal8Bit("��ȡ���ݳɹ�!"), QString::fromLocal8Bit("ȷ��"));
	}
	else
	{
		LOG_INFO("��ȡ����ʧ��!");
		QMessageBox::information(this, " ", QString::fromLocal8Bit("��ȡ����ʧ��!"), QString::fromLocal8Bit("ȷ��"));
	}
}

