#include "memory.h"
#include<thread>

using namespace std;
namespace offsets
{
	constexpr auto localPlayer = 0xDC14CC;
	constexpr auto flags = 0x104;
	constexpr auto forcejump = 0x52878FC;
}


int main() {
	auto mem = Memory("csgo.exe");
	cout << "Process id: " << mem.GetProcesID() << endl;

	const auto client = mem.GetModuleAddress("client.dll");
	cout << "client.dll -> " << "0x" << hex << client << dec << endl;

	while (true)
	{	
		const auto localPlayer = mem.Read<uintptr_t>(client + offsets::localPlayer);

		if (localPlayer) {
			const auto onGround = mem.Read<bool>(localPlayer + offsets::flags);

			if (GetAsyncKeyState(VK_SPACE) && onGround & (1 << 0))
			{
				mem.Write<BYTE>(client + offsets::forcejump, 6);
			}
		}

		this_thread::sleep_for(chrono::milliseconds(5));
	}

}