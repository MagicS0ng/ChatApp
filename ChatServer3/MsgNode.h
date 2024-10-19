#pragma once
#include "const.h"
#include <string>
#include <iostream>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
class LogicSystem;
class LogicNode;
class MsgNode
{
public:
	MsgNode(short max_len) : m_total_len(max_len), m_cur_len(0)
	{
		m_data = new char[m_total_len + 1]();
		m_data[m_total_len] = '\0';
	}
	virtual ~MsgNode()
	{
		std::cout << "Destruct MsgNode " << std::endl;
		delete[] m_data;
	}
	void Clear()
	{
		::memset(m_data, 0, m_total_len);
		m_cur_len = 0;
	}
public:
	short m_cur_len;
	short m_total_len;
	char* m_data;
};

class RecvNode : public MsgNode
{
	friend class LogicSystem;
public:
	RecvNode(short max_len, short msg_id);
private:
	short m_msg_id;
};
class SendNode :public MsgNode
{
public:
	SendNode(const char* msg, short max_len, short msg_id);
private:
	short m_msg_id;
};