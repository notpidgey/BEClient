#pragma once
#include <Windows.h>

enum class be_restart_reason
{
    unknown_restart_reason = -1,
    service_not_running_properly = 0,
    service_needs_to_be_updated = 1,
};

typedef void (__cdecl *exit_fn_t)();
typedef void (__cdecl *run_fn_t)();
typedef void (__cdecl *command_fn_t)(const char* pstr_command);
typedef void (__cdecl *received_packet_fn_t)(uint64_t pvPacket, int32_t nLength);
typedef void (__cdecl *on_receive_auth_ticket_fn_t)(uint64_t pvPacket, int32_t nTicketLength);
typedef void (__cdecl *add_peer_fn_t)(uint64_t pvPeerGUID, int32_t nGUIDLength);
typedef void (__cdecl *remove_peer_fn_t)(uint64_t pvPeerGUID, int32_t nGUIDLength);
typedef void (__cdecl *encrypt_client_packet_fn)(uint64_t pvPacket, int32_t nLength, uint64_t pvEncryptedPacket, uint64_t pnEncryptedLength);
typedef void (__cdecl *decrypt_client_packet_fn)(uint64_t pvPacket, int32_t nLength, uint64_t pvEncryptedPacket, uint64_t pnEncryptedLength);

class BECL_BE_DATA
{
public:
    exit_fn_t be_exit;
    run_fn_t be_run;
    command_fn_t be_command;
    received_packet_fn_t be_received_packet;
    on_receive_auth_ticket_fn_t be_on_receive_auth_ticket;
    add_peer_fn_t be_add_peer;
    remove_peer_fn_t be_remove_peer;

    uint64_t pv_encryption_key;
    int32_t n_encryption_key_length;

    encrypt_client_packet_fn be_encrypt_client_packet;
    decrypt_client_packet_fn be_decrypt_server_packet;
};
