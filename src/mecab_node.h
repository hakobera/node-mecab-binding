#ifndef __MECAB_NODE_H__
#define __MECAB_NODE_H__

#include <v8.h>
#include <node.h>
#include <mecab.h>

using namespace v8;

namespace MeCabBinding {

class Node : node::ObjectWrap
{
public:

  static void Initialize(const Handle<Object> target);
  static Handle<Value> New(const mecab_node_t* data);

  Node() : node::ObjectWrap() {}
  ~Node();

protected:

  static Handle<Value> New(const Arguments& args);
  static Handle<Value> Next(const Arguments& args);
  static Handle<Value> Prev(const Arguments& args);

  static Handle<Value> Getter(Local<String> property, const AccessorInfo& info);

  void setData(mecab_node_t* data);
  
  static Persistent<FunctionTemplate> constructor_template;

private:

  mecab_node_t* data;

};

} // namespace MeCabBinding

#endif // __MECAB_NODE_H__