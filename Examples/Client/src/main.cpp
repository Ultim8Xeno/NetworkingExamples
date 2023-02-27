#include "Client.h"

enum class MsgType : uint32_t
{
	ServerPing
};

class Client : public Network::Client<MsgType>
{
public:
	void PingServer()
	{
		Network::Message<MsgType> msg;
		msg.header.id = MsgType::ServerPing;
		auto time = std::chrono::system_clock::now();
		msg << time;
		Send(msg);
	}
};

int main(void)
{
	Client c;
	c.Connect("127.0.0.1", 60000);

	bool key[] = { false, false };
	bool oldKey[] = { false, false };

	bool quit = false;

	while (!quit)
	{
		if (GetForegroundWindow() == GetConsoleWindow())
		{
			key[0] = GetAsyncKeyState('P') & 0x8000;
			key[1] = GetAsyncKeyState('E') & 0x8000;
		}

		if (key[0] & !oldKey[0]) c.PingServer();
		if (key[1] & !oldKey[1]) quit = true;

		oldKey[0] = key[0];
		oldKey[1] = key[1];

		if (c.IsConnected())
		{
			while (!c.Incoming().Empty())
			{
				auto msg = c.Incoming().PopFront().msg;
				
				switch (msg.header.id)
				{
				case MsgType::ServerPing:
				{
					auto now = std::chrono::system_clock::now();
					std::chrono::system_clock::time_point then;
					msg >> then;
					std::cout << "Server Ping: " << std::chrono::duration<double>(now - then).count() << "\n";
				}
				}
			}
		}
		else
		{
			quit = true;
		}
	}

	c.Disconnect();

	return 0;
}