#include "HttpConnection.h"
#include "LogicSystem.h"

unsigned char ToHex(unsigned char x)
{
	return x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex(unsigned char x)
{
	unsigned char y;
	if (x == 'A' && x <= 'Z')
		y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z')
		y = x - 'a' + 10;
	else if (x >= '0' && x <= '9')
		y = x - '0';
	else assert(0);
	return y;
}

std::string urlEncode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum((unsigned char)str[i]) || str[i] == '-' || str[i] == '_' || str[i] == '.' || str[i] == '~')
			strTemp += str[i];
		else if (str[i] == ' ')
			strTemp += "+";
		else
		{
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] & 0x0F);
		}
	}
	return strTemp;
}
std::string urlDecode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] == '+')
			strTemp += ' ';
		else if (str[i] == '%')
		{
			assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char)(str[++i]));
			unsigned char low = FromHex((unsigned char)(str[++i]));
			strTemp += high * 16 + low;
		}
		else
			strTemp += str[i];
	}
	return strTemp;
}
HttpConnection::HttpConnection(tcp::socket socket) : m_socket(std::move(socket)) {}
void HttpConnection::Start()
{
	auto self = shared_from_this();
	http::async_read(m_socket, m_buffer, m_request, [self](beast::error_code ec, std::size_t bytes_transferred)
		{
			try
			{
				if (ec)
				{
					std::cout << "http read err is " << ec.what() << std::endl;
					return;
				}
				boost::ignore_unused(bytes_transferred);
				self->HandleReq();
				self->CheckDelay();
			}
			catch (const std::exception& exp)
			{
				std::cout << "exception is " << exp.what() << std::endl;
			}
		});

}
void HttpConnection::HandleReq()
{
	m_response.version(m_request.version());
	m_response.keep_alive(false);
	if (m_request.method() == http::verb::get)
	{
		PreParseGetParam();
		bool success = LogicSystem::GetInstance()->HandleGet(m_get_url, shared_from_this());
		if (!success) {
			m_response.result(http::status::not_found);
			m_response.set(http::field::content_type, "text/plain");
			beast::ostream(m_response.body()) << "url not found\r\n";
			WriteResponse();
			return;
		}
		m_response.result(http::status::ok);
		m_response.set(http::field::server, "GateServer");
		WriteResponse();
		return;
	}
	if (m_request.method() == http::verb::post)
	{
		bool success = LogicSystem::GetInstance()->HandlePost(m_request.target(), shared_from_this());
		if (!success) {
			m_response.result(http::status::not_found);
			m_response.set(http::field::content_type, "text/plain");
			beast::ostream(m_response.body()) << "url not found\r\n";
			WriteResponse();
			return;
		}
		m_response.result(http::status::ok);
		m_response.set(http::field::server, "GateServer");
		WriteResponse();
		return;
	}
}
void HttpConnection::WriteResponse()
{
	auto self = shared_from_this();
	m_response.content_length(m_response.body().size());
	http::async_write(m_socket, m_response, [self](beast::error_code ec, std::size_t bytes_transferred)
		{
			self->m_socket.shutdown(tcp::socket::shutdown_send, ec);
			self->m_delaychecker.cancel();
		});

}
void HttpConnection::CheckDelay()
{
	auto self = shared_from_this();
	m_delaychecker.async_wait([self](beast::error_code ec)
		{
			if (!ec)
			{
				self->m_socket.close(ec);
			}
		});
}
void HttpConnection::PreParseGetParam()
{
	auto uri = m_request.target();
	auto query_pos = uri.find('?');
	if (query_pos == std::string::npos)
	{
		m_get_url = uri;
		return;
	}
	m_get_url = uri.substr(0, query_pos);
	std::string query_string = uri.substr(query_pos + 1);
	std::string key, value;
	size_t pos = 0;
	while ((pos = query_string.find('&')) != std::string::npos)
	{
		auto pair = query_string.substr(0, pos);
		size_t eq_pos = pair.find('=');
		if (eq_pos != std::string::npos)
		{
			key = urlDecode(pair.substr(0, eq_pos));
			value = urlDecode(pair.substr(eq_pos + 1));
			m_get_params[key] = value;
		}
		query_string.erase(0, pos + 1);
	}
	if (!query_string.empty())
	{
		size_t eq_pos = query_string.find('=');
		if (eq_pos != std::string::npos)
		{
			key = urlDecode(query_string.substr(0, eq_pos));
			value = urlDecode(query_string.substr(eq_pos + 1));
			m_get_params[key] = value;
		}
	}
}
