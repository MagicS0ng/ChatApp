#include "RPConPool.h"
RPConPool::RPConPool(size_t poolSize, std::string host, std::string port) : poolSize_(poolSize), host_(host), port_(port), is_stop(false) {
    for (size_t i = 0; i < poolSize_; ++i) {

        std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
        connections_.push(VarifyService::NewStub(channel));
    }
}
RPConPool::~RPConPool()
{
    std::lock_guard<std::mutex> lock(mutex_);
    Close();
    while (!connections_.empty()) {
        connections_.pop();
    }
}
std::unique_ptr<VarifyService::Stub> RPConPool::getConnection()
{
    std::unique_lock<std::mutex> lock(mutex_);
    cv.wait(lock, [this] {
        if (is_stop) {
            return true;
        }
        return !connections_.empty();
        });
    //如果停止则直接返回空指针
    if (is_stop) {
        return  nullptr;
    }
    auto context = std::move(connections_.front());
    connections_.pop();
    return context;
}
void RPConPool::returnConnection(std::unique_ptr<VarifyService::Stub> context)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (is_stop) {
        return;
    }
    connections_.push(std::move(context));
    cv.notify_one();
}
void RPConPool::Close()
{
		is_stop = true;
		cv.notify_one();	
}