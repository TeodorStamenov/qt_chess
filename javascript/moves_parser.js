
exports.ParseMoveFromTableUIIndex = function(index)
{
    var row = 8 - parseInt(index / 8);
    var col = index % 8;
    
    var letters = 'abcdefgh';
    var move = letters[col] + row;

    return move;
};

exports.ParseMoveToTableUIIndex = function(move)
{
    var cIndex = 0;
    var rIndex = 1;
    
    // Letter 'N' or 'n'  represent that the figure is a knight
    // This letter is meaningless for the algorithm
    // RegularMove: g4 vs KnightMove: Ng4
    var indexOfX = move.indexOf('x');
    var indexOfEqual = move.indexOf('=');
    var indexOfPlus = move.indexOf('+');
    var indexOfNum = move.indexOf('#');

    var specialSymbolIndex = Math.max(indexOfEqual, indexOfPlus, indexOfNum);

    if (indexOfX != -1) {
        cIndex = indexOfX + 1;
        rIndex = indexOfX + 2;
    }
    else if (specialSymbolIndex != -1) {
        cIndex = specialSymbolIndex - 2;
        rIndex = specialSymbolIndex - 1;
    }
    else if (move.length == 3) {
        cIndex = 1;
        rIndex = 2;
    } else if (move.length == 4) {
        cIndex = 2;
        rIndex = 3;
    }
    
    try {
        var charCode = move[cIndex].toUpperCase().charCodeAt();
        var c = parseInt(String.fromCharCode(charCode - 17));
        var r = parseInt(move[rIndex]);
        var index = (8 - r) * 8 + c;
        return index;
    } catch (err) {
        console.log("Error: " + err);
        console.log("move: " + move)
        console.log("cIndex: " + cIndex);
        console.log("rIndex: " + rIndex);
    }

    return -1;
};

exports.KingSideCastling = function(moves, color)
{
    if (color == "w") {
        moves.push(module.exports.ParseMoveToTableUIIndex("f1"));
        moves.push(module.exports.ParseMoveToTableUIIndex("g1"));
    } else {
        moves.push(module.exports.ParseMoveToTableUIIndex("f8"));
        moves.push(module.exports.ParseMoveToTableUIIndex("g8"));
    }
};

exports.QueenSideCastling = function(moves, color)
{
    if (color == "w") {
        moves.push(module.exports.ParseMoveToTableUIIndex("d1"));
        moves.push(module.exports.ParseMoveToTableUIIndex("c1"));
    } else {
        moves.push(module.exports.ParseMoveToTableUIIndex("d8"));
        moves.push(module.exports.ParseMoveToTableUIIndex("c8"));
    }
};