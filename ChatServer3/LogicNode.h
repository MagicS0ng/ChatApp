#pragma once
#include "const.h"
#include "CSession.h"
class CSession;
class MsgNode;
class RecvNode;
class LogicNode
{
	friend class LogicSystem;
public:
	LogicNode(std::shared_ptr<CSession>, std::shared_ptr<RecvNode>);
private:
	std::shared_ptr<CSession> m_session;
	std::shared_ptr<RecvNode> m_recvnode;
};