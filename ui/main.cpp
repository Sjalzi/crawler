#include"service.h"

int main()
{
	auto& service = Service::getInstance();

	//ִ��ҵ�����
	std::string requestUrl = "https://ic.qq.com/pim/login.jsp";
	Proxy::getInstance().send(MsgType::GET_QRCODE_MSG, requestUrl);

	while (1)
	{
	}
}