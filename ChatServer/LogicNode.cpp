#include "LogicNode.h"
LogicNode::LogicNode(std::shared_ptr<CSession> session, std::shared_ptr<RecvNode> recvnode) :
	m_session(session), m_recvnode(recvnode)
{

}