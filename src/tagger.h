#ifndef __TAGGER_H__
#define __TAGGER_H__

#include <v8.h>
#include <node.h>
#include <node_events.h>
#include <mecab.h>
#include <stdio.h>

using namespace v8;

namespace MeCabBinding {

class Tagger : node::ObjectWrap {
public:

  static void Initialize(const Handle<Object> target);

  bool initialized();

  const char* Parse(const char* input);
  const mecab_node_t* ParseToNode(const char* input);

  Tagger(const char* arg);
  ~Tagger();

protected:

  static Handle<Value> New(const Arguments& args);

  static Handle<Value> Parse(const Arguments& args);
  static Handle<Value> ParseToNode(const Arguments& args);

  static Handle<Value> Version(const Arguments& args);

private:

  mecab_t* mecab;
  mecab_node_t* mecabNode;

};

} // namespace MeCabBinding

#endif // __TAGGER_H__