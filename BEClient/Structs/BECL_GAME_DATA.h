#pragma once
#include <Windows.h>

typedef void (__cdecl *pfn_print_message_t)(char* pstr_message);
typedef void (__cdecl *pfn_send_packet_t)(uint64_t pv_packet, int32_t n_length);
typedef void (__cdecl *pfn_request_restart_t)(int32_t i_reason);
typedef void (__cdecl *pfn_disconnect_peer_t)(uint64_t pv_peer_guid, int32_t n_guid_length, char* pstr_reason);

class BECL_GAME_DATA
{
public:
    const char* game_version;
    uint32_t server_address;
    uint16_t server_port;
    
    pfn_print_message_t print_message_fn;
    pfn_request_restart_t request_restart_fn;
    pfn_send_packet_t send_packet_fn;
    pfn_disconnect_peer_t disconnect_peer_fn;
};