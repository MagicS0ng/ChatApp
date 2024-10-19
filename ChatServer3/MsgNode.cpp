#include "MsgNode.h"
RecvNode::RecvNode(short max_len, short msg_id) :MsgNode(max_len), m_msg_id(msg_id)
{

}
SendNode::SendNode(const char * msg, short max_len, short msg_id):MsgNode(max_len + ChatSet::HEAD_TOTAL_LEN), m_msg_id(msg_id)
{
	short msg_id_host = boost::asio::detail::socket_ops::host_to_network_short(msg_id);
	memcpy(m_data, &msg_id_host, HEAD_ID_LEN);
	short max_len_host = boost::asio::detail::socket_ops::host_to_network_short(max_len);
	memcpy(m_data+ChatSet::HEAD_ID_LEN, &max_len_host, ChatSet::HEAD_DATA_LEN);
	memcpy(m_data+ChatSet::HEAD_ID_LEN+ChatSet::HEAD_DATA_LEN,msg,max_len);
}