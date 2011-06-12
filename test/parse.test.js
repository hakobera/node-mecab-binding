var MeCab = require('../mecab'),
    assert = require('assert'),
    exec = require('child_process').exec,
    child;

child = exec('mecab -v', function(err, stdout, stderr) {
  console.log(stdout);
  assert.equal(stdout, 'mecab of ' + MeCab.Tagger.version() + '\n\n');
});

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