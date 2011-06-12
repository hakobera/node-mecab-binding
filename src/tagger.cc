#include "tagger.h"
#include "mecab_node.h"

using namespace v8;

namespace MeCabBinding {

void Tagger::Initialize(const Handle<Object> target)
{
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(New);

  //t->Inherit(EventEmitter::constructor_template);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(t, "parse", Parse);
  NODE_SET_PROTOTYPE_METHOD(t, "parseToNode", ParseToNode);

  NODE_SET_METHOD(t->GetFunction(), "version", Version);

  target->Set(String::NewSymbol("Tagger"), t->GetFunction());
}

bool Tagger::initialized()
{
  return mecab != NULL;
}

const char* Tagger::Parse(const char* input)
{
  const char* result = mecab_sparse_tostr(mecab, input);
  return result;
}

const mecab_node_t* Tagger::ParseToNode(const char* input)
{
  const mecab_node_t* result = mecab_sparse_tonode(mecab, input);
  return result;
}

Handle<Value> Tagger::New(const Arguments& args)
{
  v8::HandleScope scope;

  Local<String> arg = String::New("");
  if (args.Length() > 0) {
    if (!args[0]->IsString()) {
      return ThrowException(Exception::Error(String::New("Must give a string to MeCab")));
    }
    arg = args[0]->ToString();
  }

  String::Utf8Value mecabOptions(arg);
  Tagger* tagger = new Tagger(*mecabOptions);
  if (!tagger->initialized()) {
    return ThrowException(Exception::Error(String::New("Failed to create MeCab")));
  }

  tagger->Wrap(args.This());

  return args.This();
}

Tagger::Tagger(const char* arg) : ObjectWrap()
{
  mecab = mecab_new2(arg);
}

Tagger::~Tagger()
{
  mecab_destroy(mecab);
  mecab = NULL;
}

Handle<Value> Tagger::Parse(const Arguments& args)
{
  Tagger* tagger = node::ObjectWrap::Unwrap<Tagger>(args.This());

  HandleScope scope;

  if (args.Length() == 0 || !args[0]->IsString()) {
    return ThrowException(Exception::Error(String::New("Must give input string as argument in parse()")));
  }

  String::Utf8Value input(args[0]->ToString());

  const char* result = tagger->Parse(*input);
  if (result == NULL) {
      return ThrowException(Exception::Error(String::New(mecab_strerror(tagger->mecab))));
  }

  return scope.Close(String::New(result));
}

Handle<Value> Tagger::ParseToNode(const Arguments& args)
{
  Tagger* tagger = node::ObjectWrap::Unwrap<Tagger>(args.This());

  HandleScope scope;

  if (args.Length() == 0 || !args[0]->IsString()) {
    return ThrowException(Exception::Error(String::New("Must give input string as argument in parse()")));
  }

  String::Utf8Value input(args[0]->ToString());

  const mecab_node_t* result = tagger->ParseToNode(*input);

  if (result == NULL) {
      return ThrowException(Exception::Error(String::New(mecab_strerror(tagger->mecab))));
  }

  return scope.Close(Node::New(result));
}

Handle<Value> Tagger::Version(const Arguments& args)
{
  HandleScope scope;

  Local<String> version = String::New(mecab_version());

  return scope.Close(version);
}

} // namespace MeCabBinding