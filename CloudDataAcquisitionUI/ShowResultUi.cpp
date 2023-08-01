#include "ShowResultsUi.h"

using namespace std;


//�������ݿ�Ĳ�ѯ���
int callback(void* data, int argc, char** argv, char** azColName)
{
	CShowResults* ShowResults = (CShowResults*)data;
	if (ShowResults->cur == 0)
	{
		Pqq* pqq = new Pqq;
		pqq->scrollArea = new QScrollArea;
		pqq->tableWidget = new QTableWidget;
		pqq->scrollArea->setWidget(pqq->tableWidget);
		auto qlist = QStringList();
		for (int i = 0; i < argc; ++i)
		{
			qlist << azColName[i];
		}
		pqq->tableWidget->setColumnCount(argc);//�����˱�������Ϊ 8
		pqq->tableWidget->setHorizontalHeaderLabels(qlist);
		//pqq->tableWidget->setRowCount(0); // ������20��Ŀ��������ʾ����ʱ���Թ����鿴
		pqq->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #f0f0f0; }"); // ��ͷ����ɫ����ɫ
		pqq->scrollArea->setWidgetResizable(true);
		ShowResults->qsvec.push_back(pqq);
	}
	addDataToTable(ShowResults->qsvec.back()->tableWidget, argc, argv);
	ShowResults->cur++;
	return 0;
}


CShowResults::CShowResults(QWidget* parent, std::string dbpath)
	: CUIDialog(parent)
{
	cur = 0;
	// ����������
	mainWindow = new QWidget;
	mainWindow->setWindowTitle(QString::fromLocal8Bit("QQͬ�����ֽ���"));//�����˴��ڱ���Ϊ "QQͬ�����ֽ���"
	mainWindow->resize(800, 500);//���ڴ�С����Ϊ��� 800 �߶� 500 

	// �������Ŀ¼��
	treeWidget = new QTreeWidget;
	treeWidget->setHeaderLabel(QString::fromLocal8Bit("Ŀ¼"));//����Ŀ¼����ͷ����ǩΪ "Ŀ¼"
	// FontAwesome����ͼ��
	QFont fontAwesomeFont("FontAwesome");
	fontAwesomeFont.setPointSize(12); // ���������С
	treeWidget->setFont(fontAwesomeFont); // ��������
	// �������ڵ���ӽڵ㣬ʹ��FontAwesome����ͼ��
	rootItem = new QTreeWidgetItem(treeWidget, QStringList() << QString::fromLocal8Bit(" QQͬ������"));
	qqNumberItem = new QTreeWidgetItem(rootItem, QStringList() << QString::fromLocal8Bit(" QQ����"));
	userInfoItem = new QTreeWidgetItem(qqNumberItem, QStringList() << QString::fromLocal8Bit(" �û���Ϣ"));
	contactsItem = new QTreeWidgetItem(qqNumberItem, QStringList() << QString::fromLocal8Bit(" ��ϵ��"));
	messagesItem = new QTreeWidgetItem(qqNumberItem, QStringList() << QString::fromLocal8Bit(" ����"));
	photosItem = new QTreeWidgetItem(qqNumberItem, QStringList() << QString::fromLocal8Bit(" ���"));
	otherItem = new QTreeWidgetItem(qqNumberItem, QStringList() << QString::fromLocal8Bit(" ����"));
	//��Ŀ¼���е����нڵ㶼չ����ʹ�����нڵ㶼�ɼ���
	treeWidget->expandAll();
	//�������Ŀ¼��������ʽ
	applyStyles();



	////��ѯ���ݿ� ���������
	SqlRes sqlres;
	sqliteDb sqlitedb;
	sqlres = sqlitedb.InitDB(dbpath.c_str(), false);
	if (sqlres.errnum == 0)
	{
		LOG_INFO("�����ݿ�ɹ�");
	}
	else
	{
		LOG_ERROR("�����ݿ�ʧ��");
	}
	sqlitedb.setDQLCallBack(callback);
	string sql = "select * from contacts;";
	sqlitedb.do_sql(sql.c_str(), this);
	sqlitedb.close();


	//stackedWidget = QSharedPointer<QStackedWidget>(new QStackedWidget);
	//for (auto& a : qsvec)
	//{
	//	stackedWidget->addWidget(a->scrollArea);
	//}

	leftLayout = new QVBoxLayout;
	rightLayout = new QVBoxLayout;
	leftLayout->addWidget(treeWidget);//��Ŀ¼�� treeWidget ��������಼��
	rightLayout->addWidget(qsvec.back()->scrollArea);//���������Ĺ������� scrollArea �������Ҳ಼�� 

	// ����һ��ˮƽ�������ڰ����������಼��
	mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout, 1); // ������಼�ֵ���������Ϊ1
	mainLayout->addSpacing(30); // ���ˮƽ���
	mainLayout->addLayout(rightLayout, 3); // �����Ҳ಼�ֵ���������Ϊ2
	mainWindow->setLayout(mainLayout);
	mainWindow->show();
	connect(treeWidget, &QTreeWidget::itemClicked, this, &CShowResults::onItemClicked);

}

CShowResults::~CShowResults()
{}

//��ʾ����ۺ���
void CShowResults::onItemClicked(QTreeWidgetItem* item, int column)
{
	//item->
	// ��ȡ���������ı�
	QString text = item->text(column);

	// �����ı��л�����Ӧ����ͼ����
	if (text == "QQ����")
	{
		// �л���QQ������ͼ����
		// ...
	}
	else if (text == "�û���Ϣ")
	{
		stackedWidget->setCurrentIndex(0);
	}
	else if (text == "��ϵ��")
	{
		stackedWidget->setCurrentIndex(1);
	}
	else if (text == "����")
	{
		stackedWidget->setCurrentIndex(2);
	}
	else if (text == "���")
	{
		stackedWidget->setCurrentIndex(3);
	}
	else if (text == "����")
	{
		stackedWidget->setCurrentIndex(4);
	}
	// ��������л��߼�
}


// ��������ӵ����ĺ���������һ��ָ�� QTableWidget ��ָ����Ϊ����
void addDataToTable(QTableWidget* tableWidget, int argc, char** argv)
{
	// ��ȡ��ǰ��������
	int currentRowCount = tableWidget->rowCount();

	// �ڱ��ĩβ����һ��
	if (tableWidget != nullptr)
	{
		tableWidget->insertRow(currentRowCount);
	}

	for (int i = 0; i < argc; ++i)
	{
		QTableWidgetItem* newItem = new QTableWidgetItem(argv[i]);
		if (tableWidget != nullptr)
		{
			tableWidget->setItem(currentRowCount, i, newItem);
		}
	}
}

//������������������ʽ������
void CShowResults::applyStyles()
{
	// ���������ڱ���ɫ
	setStyleSheet("background-color: #f0f0f0;");

	// �������Ŀ¼������ʽ
	treeWidget->setStyleSheet(
		"QTreeWidget {"
		"background-color: #ffffff;" // ��ɫ����
		"border: 1px solid #d0d0d0;" // ��ɫ�߿�
		"}"
		"QTreeWidget::item {"
		"height: 25px;" // ������ĸ߶�
		"padding-left: 0px;" // ��߾�
		"}"
		"QTreeWidget::item:selected {"
		"background-color: #007bff;" // ѡ�����ɫ����ɫ
		"color: #ffffff;" // ѡ����������ɫ����ɫ
		"}"
	);
}