var express = require('express');
var fs = require('fs');

if (process.argv.length <= 2) {
	console.log("Usage: " + __filename + " path/to/directory");
	process.exit(-1);

} else {
	var app = express();
	var server = app.listen(3000);

	if (server) {
		console.log('Server istening on port 3000');
	}

	var path = process.argv[2];
	var items;

	fs.readdir(path, function (err, content) {
		items = content;
	});

	app.use(express.static('/'));

	app.get('/', print);

	function print(request, response) {
		response.send(items);
	}
}
