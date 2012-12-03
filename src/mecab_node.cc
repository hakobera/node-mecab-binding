#include "mecab_node.h"

#define SYMBOL(name) String::NewSymbol(name)

#define SURFACE_SYMBOL SYMBOL("surface")
#define FEATURE_SYMBOL SYMBOL("feature")
#define LENGTH_SYMBOL SYMBOL("length")
#define R_LENGTH_SYMBOL SYMBOL("rlength")
#define ID_SYMBOL SYMBOL("id")
#define RC_ATTR_SYMBOL SYMBOL("rcAttr")
#define LC_ATTR_SYMBOL SYMBOL("lcAttr")
#define POSID_SYMBOL SYMBOL("posid")
#define CHAR_TYPE_SYMBOL SYMBOL("charType")
#define STAT_SYMBOL SYMBOL("stat")
#define IS_BEST_SYMBOL SYMBOL("isbest")
#define ALPHA_SYMBOL SYMBOL("alpha")
#define BETA_SYMBOL SYMBOL("beta")
#define PROB_SYMBOL SYMBOL("prob")
#define WCOST_SYMBOL SYMBOL("wcost")
#define COST_SYMBOL SYMBOL("cost")

#define SET_GETTER(t, symbol, getter) t->PrototypeTemplate()->SetAccessor(symbol, getter);

using namespace v8;

namespace MeCabBinding {

Persistent<FunctionTemplate> Node::constructor_template;

void Node::Initialize(const Handle<Object> target)
{
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(SYMBOL("Node"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "next", Next);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "prev", Prev);

  SET_GETTER(constructor_template, SURFACE_SYMBOL, Getter);     // 形態素の文字列情報
  SET_GETTER(constructor_template, FEATURE_SYMBOL, Getter);     // CSV で表記された素性情報
  SET_GETTER(constructor_template, LENGTH_SYMBOL, Getter);      // 形態素の長さ
  SET_GETTER(constructor_template, R_LENGTH_SYMBOL, Getter);     // 形態素の長さ(先頭のスペースを含む)
  SET_GETTER(constructor_template, ID_SYMBOL, Getter);          // 形態素に付与される ユニークID
  SET_GETTER(constructor_template, RC_ATTR_SYMBOL, Getter);      // 右文脈 id
  SET_GETTER(constructor_template, LC_ATTR_SYMBOL, Getter);      // 左文脈 id
  SET_GETTER(constructor_template, POSID_SYMBOL, Getter);       // 形態素 ID
  SET_GETTER(constructor_template, CHAR_TYPE_SYMBOL, Getter);   // 文字種情報
  SET_GETTER(constructor_template, STAT_SYMBOL, Getter);        // 形態素の種類: 以下のマクロの値
  SET_GETTER(constructor_template, IS_BEST_SYMBOL, Getter);      // ベスト解の場合 1, それ以外 0
  SET_GETTER(constructor_template, ALPHA_SYMBOL, Getter);       // forward backward の foward log 確率
  SET_GETTER(constructor_template, BETA_SYMBOL, Getter);        // forward backward の backward log 確率
  SET_GETTER(constructor_template, PROB_SYMBOL, Getter);        // 周辺確率
  SET_GETTER(constructor_template, WCOST_SYMBOL, Getter);       // 単語生起コスト
  SET_GETTER(constructor_template, COST_SYMBOL, Getter);        // 累積コスト

  target->Set(SYMBOL("Node"), constructor_template->GetFunction());
}

Handle<Value> Node::New(const mecab_node_t* data)
{
  HandleScope scope;
  Local<Value> arg = Integer::NewFromUnsigned(0);
  Local<Object> obj = constructor_template->GetFunction()->NewInstance(1, &arg);

  Node* node = node::ObjectWrap::Unwrap<Node>(obj);
  node->setData(const_cast<mecab_node_t*>(data));

  return obj;
}

Node::~Node()
{
}

Handle<Value> Node::New(const Arguments& args)
{
  if (!args.IsConstructCall()) {
    return node::FromConstructorTemplate(constructor_template, args);
  }

  HandleScope scope;

  Node* node = new Node();
  node->Wrap(args.This());

  return args.This();
}

Handle<Value> Node::Getter(Local<String> property, const AccessorInfo& info)
{
  Node* self = node::ObjectWrap::Unwrap<Node>(info.This());

  HandleScope scope;

  mecab_node_t* node = self->data;

  if (property == SURFACE_SYMBOL) {
    return String::New( "" ); // this is broken
  } else if (property == FEATURE_SYMBOL) {
    return String::New(node->feature);
  } else if (property == LENGTH_SYMBOL) {
    return Int32::New(node->length);
  } else if (property == R_LENGTH_SYMBOL) {
    return Int32::New(node->rlength);
  } else if (property == ID_SYMBOL) {
    return Int32::New(node->id);
  } else if (property == RC_ATTR_SYMBOL) {
    return Int32::New(node->rcAttr);
  } else if (property == LC_ATTR_SYMBOL) {
    return Int32::New(node->lcAttr);
  } else if (property == POSID_SYMBOL) {
    return Int32::New(node->posid);
  } else if (property == CHAR_TYPE_SYMBOL) {
    return Int32::New(node->char_type);
  } else if (property == STAT_SYMBOL) {
    return Int32::New(node->stat);
  } else if (property == IS_BEST_SYMBOL) {
    return Int32::New(node->isbest);
  } else if (property == ALPHA_SYMBOL) {
    return Number::New(node->alpha);
  } else if (property == BETA_SYMBOL) {
    return Number::New(node->beta);
  } else if (property == PROB_SYMBOL) {
    return Number::New(node->prob);
  } else if (property == WCOST_SYMBOL) {
    return Int32::New(node->wcost);
  } else if (property == COST_SYMBOL) {
    return Int32::New(node->cost);
  } else {
    return ThrowException(Exception::Error(String::New("Invalid property name")));
  }
}

void Node::setData(mecab_node_t* node)
{
  data = node;
}

Handle<Value> Node::Next(const Arguments& args)
{
  Node* self = node::ObjectWrap::Unwrap<Node>(args.This());

  HandleScope scope;

  mecab_node_t* next = self->data->next;

  if (!next) {
    return scope.Close(Undefined());
  }

  return scope.Close(Node::New(next));
}

Handle<Value> Node::Prev(const Arguments& args)
{
  Node* self = node::ObjectWrap::Unwrap<Node>(args.This());

  HandleScope scope;

  mecab_node_t* prev = self->data->prev;

  if (!prev) {
    return scope.Close(Undefined());
  }

  return scope.Close(Node::New(prev));
}

} // namespace MeCabBinding
