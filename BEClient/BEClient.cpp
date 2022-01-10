#include <iostream>
#include <ostream>

#include "Structs/BECL_DATA.h"
#include "Structs/BECL_GAME_DATA.h"

enum class EInstanceStatus
{
    none,
    not_initialized,
    successfully_initialized,
    destroying,
    destroyed
};

typedef bool (__cdecl *battleclient_init_func)(int ver, uint64_t game_data, uint64_t out_be_data);

int main()
{
    const HMODULE lib = LoadLibraryA("BEClient_x64.dll");
    
    char addressBytes[] = { 192, 168, 1, 1 };

    BECL_GAME_DATA game_data;
    game_data.game_version = "Escape from Tarkov 0.12.11.1.13323";
    game_data.server_address = (uint32_t)((int32_t)addressBytes[0] << 24 | (int32_t)addressBytes[1] << 16 | (int32_t)addressBytes[2] << 8) | (int32_t)addressBytes[3];
    game_data.server_port = 0;

    game_data.print_message_fn = [](char* pstrMessage) {
        std::printf("[+] Print Message: [ Message: %s ]\n", pstrMessage);
    };
    game_data.send_packet_fn = [](uint64_t pv_packet, int32_t n_length) {
        std::printf("[+] Send Packet: [ Length: %i ]\n", n_length);
    };
    game_data.request_restart_fn = [](int32_t i_reason) {
        std::string reason;
        switch (static_cast<be_restart_reason>(i_reason))
        {
        case be_restart_reason::unknown_restart_reason:
            reason = "Unknown Restart Reason";
            break;
        case be_restart_reason::service_needs_to_be_updated:
            reason = "Service Needs To Update";
            break;
        case be_restart_reason::service_not_running_properly:
            reason = "Service Not Running Properly";
            break;
        }
        
        std::printf("[+] Request Restart: [ Reason: %s ]\n", reason);
    };
    game_data.disconnect_peer_fn = [](uint64_t pv_peer_guid, int32_t n_guid_length, LPSTR pstr_reason) {
        std::printf("[-] Disconnect Peer [ GUID Length: %i, Reason: %s ]\n", n_guid_length, pstr_reason);
    };

    const char enc_key[256] = { 0 };

    BECL_BE_DATA be_data;
    be_data.pv_encryption_key = (uint64_t)enc_key;
    be_data.n_encryption_key_length = 256;
    const bool ret = reinterpret_cast<battleclient_init_func>(GetProcAddress(lib, "Init"))(4, (uint64_t)&game_data, (uint64_t)&be_data);
    if (ret)
    {
        Beep(1000, 100);
        
        std::printf("[+] Encryption Key: [ Key Size: %i ]\n", be_data.n_encryption_key_length);
        be_data.be_run();
        be_data.be_command("guid");
        be_data.be_exit();

        std::getchar();
    }
    else
    {
        std::printf("[-] BattlEye failed to initialize\n");
        exit(-1);
    }

    return 0;
}
