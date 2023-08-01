#include "TaskCardUi.h"
#define LENGTH 400
#define HEIGHT 400

//c--->c++-->qt-->3rd-->�Լ�
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>

CTaskCardUi::CTaskCardUi(QWidget* parent):
	CSubUIDialog(parent)
{
	resize(LENGTH, HEIGHT);
	initUi();
}

CTaskCardUi::~CTaskCardUi()
{
	//����
	//�ſؼ�
	//�����
}

void CTaskCardUi::paintEvent(QPaintEvent* event)
{
	/*QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);*/
}

void CTaskCardUi::initUi()
{
	/*QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);
	this->setClientLayout(vLayout);

	QHBoxLayout* hLayout = new QHBoxLayout;
	vLayout->addLayout(hLayout);*/
	{
		// ���岼�֣���ֱ���֣��������㲼��
		QVBoxLayout* vLayout = new QVBoxLayout;
		vLayout->setSpacing(0);
		vLayout->setContentsMargins(0, 0, 0, 0);  // ���ϡ��ҡ���
		this->setClientLayout(vLayout);
		// 1����һ�㲼�֣�ˮƽ���֣�չʾ����ͼƬ
		{
			QWidget* firstQW = new QWidget;
			// ����QW�����ԣ���ʽ
			firstQW->setFixedSize(LENGTH, 100);
			firstQW->setObjectName("taskCardUiFirstQW");
			firstQW->setStyleSheet("#taskCardUiFirstQW{border: 1px solid blue;}");
			vLayout->addWidget(firstQW);

			QHBoxLayout* hLayout_1 = new QHBoxLayout;
			hLayout_1->setSpacing(0);
			hLayout_1->setContentsMargins(10, 0, 50, 0);  // ���ϡ��ҡ���
			firstQW->setLayout(hLayout_1);
			{
				// ��һ��ͼƬչʾ
				{
					firstLayerLabel_1 = new QLabel("picture");  // ����label�ĳ�ʼ��ʾ����Ϊpicture
					firstLayerLabel_1->setObjectName("taskCardUiLabel_1");
					firstLayerLabel_1->setFixedSize(100, 100);  // ���ñ�ǩ�Ĵ�С
					firstLayerLabel_1->setStyleSheet("#taskCardUiLabel_1 { border: 1px solid red; }");  // ���ñ�ǩ����ʽ
					// ����ͼƬ
					QPixmap pixmap("./pic1.png");
					QPixmap scaledPixmap = pixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio);  // ����ͼƬ�Ĵ�С
					firstLayerLabel_1->setPixmap(scaledPixmap);
					hLayout_1->addWidget(firstLayerLabel_1);
					hLayout_1->setAlignment(firstLayerLabel_1, Qt::AlignLeft);  // ��ͼƬ�������У�����Ҫ��Ч�����˴���������addWidget()֮��
				}

				// �ڶ���ͼƬչʾ
				{
					firstLayerLabel_2 = new QLabel("picture");  // ����label�ĳ�ʼ��ʾ����Ϊpicture
					firstLayerLabel_2->setObjectName("taskCardUiLabel_2");
					firstLayerLabel_2->setFixedSize(100, 100);  // ���ñ�ǩ�Ĵ�С
					firstLayerLabel_2->setStyleSheet("#taskCardUiLabel_2 { border: 1px solid red; }");  // ���ñ�ǩ����ʽ
					// ����ͼƬ
					QPixmap pixmap("./pic1.png");
					QPixmap scaledPixmap = pixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio);  // ����ͼƬ�Ĵ�С
					firstLayerLabel_2->setPixmap(scaledPixmap);
					hLayout_1->addWidget(firstLayerLabel_2);
					hLayout_1->setAlignment(firstLayerLabel_2, Qt::AlignRight);
				}
			}
		}

		// 2���ڶ��㲼�֣���ֱ���֣���������label������LineEdit
		{
			QWidget* secondQW = new QWidget;
			// ����QW�����ԣ���ʽ
			secondQW->setFixedHeight(200);
			secondQW->setFixedWidth(LENGTH);
			secondQW->setObjectName("taskCardUiSecondQW");
			// secondQW->setStyleSheet("#taskCardUiSecondQW{border: 1px solid black;}");
			vLayout->addWidget(secondQW);

			QVBoxLayout* vLayout_2 = new QVBoxLayout;
			vLayout_2->setSpacing(0);
			vLayout_2->setContentsMargins(10, 0, 10, 0);  // ���ϡ��ҡ���
			secondQW->setLayout(vLayout_2);
			// ÿһ��label��LineEdit��ˮƽ����
			// ��һ��label��LineEdit
			{
				QWidget* secondQW_1 = new QWidget;
				vLayout_2->addWidget(secondQW_1);

				QHBoxLayout* hLayout_21 = new QHBoxLayout;
				hLayout_21->setSpacing(20);
				secondQW_1->setLayout(hLayout_21);

				hLayout_21->addStretch();
				secondLayerLabel_1 = new QLabel(QString::fromLocal8Bit("�������ƣ�"));
				hLayout_21->addWidget(secondLayerLabel_1);

				lineEdit_1 = new QLineEdit(QString::fromLocal8Bit("���������������"));
				lineEdit_1->setFixedSize(200, 30);
				hLayout_21->addWidget(lineEdit_1);
				hLayout_21->addStretch();
			}
			// �ڶ���label��LineEdit
			{
				QWidget* secondQW_2 = new QWidget;
				vLayout_2->addWidget(secondQW_2);

				QHBoxLayout* hLayout_22 = new QHBoxLayout;
				hLayout_22->setSpacing(20);
				secondQW_2->setLayout(hLayout_22);

				hLayout_22->addStretch();
				secondLayerLabel_2 = new QLabel(QString::fromLocal8Bit("��ʼʱ�䣺"));
				hLayout_22->addWidget(secondLayerLabel_2);

				lineEdit_2 = new QLineEdit(QString::fromLocal8Bit("�����뿪ʼʱ��"));
				lineEdit_2->setFixedSize(200, 30);
				hLayout_22->addWidget(lineEdit_2);
				hLayout_22->addStretch();
			}
			// ������label��LineEdit
			{
				QWidget* secondQW_3 = new QWidget;
				vLayout_2->addWidget(secondQW_3);

				QHBoxLayout* hLayout_23 = new QHBoxLayout;
				hLayout_23->setSpacing(20);
				secondQW_3->setLayout(hLayout_23);

				hLayout_23->addStretch();
				secondLayerLabel_3 = new QLabel(QString::fromLocal8Bit("����ʱ�䣺"));
				hLayout_23->addWidget(secondLayerLabel_3);

				lineEdit_3 = new QLineEdit(QString::fromLocal8Bit("���������ʱ��"));
				lineEdit_3->setFixedSize(200, 30);
				hLayout_23->addWidget(lineEdit_3);
				hLayout_23->addStretch();
			}
		}

		// �����㲼�֣�ˮƽ���֣�����������ť
		{
			QWidget* thirdQW = new QWidget;
			// ����QW�����ԣ���ʽ
			thirdQW->setFixedHeight(100);
			thirdQW->setFixedWidth(LENGTH);
			thirdQW->setObjectName("taskCardUiThirdQW");
			// thirdQW->setStyleSheet("#taskCardUiThirdQW{border: 1px solid black;}");
			vLayout->addWidget(thirdQW);

			QHBoxLayout* hLayout_3 = new QHBoxLayout;
			hLayout_3->setSpacing(0);
			hLayout_3->setContentsMargins(10, 0, 40, 0);  // ���ϡ��ҡ���
			thirdQW->setLayout(hLayout_3);
			// ��ʼ����ť
			{
				startButton = new QPushButton(QString::fromLocal8Bit("��ʼ����"));
				startButton->setObjectName("taskCardUiStartButton");
				startButton->setFixedSize(100, 30);
				startButton->setStyleSheet("#taskCardUiStartButton{background-color:blue;color:red}");
				QFont f31("����", 12);
				startButton->setFont(f31);
				hLayout_3->addWidget(startButton);
			}

			// ��������ť
			{
				endButton = new QPushButton(QString::fromLocal8Bit("��������"));
				endButton->setObjectName("taskCardUiEndButton");
				endButton->setFixedSize(100, 30);
				endButton->setStyleSheet("#taskCardUiEndButton{background-color:blue;color:red}");
				QFont f32("����", 12);
				endButton->setFont(f32);
				hLayout_3->addWidget(endButton);
			}
		}
		vLayout->addStretch();
	}
}
