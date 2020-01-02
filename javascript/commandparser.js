var CommandID = require('./commandids');
var ChessManager = require('./chesswrapper');

var ClHanshakeCmd = require('./proto_messages/ClHandshake_pb');
var ClNewGameCmd = require('./proto_messages/ClNewGame_pb');
var ClAskPossibleMoves = require('./proto_messages/ClAskPossibleMoves_pb');
var ClMakeMove = require('./proto_messages/ClMakeMove_pb');
var ClEngineMakeMove = require('./proto_messages/ClEngineMakeMove_pb');


exports.parseCommand = function(bytes) 
{
    try {
        var serverCmd;
        var id = bytes[1];

        switch(id)
        {
            case CommandID.ClHandshakeID:
                var clientCmd = proto.client.ClHandshake.deserializeBinary(bytes);
                serverCmd = ChessManager.handshake();
                break;
            case CommandID.ClNewGameID:
                var clientCmd = proto.client.ClNewGame.deserializeBinary(bytes);
                serverCmd = ChessManager.newGame(clientCmd.getFen());
                break;
            case CommandID.ClAskPossibleMovesID:
                var clientCmd = proto.client.ClAskPossibleMoves.deserializeBinary(bytes);
                serverCmd = ChessManager.possibleMoves(clientCmd.getIndex());
                break;
            case CommandID.ClMakeMoveID:
                var clientCmd = proto.client.ClMakeMove.deserializeBinary(bytes);
                serverCmd = ChessManager.makeMove(clientCmd.getFromindex(), clientCmd.getToindex());
                break;
            case CommandID.ClEngineMakeMoveID:
                var clientCmd = proto.client.ClEngineMakeMove.deserializeBinary(bytes);
                serverCmd = ChessManager.makeEngineMove(clientCmd.getMove());
                break;
        }

        console.log((new Date()) + " Received Message: " + clientCmd.getId());
        console.log((new Date()) + " Send Message: " + serverCmd.getId());
        return serverCmd;
    }
    catch (err) {
        console.log("Error: " + err);
    }
}

exports.testFunc = function()
{
    console.log("hello world");
}