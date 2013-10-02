node-mecab
==========

node-mecab is a very simple MeCab binding for Node.
Not all features are supported now. 


Requirement
===========

- Node.js >= 0.4.0
- MeCab >= 0.9.7


How to install
==============

You can install mecab-binding from npm repository.

	npm install mecab-binding

You can also make it yourself.

	git clone git://github.com/hakobera/node-mecab-binding
	cd node-mecab-binding
	npm install -g
	npm link


How to use
==========

Simple analyze
--------------

Create Mecab.Tagger instance and call parse() method. You can get a result as string.
Mecab.Tagger constuctor arguments is same as executable mecab command line interface. 

	var MeCab = require('mecab-binding');
	var m = new MeCab.Tagger('-O wakati');
	console.log(m.parse('今日もしないとね'));

This is similar to other language binding.
http://mecab.sourceforge.net/bindings.html

Mecab.Taggerhttp://mecab.sourceforge.net/mecab.html constuctor arguments is same as executable mecab command line interface listed below.

http://mecab.sourceforge.net/mecab.html

Get more information for each word
----------------------------------

When you call parseToNode() method, you can get special morpheme as Mecab.Node instance. 

	var MeCab = require('mecab-binding');
	var m = new MeCab.Tagger('');

	var n = m.parseToNode('今日もしないとね');
	for (; n; n = n.next()) {
		console.log("%s\t%d", n.feature, n.cost);
	}

Currently, node.surface value cannot get correctly. If your focus is on surface and feature information, you can either use the parse() or the new parseToArray() method:

	var arr = m.parseToArray('今日もしないとね');
	for (var i = 0; i < arr.length; i += 2) {
		console.log('Surface: %s\tFeature: %s', arr[i], arr[i + 1]);
	}

Error handling
--------------

If error has occurred, mecab-binding throws Error.
So, if you want to handle it, write try-catch block.

	var MeCab = require('mecab-binding');

	try {
		var m = new MeCab.Tagger('-d .');
		console.log(m.parse('今日もしないとね'));
	} catch (e) {
	  console.log('Illegal argument error occurred.');
		console.log(e);
	}

LICENSE
=======
The MIT License

Copyright 2011 Kazuyuki Honda <hakobera@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
