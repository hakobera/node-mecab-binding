var MeCab = require('../mecab'),
    assert = require('assert');

assert.equal('0.98', MeCab.Tagger.version());

var input = '今日もしないとね',
    m, result;

m = new MeCab.Tagger('-O wakati');
result = m.parse(input);

assert.equal('今日 も し ない と ね \n', result);
console.log(result);

m = new MeCab.Tagger('-O yomi');
result = m.parse(input);

assert.equal('キョウモシナイトネ\n', result);
console.log(result);