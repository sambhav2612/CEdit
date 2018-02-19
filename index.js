var fs = require('fs');

if (process.argv.length <= 2) {
    console.log("Usage: " + __filename + " path/to/directory");
    process.exit(-1);
}

var path = process.argv[2];
var root = document.getElementsById('root');

var list = document.createElement('div');
list.setAttribute('class', 'container-fluid');
root.appendChild(list);

var listOl = document.createElement('ol');
list.appendChild(listOl);

fs.readdir(path, function (err, items) {
    var listLi = document.createElement('li');
    listLi.innerText = items;

    listOl.appendChild(listLi);

    /*for (var i = 0; i < items.length; i++) {
        console.log(items[i]);
    }*/
});
