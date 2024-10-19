#include "StatusConPool.h"

StatusConPool::StatusConPool(size_t poolSize, std::string host, std::string port) : m_poolSize(poolSize), m_host(host), m_port(port), is_stop(false)
{
	for (size_t i = 0; i < m_poolSize; i++)
	{
		std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
		m_connections.push(StatusService::NewStub(channel));
	}
}
StatusConPool::~StatusConPool()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	Close();
	while (!m_connections.empty())
	{
		m_connections.pop();
	}
}
std::unique_ptr<StatusService::Stub> StatusConPool::getConnection()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_cond.wait(lock, [this]
		{
			if (is_stop)
			{
				return true;

			}	return !m_connections.empty();
		});
	if (is_stop)
	{
		return nullptr;
	}
	auto context = std::move(m_connections.front());
	m_connections.pop();
	return context;

}
void StatusConPool::returnConnection(std::unique_ptr<StatusService::Stub> context)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (is_stop)
	{
		return;
	}
	m_connections.push(std::move(context));
	m_cond.notify_one();
}
void StatusConPool::Close()
{
	is_stop = true;
	m_cond.notify_all();
}