var MeCab = require('../mecab'),
    assert = require('assert');

assert.equal('0.98', MeCab.Tagger.version());

var input = '今日も',
    m, node, n1, n2, n3, n4;

m = new MeCab.Tagger();
node = m.parseToNode(input);

assert.equal(MeCab.MECAB_BOS_NODE, node.stat);
assert.equal('BOS/EOS,*,*,*,*,*,*,*,*', node.feature);

node = node.next();
assert.equal(MeCab.MECAB_NOR_NODE, node.stat);
assert.equal('名詞,副詞可能,*,*,*,*,今日,キョウ,キョー', node.feature);

node = node.next();
assert.equal(MeCab.MECAB_NOR_NODE, node.stat);
assert.equal('助詞,係助詞,*,*,*,*,も,モ,モ', node.feature);

node = node.next();
assert.equal(MeCab.MECAB_EOS_NODE, node.stat);
assert.equal('BOS/EOS,*,*,*,*,*,*,*,*', node.feature);

node = node.prev();
assert.equal(MeCab.MECAB_NOR_NODE, node.stat);
assert.equal('助詞,係助詞,*,*,*,*,も,モ,モ', node.feature);

node = node.next().next();
assert.equal(undefined, node);