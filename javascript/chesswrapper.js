var Chess = require("./node_modules/chess.js").Chess;
var CommandID = require('./commandids');
var ChessMovesParser = require('./moves_parser.js');

var SrvHandshakeCmd = require('./proto_messages/SrvHandshake_pb');
var SrvNewGameOkCmd = require('./proto_messages/SrvNewGameOk_pb');
var SrvPossibleMoves = require('./proto_messages/SrvPossibleMoves_pb');
var SrvMoveResult = require('./proto_messages/SrvMoveResult_pb');


const NEW_GAME_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

const MOVE_RESULT_OK = 0;
const MOVE_RESULT_FAIL = -1;

const KING_CASTLING = "O-O";
const QUEEN_CASTLING = "O-O-O";

var chess = new Chess();

var whiteKingPosition = "e1";
var blackKingPosition = "e8";

// Print(chess);
// var res = chess.move({from:'b1', to:'a3'});
// Print(chess);
// console.log(res);

// function Print(obj)
// {
//     console.log(obj.ascii());
// }

exports.handshake = function()
{
    var cmd = new proto.server.SrvHandshake();
    cmd.setId(CommandID.SrvHandshakeID);
    return cmd;
}

exports.newGame = function(fen)
{
    if (fen) {
        chess = new Chess(fen);
    } else {
        chess = new Chess(NEW_GAME_FEN);
    }

    var cmd = new proto.server.SrvNewGameOk();
    cmd.setId(CommandID.SrvNewGameOkID);
    cmd.setFen(chess.fen());

    console.log(chess.fen());

    whiteKingPosition = "e1";
    blackKingPosition = "e8";
    
    return cmd; 
}

function checkPromotion(position)
{
    var moves = chess.moves({square: position});

    for (var m in moves) {
        if (moves[m].indexOf('=') != -1) {
            return true;
        }
    }

    return false;
}

exports.possibleMoves = function(index)
{
    var position = ChessMovesParser.ParseMoveFromTableUIIndex(index);

    var moves = chess.moves({square: position});

    console.log("PossibleMoves");
    console.log("Position: " + position);
    console.log("Moves: ");
    console.log(moves)

    var possibleMoves = [];
    for (var m in moves) {
        var move = moves[m];
        
        // king side castling
        if (checkKingSideCastling(move)) {
            var figure = chess.get(position);
            ChessMovesParser.KingSideCastling(possibleMoves, figure['color']);
        } 
        // queen side castling
        else if (checkQueenSideCastling(move)) {
            var figure = chess.get(position);
            ChessMovesParser.QueenSideCastling(possibleMoves, figure['color']);
        }
        // other moves
        else {
            var possibleMove = ChessMovesParser.ParseMoveToTableUIIndex(move);
            possibleMoves.push(possibleMove);
        }

    }
    
    console.log("PossibleMovesIndexes: " + possibleMoves);

    var cmd = new proto.server.SrvPossibleMoves();
    cmd.setId(CommandID.SrvPossibleMovesID);
    cmd.setIndex(index);
    cmd.setMovesList(possibleMoves);

    return cmd; 
}

exports.makeMove = function(fromIndex, toIndex)
{
    var fromPosition = ChessMovesParser.ParseMoveFromTableUIIndex(fromIndex);
    var toPosition = ChessMovesParser.ParseMoveFromTableUIIndex(toIndex);
    
    return makeActualMove(fromPosition, toPosition);
}

exports.makeEngineMove = function(move)
{
    var fromPosition = move.substring(0, 2);
    var toPosition = move.substring(2,4);
    
    return makeActualMove(fromPosition, toPosition)
}

// helper functions
function makeActualMove(fromPosition, toPosition)
{
    var res;
    var color;

    if (checkPromotion(fromPosition))
    {
        res = chess.move({from: fromPosition, to: toPosition, promotion: 'q'});
    } else {
        res = chess.move({ from: fromPosition, to: toPosition });
    }

    if (res != null) {
        color = res['color'];
    
        // update king position if it is moved
        if (res['piece'] == 'k') {
            if (color == 'w') {
                whiteKingPosition = toPosition;
            } else {
                blackKingPosition = toPosition;
            }
        }
    }

    console.log("MakeMove: " + color);
    console.log("WhiteKingPos: " + whiteKingPosition);
    console.log("BlackKingPos: " + blackKingPosition);
    console.log("FromPosition: " + fromPosition);
    console.log("ToPosition: " + toPosition);
    console.log("Result: ");
    console.log(res);

    var cmd = new proto.server.SrvMoveResult();
    cmd.setId(CommandID.SrvMoveResult);
    
    if (res != null) {
        cmd.setResult(MOVE_RESULT_OK);
        cmd.setFromindex(ChessMovesParser.ParseMoveToTableUIIndex(fromPosition));
        cmd.setToindex(ChessMovesParser.ParseMoveToTableUIIndex(toPosition));
        cmd.setFen(chess.fen());
        cmd.setColor(color);
        cmd.setCapture(res['captured']);
        cmd.setFlags(res['flags']);

        if (chess.in_check())
        {
            cmd.setOppcheck('check');
            if (color == 'w')
                cmd.setOppkingpos(ChessMovesParser.ParseMoveToTableUIIndex(blackKingPosition));
            else
                cmd.setOppkingpos(ChessMovesParser.ParseMoveToTableUIIndex(whiteKingPosition));
        }
        if (chess.in_checkmate()) {
            cmd.setOppcheck('checkmate');
        }
        if (chess.in_stalemate()) {
            cmd.setOppcheck('stalemate');
        }
    }
    else {
        cmd.setResult(MOVE_RESULT_FAIL);
    }

    return cmd;
}

function checkKingSideCastling(moveString)
{
    var res = moveString.includes(KING_CASTLING);
    var len = moveString.length < QUEEN_CASTLING.length;
    return res && len;
}

function checkQueenSideCastling(moveString)
{
    return moveString.includes(QUEEN_CASTLING);
}


// var fen = "rnbqk2r/pppppppp/4bn2/P7/2N1PP2/1BQB1NP1/1PPP3P/R3K2R b KQkq - 1 1";
// var chess = new Chess(fen);

// console.log(chess.ascii());
// console.log(chess.fen());

// chess.move('b5');

// console.log(chess.ascii());

// var moves = chess.moves({square: 'a5'});

// console.log(moves);

// while (!chess.game_over()) {
//     var moves = chess.moves();
//     var move = moves[Math.floor(Math.random() * moves.length)];
//     chess.move(move);
//     console.log(chess.ascii());
//     console.log(chess.fen());
// }

// console.log("PNG");
// console.log(chess.pgn());

