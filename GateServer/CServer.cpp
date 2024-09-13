#include "CServer.h"
#include "HttpConnection.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port): m_ioc(ioc), m_acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{

}
void CServer::Start()
{
	auto self = shared_from_this();
	auto& io_context = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(io_context);
	m_acceptor.async_accept(new_con->GetSocket(), [self, new_con](beast::error_code ec)
		{
			try
			{ // if failed, listen on other one
				if (ec)
				{
					self->Start();
					return;
				}
				// create new connection
				new_con->Start();

				// keep listening
				self->Start();
			}
			catch (std::exception &exp)
			{
				std::cout << "We got some exception here!" << exp.what() << std::endl;
				self->Start();
			}
		});
}