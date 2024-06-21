#include "LogicSystem.h"
#include "HttpConnection.h"
#include "VerifyGrpcClient.h";
#include "RedisMgr.h"
#include "MysqlMgr.h"


void LogicSystem::RegGet(std::string url, HttpHandler handler)
{
	m_get_handler.insert(make_pair(url, handler));
}
void LogicSystem::RegPost(std::string url, HttpHandler handler)
{
	m_post_handler.insert(make_pair(url, handler));
}


LogicSystem::LogicSystem()
{
	RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection)
		{
			beast::ostream(connection->m_response.body()) << "receive get_test req";
			int i = 0;
			for (auto& elem : connection->m_get_params)
			{
				i++;
				beast::ostream(connection->m_response.body()) << "param " << i << ": key is " << elem.first;
				beast::ostream(connection->m_response.body()) << "\n";
				beast::ostream(connection->m_response.body()) << "param " << i << ": value is " << elem.second;
				beast::ostream(connection->m_response.body()) << "\n";
			}
		});
	RegPost("/get_security_code", [](std::shared_ptr<HttpConnection> connection)
		{
			auto body_str = boost::beast::buffers_to_string(connection->m_request.body().data());
			std::cout << "receive body is " << body_str << std::endl;
			connection->m_response.set(http::field::content_type, "text/json");
			Json::Value root;
			Json::Reader reader;
			Json::Value src_root;
			bool parse_success = reader.parse(body_str, src_root);
			std::cout << std::boolalpha <<parse_success << std::endl;
			if (!parse_success)
			{
				std::cout << "Failed to parse JSON data!" << std::endl;
				root["error"] = ErrorCodes::ErrorJson;
				std::string jsonstr = root.toStyledString();
				beast::ostream(connection->m_response.body() )<<jsonstr;
				return true;
			}
			if (!src_root.isMember("email"))
			{
				std::cout << "Failed to parse JSON data!" << std::endl;
				root["error"] = ErrorCodes::ErrorJson;
				std::string jsonstr = root.toStyledString();
				beast::ostream(connection->m_response.body()) << jsonstr;
				return true;

			}


			auto email = src_root["email"].asString();
			GetVarifyRsp rsp = VerifyGrpcClient::GetInstance()->GetVarifyCode(email);
			std::cout << "email is " << email << std::endl;
			root["error"] = rsp.error();
			root["email"] = src_root["email"];
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->m_response.body()) << jsonstr;
			return true;
		});
	RegPost("/user_register", [](std::shared_ptr<HttpConnection> connection)
		{
			auto body_str = boost::beast::buffers_to_string(connection->m_request.body().data());
			std::cout << "receive body is " << body_str << std::endl;
			connection->m_response.set(http::field::content_type, "text/json");
			Json::Value root;
			Json::Reader reader;
			Json::Value src_root;
			bool parse_success = reader.parse(body_str, src_root);
			if (!parse_success)
			{
				std::cout << "Failed to parse Json!\n";
				root["error"] = ErrorCodes::ErrorJson;
				std::string jsonstr = root.toStyledString();
				beast::ostream(connection->m_response.body()) << jsonstr;
				return true;
			}
			auto  email = src_root["email"].asString();
			auto  userName = src_root["user"].asString();
			auto  passwd = src_root["passwd"].asString();
			auto  passwdrepeat = src_root["passwdrepeat"].asString();
			if (passwd != passwdrepeat)
			{
				std::cout << "Password Mismatch\n";
				root["error"] = ErrorCodes::PasswdErr;
				std::string jsonstr = root.toStyledString();
				beast::ostream(connection->m_response.body()) << jsonstr;
				return true;
			}

			std::string varify_code;
			bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX+src_root["email"].asString(), varify_code);
			if (!b_get_varify)
			{
				std::cout << " get varify code expired\n";
				root["error"] = ErrorCodes::VarifyExpired;
				std::string jsonstr = root.toStyledString();
				beast::ostream(connection->m_response.body()) << jsonstr;
				return true;
			}
			if (varify_code != src_root["varifycode"].asString())
			{
				std::cout << " varify code mismatch!\n";
				root["error"] = ErrorCodes::VarifyCodeErr;
				std::string jsonstr = root.toStyledString();
				beast::ostream(connection->m_response.body()) << jsonstr;
				return true;
			}
			
			int uid = MysqlMgr::GetInstance()->RegUser(userName, email, passwd);
			if (uid == 0 || uid == -1)
			{
				std::cout << "user or email exist\n";
				root["error"] = ErrorCodes::UserExist;
				std::string jsonstr = root.toStyledString();
				beast::ostream(connection->m_response.body()) << jsonstr;
				return true;
			}
			root["error"] = 0;
			root["uid"] = uid;
			root["email"] = src_root["email"].asString();
			root["user"] = src_root["user"].asString();
			root["passwd"] = src_root["passwd"].asString();
			root["passwdrepeat"] = src_root["passwdrepeat"].asString();
			root["varifycode"] = src_root["varifycode"].asString();
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->m_response.body()) << jsonstr;
			return true;
			}
	);
	RegPost("/reset_pwd", [](std::shared_ptr<HttpConnection> connection)  {
		auto body_str = boost::beast::buffers_to_string(connection->m_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->m_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success)
		{
			std::cout << "Failed to parse JSON during reseting pwd!\n";
			root["error"] = ErrorCodes::ErrorJson;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->m_response.body()) << jsonstr;
			return true;
		}
		auto email = src_root["email"].asString();
		auto name = src_root["user"].asString();
		auto pwd = src_root["passwd"].asString();
		std::string varify_code;
		bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX + src_root["email"].asString(), varify_code);
		if (!b_get_varify)
		{
			std::cout << " get varify code expired!\n";
			root["error"] = ErrorCodes::VarifyExpired;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->m_response.body()) << jsonstr;
			return true;
		}
		if (varify_code != src_root["varifycode"].asString())
		{
			std::cout << " varify code error " << std::endl;
			root["error"] = ErrorCodes::VarifyCodeErr;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->m_response.body()) << jsonstr;
			return true;
		}
		bool email_valid = MysqlMgr::GetInstance()->CheckEmail(name, email);
		if (!email_valid)
		{
			std::cout << " user email not match " << std::endl;
			root["error"] = ErrorCodes::EmailNotMatch;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->m_response.body()) << jsonstr;
			return true;
		}
		bool b_updatePwd = MysqlMgr::GetInstance()->UpdatePwd(name, pwd);
		if (!b_updatePwd)
		{
			std::cout << " update pwd failed\n";
			root["error"] = ErrorCodes::PasswdUpFailed;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->m_response.body()) << jsonstr;
			return true;
		}
		std::cout << "succeed to reset passwd " << pwd << std::endl;
		root["error"] = 0;
		root["email"] = email;
		root["user"] = name;
		root["passwd"] = pwd;
		root["varifycode"] = src_root["varifycode"].asString();
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->m_response.body()) << jsonstr;
		return true;
		});
	RegPost("/user_login", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->m_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->m_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success)
		{
			std::cout << "Failed to parse JSON data!\n";
			root["error"] = ErrorCodes::ErrorJson;
			std::string jsonStr = root.toStyledString();
			beast::ostream(connection->m_response.body()) << jsonStr;
			return true;
		}
		auto email = src_root["email"].asString();
		auto passwd = src_root["passwd"].asString();
		UserInfo userInfo;
		bool pwd_valid = MysqlMgr::GetInstance()->CheckPwd(email, passwd, userInfo);
		if (!pwd_valid)
		{
			std::cout << "User pwd mismatch\n";
			root["error"] = ErrorCodes::PasswdInvalid;
			std::string jsonStr = root.toStyledString();
			beast::ostream(connection->m_response.body()) << jsonStr;
			return true;
		}
		auto reply = StatusGrpcClient::GetInstance()->GetChatServer(userInfo.uid);
		if (reply.error())
		{
			std::cout << " grpc get chat server failed, error is " << reply.error() << std::endl;
			root["error"] = ErrorCodes::RPCFailed;
			std::string jsonStr = root.toStyledString();
			beast::ostream(connection->m_response.body()) << jsonStr;
			return true;
		}
		std::cout << "Succeed to load userinfo, uid is " << userInfo.uid << std::endl;
		root["error"] = 0;
		root["email"] = email;
		root["uid"] = userInfo.uid;
		
		root["token"] = reply.token();
		root["host"] = reply.host();
		root["port"] = reply.port();
		std::cout << "host: [" << reply.host() << "], port: [" << reply.port() << "], token: [" << reply.token() << "]" << std::endl;
		std::string jsonStr = root.toStyledString();
		beast::ostream(connection->m_response.body()) << jsonStr;
		return true;
		});
	

}		
bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> con)
{
	if (m_get_handler.find(path) == m_get_handler.end())
	{
		return false;
	}
	m_get_handler[path](con);
	return true;
}
bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> con)
{
	if (m_post_handler.find(path) == m_post_handler.end())
	{
		return false;
	}
	m_post_handler[path](con);
	return true;
}