/*
 * MeCab binding for Node.
 * Interface name is compatible to MeCab C++ library.
 *
 * @see http://mecab.sourceforge.net/
 * @see http://mecab.sourceforge.net/libmecab.html
 */

#include <v8.h>
#include <node.h>
#include <mecab.h>

#include "mecab_node.h"
#include "tagger.h"

using namespace v8;

extern "C"
void init (Handle<Object> target)
{
  HandleScope scope;
  MeCabBinding::Node::Initialize(target);
  MeCabBinding::Tagger::Initialize(target);
}