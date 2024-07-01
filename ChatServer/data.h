#pragma once
#include <string>
struct UserInfo
{	
	UserInfo() :name(""), pwd(""), uid(0), email(""), nick(""), desc(""), sex(0) {}
	std::string userName;
	std::string userPwd;
	std::string userEmail;
	std::string userNick;
	int userSex;
	std::string userDesc;
	int uid;
};