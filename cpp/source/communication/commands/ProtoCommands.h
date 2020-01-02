#pragma once
#include "protomessages/SrvHandshake.pb.h"
#include "protomessages/SrvNewGameOk.pb.h"
#include "protomessages/SrvPossibleMoves.pb.h"
#include "protomessages/SrvMoveResult.pb.h"

#include "protomessages/ClHandshake.pb.h"
#include "protomessages/ClNewGame.pb.h"
#include "protomessages/ClAskPossibleMoves.pb.h"
#include "protomessages/ClMakeMove.pb.h"
#include "protomessages/ClEngineMakeMove.pb.h"

class SrvHandshakeCmd;
class SrvNewGameOkCmd;
class SrvPossibleMovesCmd;
class SrvMoveResultCmd;
class SrvEngineMoveResultCmd;

class ClHandshakeCmd;
class ClNewGameCmd;
class ClAskPossibleMovesCmd;
class ClMakeMoveCmd;
class ClEngineMakeMoveCmd;

template<class Cmd>
struct Proto;

template<>
struct Proto<SrvHandshakeCmd>
{
    using ProtoCommandType = server::SrvHandshake;
};

template<>
struct Proto<SrvNewGameOkCmd>
{
    using ProtoCommandType = server::SrvNewGameOk;
};

template<>
struct Proto<SrvPossibleMovesCmd>
{
    using ProtoCommandType = server::SrvPossibleMoves;
};

template<>
struct Proto<SrvMoveResultCmd>
{
    using ProtoCommandType = server::SrvMoveResult;
};

template<>
struct Proto<ClHandshakeCmd>
{
    using ProtoCommandType = client::ClHandshake;
};

template<>
struct Proto<ClNewGameCmd>
{
    using ProtoCommandType = client::ClNewGame;
};

template<>
struct Proto<ClAskPossibleMovesCmd>
{
    using ProtoCommandType = client::ClAskPossibleMoves;
};

template<>
struct Proto<ClMakeMoveCmd>
{
    using ProtoCommandType = client::ClMakeMove;
};

template<>
struct Proto<ClEngineMakeMoveCmd>
{
    using ProtoCommandType = client::ClEngineMakeMove;
};
