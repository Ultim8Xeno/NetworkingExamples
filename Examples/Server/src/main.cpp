#include "Server.h"

enum class MsgType : uint32_t
{
	ServerPing
};

class Server : public Network::Server<MsgType>
{
public:
	Server(uint16_t port) : Network::Server<MsgType>(port)
	{

	}
protected:
	virtual bool OnClientConnection(std::shared_ptr<Network::Connection<MsgType>> client)
	{
		return true;
	}
	virtual void OnClientDisconnect(std::shared_ptr<Network::Connection<MsgType>> client)
	{

	}
	virtual void OnMessage(std::shared_ptr<Network::Connection<MsgType>> client, Network::Message<MsgType>& msg)
	{
		switch (msg.header.id)
		{
		case MsgType::ServerPing:
		{
			std::chrono::system_clock::time_point time;
			msg >> time;
			Network::Message<MsgType> outMsg;
			outMsg.header.id = MsgType::ServerPing;
			outMsg << time;
			client->Send(outMsg);
		}
		break;
		default:
			break;
		}
	}
};

int main(void)
{
	Server server(60000);
	server.Start();

	while (1)
	{
		server.Update(-1, true);
	}

	return 0;
}