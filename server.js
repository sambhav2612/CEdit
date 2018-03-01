var express = require('express');
var fs = require('fs');

if (process.argv.length <= 2) {
	console.log("Usage: " + __filename + " path/to/directory");
	process.exit(-1);

} else {
	var app = express();
	var port = process.env.PORT || 3000;

	app.use(require('body-parser').urlencoded({ extended: true }));
	app.use(require('body-parser').json());

	var path = process.argv[2];
	var items;

	fs.readdir(path, function (err, content) {
		items = content;
		//console.log(items);
	});

	app.get('/', function (req, res) {
		//console.log(req);
		res.json({ "response": items });
	});

	if (app.listen(port)) {
		console.log('Server istening on port ' + port);
	}
}
