#pragma once
#include "const.h"
class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;
	HttpConnection(tcp::socket socket);
	void Start();
private:
	void CheckDelay();
	void PreParseGetParam();
	void WriteResponse();
	void HandleReq();
	tcp::socket m_socket;
	beast::flat_buffer m_buffer{ 8192 };
	http::request<http::dynamic_body> m_request;
	http::response<http::dynamic_body> m_response;
	net::steady_timer m_delaychecker{
		m_socket.get_executor(), std::chrono::seconds(60)
};
	std::string m_get_url;
	std::unordered_map<std::string, std::string>  m_get_params;
		
};

