#pragma once

#include <cstdint>

enum CommandId : std::uint8_t
{
    CLIENT_HANDSHAKE    = 1,
    CLIENT_NEW_GAME     = 2,
    CLIENT_ASK_MOVES    = 3,
    CLIENT_MAKE_MOVE    = 4,
    CLIENT_ENGINE_MAKE_MOVE = 5,

    SERVICE_HANDSHAKE   = 100,
    SERVICE_NEW_GAME_OK = 101,
    SERVICE_POSSIBLE_MOVES = 102,
    SERVICE_MOVE_RESULT = 103,
    SERVICE_ENGINE_MOVE_RESULT = 104,
};
