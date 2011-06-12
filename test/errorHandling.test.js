var MeCab = require('../mecab'),
    assert = require('assert');

var input = '今日もしないとね';

assert.throws(function() {
	var m = new MeCab.Tagger('-d .');
  m.parse(input);
});