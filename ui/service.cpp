#include"service.h"

// ��ȡ��������Ľӿں���
Service& Service::getInstance()
{
	static Service service;
	return service;
}

Service::Service()
{
	// ��ʼ��proxy
	Proxy::getInstance().set_GET_QRCODE_MSG_ACK_callback(std::bind(&Service::GET_QRCODE_MSG_ACK_callback, this, std::placeholders::_1));
	Proxy::getInstance().set_QRCODE_CONFIRM_MSG_ACK_callback(std::bind(&Service::QRCODE_CONFIRM_MSG_ACK_callback, this, std::placeholders::_1));
	Proxy::getInstance().set_START_CRAWL_MSG_ACK_callback(std::bind(&Service::START_CRAWL_MSG_ACK_callback, this, std::placeholders::_1));
	Proxy::getInstance().set_CURRENT_PROGESS_MSG_ACK_callback(std::bind(&Service::CURRENT_PROGESS_MSG_ACK_callback, this, std::placeholders::_1));
	Proxy::getInstance().initsubpubchannel(1000, 1001);
}

void Service::GET_QRCODE_MSG_ACK_callback(std::string image_path)
{
	LOG_INFO("ͼƬλ��:%s", image_path.c_str());
	std::cout << "�ȴ��û�ɨ��,����y����:" << std::endl;
	string cur;
	getline(cin, cur);
	if (cur == "y")
	{
		string requeststr = "";
		Proxy::getInstance().send(MsgType::QRCODE_CONFIRM_MSG, requeststr);
	}
}

void Service::QRCODE_CONFIRM_MSG_ACK_callback(std::string msg)
{
	if (msg == "true")
	{
		LOG_INFO("��½�ɹ�!");
		std::cout << "����y��ʼ��ȡ����:" << std::endl;
		string cur;
		getline(cin, cur);
		if (cur == "y")
		{
			string requeststr = "";
			Proxy::getInstance().send(MsgType::START_CRAWL_MSG, requeststr);
		}
	}
	else
	{
		LOG_INFO("��½ʧ��!");
	}
}

void Service::START_CRAWL_MSG_ACK_callback(std::string msg)
{
	if (msg.size())
	{
		SqlRes sqlres;
		LOG_INFO("��ȡ��ɣ���ʼ��ȡ�������ݿ�����ݲ���ʾ!");
		sqliteDb sqlitedb;
		string nickname_db = dbPath + msg + ".db";
		sqlres = sqlitedb.InitDB(nickname_db.c_str(), false);

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
		sqlitedb.do_sql(sql.c_str());
		sqlitedb.close();
	}
	else
	{
		LOG_INFO("��ѯ���ݿ�ʧ��!");
	}
}

void Service::CURRENT_PROGESS_MSG_ACK_callback(std::string msg)
{
	//��ʾ������

}


//�������ݿ�Ĳ�ѯ���
int callback(void* data, int argc, char** argv, char** azColName)
{
	fprintf(stderr, "%s: \n", (const char*)data);
	//for (int i = 0; i < argc; ++i)
	//{
	//	char buf[1024] = { 0 };
	//	sprintf(buf, "%-6s=%-6s ", azColName[i], argv[i] ? argv[i] : "NULL");
	//	writeintfile("m.txt", buf, false,false);
	//}
	//writeintfile("m.txt", "\n", false,false);
	return 0;
}