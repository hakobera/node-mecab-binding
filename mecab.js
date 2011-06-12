var MeCab = require('./build/default/binding');

MeCab.MECAB_NOR_NODE = 0;
MeCab.MECAB_UNK_NODE = 1;
MeCab.MECAB_BOS_NODE = 2;
MeCab.MECAB_EOS_NODE = 3;

module.exports = MeCab;