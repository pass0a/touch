var fs = require('fs-extra');
var path = require('path');
fs
	.copy('../output/node_modules/fb/', path.resolve(__dirname, 'dist/src'))
	.then(() => {
		console.log('copy core success!');
	})
	.catch((err) => {
		console.error(err);
	});
