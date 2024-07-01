#pragma once
#include <functional>


enum ErrorCodes {
	Success = 0,
	Error_Json = 1001,  //Json��������
	RPCFailed = 1002,  //RPC�������
	VarifyExpired = 1003, //��֤�����
	VarifyCodeErr = 1004, //��֤�����
	UserExist = 1005,       //�û��Ѿ�����
	PasswdErr = 1006,    //�������
	EmailNotMatch = 1007,  //���䲻ƥ��
	PasswdUpFailed = 1008,  //��������ʧ��
	PasswdInvalid = 1009,   //�������ʧ��
	TokenInvalid = 1010,   //TokenʧЧ
	UidInvalid = 1011,  //uid��Ч
};


// Defer��
class Defer {
public:
	// ����һ��lambda���ʽ���ߺ���ָ��
	Defer(std::function<void()> func) : func_(func) {}

	// ����������ִ�д���ĺ���
	~Defer() {
		func_();
	}

private:
	std::function<void()> func_;
};

constexpr auto MAX_LENGTH = 1024 * 2;
//ͷ���ܳ���
constexpr auto HEAD_TOTAL_LEN = 4;
//ͷ��id����
constexpr auto HEAD_ID_LEN = 2;
//ͷ�����ݳ���
constexpr auto HEAD_DATA_LEN = 2;
constexpr auto MAX_RECVQUE = 10000;
constexpr auto MAX_SENDQUE = 1000;


enum MSG_IDS {
	MSG_CHAT_LOGIN = 1005, //�û���½
	MSG_CHAT_LOGIN_RSP = 1006, //�û���½�ذ�
	ID_SEARCH_USER_REQ = 1007, //�û���������
	ID_SEARCH_USER_RSP = 1008, //�����û��ذ�
	ID_ADD_FRIEND_REQ = 1009, //������Ӻ�������
	ID_ADD_FRIEND_RSP  = 1010, //������Ӻ��ѻظ�
	ID_NOTIFY_ADD_FRIEND_REQ = 1011,  //֪ͨ�û���Ӻ�������
};

constexpr auto USERIPPREFIX    = "uip_";
constexpr auto USERTOKENPREFIX = "utoken_";
constexpr auto IPCOUNTPREFIX   = "ipcount_";
constexpr auto USER_BASE_INFO  = "ubaseinfo_";
constexpr auto LOGIN_COUNT     = "logincount";
constexpr auto NAME_INFO       = "nameinfo_";

