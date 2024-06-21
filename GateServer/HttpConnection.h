#pragma once
#include "const.h"
class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;
	w(tcp::socket socket); // 接管socket
	void Start();						
private:
	void CheckDelay();
	void PreParseGetParam();
	void WriteResponse();
	void HandleReq();
	tcp::socket m_socket;
	beast::flat_buffer m_buffer{ 8192 };  // http消息的缓冲区，
	http::request<http::dynamic_body> m_request;	 // 存储接收到的http消息
	http::response<http::dynamic_body> m_response;		// 用于构建并发送回客户端的http相应
	net::steady_timer m_delaychecker{					// 计时器，超时则关闭
		m_socket.get_executor(), std::chrono::seconds(60)
};
	std::string m_get_url;								// 构造url路径
	std::unordered_map<std::string, std::string>  m_get_params; // 解析url参数

};

