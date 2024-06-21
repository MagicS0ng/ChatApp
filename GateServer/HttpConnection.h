#pragma once
#include "const.h"
class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;
	w(tcp::socket socket); // �ӹ�socket
	void Start();						
private:
	void CheckDelay();
	void PreParseGetParam();
	void WriteResponse();
	void HandleReq();
	tcp::socket m_socket;
	beast::flat_buffer m_buffer{ 8192 };  // http��Ϣ�Ļ�������
	http::request<http::dynamic_body> m_request;	 // �洢���յ���http��Ϣ
	http::response<http::dynamic_body> m_response;		// ���ڹ��������ͻؿͻ��˵�http��Ӧ
	net::steady_timer m_delaychecker{					// ��ʱ������ʱ��ر�
		m_socket.get_executor(), std::chrono::seconds(60)
};
	std::string m_get_url;								// ����url·��
	std::unordered_map<std::string, std::string>  m_get_params; // ����url����

};

