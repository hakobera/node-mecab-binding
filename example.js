var MeCab = require('./mecab');

var input = '今日もしないとね',
    m, node;

// Simple
m = new MeCab.Tagger();
console.log(m.parse(input));

m = new MeCab.Tagger('-O wakati');
console.log(m.parse(input));

// Use node
node = m.parseToNode(input);
for (; node; node = node.next()) {
  console.log("%s\t%s\t%d",
                    node.surface,
                    node.feature,
                    node.charType);
}

// Error Handling
try {
  var m = new MeCab.Tagger('-d .');
  console.log(m.parse(input));
} catch (e) {
  console.log(e);
}

