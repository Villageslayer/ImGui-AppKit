#include "Cheat.h"
#include <iostream>

using namespace Cheat;

namespace offsets
{
	uintptr_t local_player = 0x17E0A8;
	uint32_t current_ammo = 0x140;
	uint32_t akimbo_ammo = 0x148;
	uint32_t health = 0xEC;
	uint32_t akimbo = 0x100;
	uintptr_t pitch = 0x34;
	uintptr_t yaw = 0x38;
	uint32_t x = 0x4;
	uint32_t y = 0x8;
	uint32_t z = 0xC;
}
namespace addresses
{

	uint32_t current_ammo = 0;
	uint32_t health = 0;
	uint32_t akimbo_ammo = 0;
	uint32_t akimbo = 0;
	uintptr_t pitch = 0;
	uintptr_t yaw = 0;
	uintptr_t x = 0;
	uintptr_t y = 0;
	uintptr_t z = 0;
}
uintptr_t get_local_player()
{
	return mem.Read<uint32_t>(buffer::base + offsets::local_player);
}
void log(std::string message, uint32_t value)
{
	std::cout << "[+]" << message << value << std::endl;
}
void init_buffer(VMMDLL_SCATTER_HANDLE handle, DWORD pid)
{

	mem.AddScatterReadRequest(handle, addresses::current_ammo, &buffer::current_ammo, sizeof(buffer::current_ammo));
	mem.AddScatterReadRequest(handle, addresses::health, &buffer::health, sizeof(buffer::health));
	mem.AddScatterReadRequest(handle, addresses::akimbo_ammo, &buffer::akimbo_ammo, sizeof(buffer::akimbo_ammo));
	mem.AddScatterReadRequest(handle, addresses::akimbo, &buffer::akimbo, sizeof(buffer::akimbo));
	mem.AddScatterReadRequest(handle, addresses::pitch, &buffer::pitch, sizeof(buffer::pitch));
	mem.AddScatterReadRequest(handle, addresses::yaw, &buffer::yaw, sizeof(buffer::yaw));
	mem.AddScatterReadRequest(handle, addresses::x, &buffer::x, sizeof(buffer::x));
	mem.AddScatterReadRequest(handle, addresses::y, &buffer::y, sizeof(buffer::y));
	mem.AddScatterReadRequest(handle, addresses::z, &buffer::z, sizeof(buffer::z));
	mem.ExecuteReadScatter(handle, pid);
	mem.CloseScatterHandle(handle);
}
void pause()
{
	std::cout << "Press any key to continue...";
	std::cin.get();
}
void init_addresses()
{
	buffer::local_player = get_local_player();
	addresses::current_ammo = buffer::local_player + offsets::current_ammo;
	addresses::health = buffer::local_player + offsets::health;
	addresses::akimbo_ammo = buffer::local_player + offsets::akimbo_ammo;
	addresses::akimbo = buffer::local_player + offsets::akimbo;
	addresses::pitch = buffer::local_player + offsets::pitch;
	addresses::yaw = buffer::local_player + offsets::yaw;
	addresses::x = buffer::local_player + offsets::x;
	addresses::y = buffer::local_player + offsets::y;
	addresses::z = buffer::local_player + offsets::z;
}

void Cheat::run(){

	if (!mem.Init("ac_client.exe", true, true))
	{
		std::cout << "Failed to initilize DMA" << std::endl;
		Sleep(10000);
		
	}

	std::cout << "DMA initilized" << std::endl;




	if (!mem.FixCr3())
		std::cout << "Failed to fix CR3" << std::endl;
	else
		std::cout << "CR3 fixed" << std::endl;

	buffer::base = mem.GetBaseDaddy("ac_client.exe");
	DWORD pid = mem.GetPidFromName("ac_client.exe");




	VMMDLL_SCATTER_HANDLE handle = mem.CreateScatterHandle(pid);


	init_addresses();
	init_buffer(handle, pid);



	log("Health:", buffer::health);

	log("Ammo:", buffer::current_ammo);
	log("Akimbo Ammo:", buffer::akimbo_ammo);
	log("Akimbo:", buffer::akimbo);
	log("X:", buffer::x);
	log("Y:", buffer::y);
	log("Z:", buffer::z);
	std::cout << "[+]" << "Pitch:" << std::defaultfloat << buffer::pitch << std::endl;
	std::cout << "[+]" << "Yaw:" << std::defaultfloat << buffer::yaw << std::endl;
	log("Boosting HP \n", 0);



	mem.Write<float>(addresses::pitch, 0.0f);
	mem.Write<float>(addresses::yaw, 0.0f);
}