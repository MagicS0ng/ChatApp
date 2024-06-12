#pragma once
#include "const.h"
#include "MySqlDAO.h"
#include "StatusGrpcClient.h"

class HttpConnection;
typedef std::function<void(std::shared_ptr <HttpConnection>)>HttpHandler;
class LogicSystem :public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem() {
	};
	bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
	bool HandlePost(std::string, std::shared_ptr<HttpConnection>);
	void RegGet(std::string, HttpHandler);
	void RegPost(std::string, HttpHandler);
private:
	LogicSystem();
	std::map < std::string, HttpHandler> m_post_handler;
	std::map < std::string, HttpHandler> m_get_handler;

};
