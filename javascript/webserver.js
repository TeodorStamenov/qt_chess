"use strict";

var WebSocketServer = require('websocket').server;
var http = require('http');
var parser = require('./commandparser');

var webSocketServerPort = 1337;


var server = http.createServer(function(req,res) {});
server.listen(webSocketServerPort, function() {
	console.log((new Date()) + " Server is listening on port " + webSocketServerPort);
});

var wsServer = new WebSocketServer({
	httpServer: server
});

wsServer.on('request', function(req) {
	console.log((new Date()) + " Connection from origin " + req.origin + ".");

	var connection = req.accept(null, req.origin);
	connection.binaryType = "arraybuffer";

	console.log((new Date()) + " Connection accepted.");

	connection.on('message', function incoming(message) {
		var bytes = Array.prototype.slice.call(message.binaryData, 0);
		var responseCmd = parser.parseCommand(bytes);

		var bytesResponse = responseCmd.serializeBinary();
		var buf = new Buffer(bytesResponse);
		connection.sendBytes(buf);
	});

	connection.on('close', function(connection) {
		// close user connection
		console.log((new Date()) + " Peer " + connection.remoteAddress + " disconnected.");
	});
});