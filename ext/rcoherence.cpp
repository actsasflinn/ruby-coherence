#include <rcoherence.h>

using namespace coherence::lang;
using coherence::net::CacheFactory;
using coherence::net::NamedCache;
using coherence::util::Iterator;

static NamedCache::Handle getCache(VALUE vself) {
  String::View vsCacheName = RSTRING_PTR(rb_iv_get(vself, "@cache_name"));
  NamedCache::Handle hCache = CacheFactory::getCache(vsCacheName);
  return hCache;
}

static VALUE cNamedCache_put(VALUE vself, VALUE vkey, VALUE vval){
  NamedCache::Handle hCache = getCache(vself);

  String::View vsKey = RSTRING_PTR(vkey);
  String::View vsValue = RSTRING_PTR(vval);

  try {
    hCache->put(vsKey, vsValue);
  } catch (const std::exception& e) {
    // don't throw anything just yet
    // std::cerr << "error: " << e.what() << std::endl;
  }

  return Qtrue;
}

static VALUE cNamedCache_get(VALUE vself, VALUE vkey){
  VALUE vval = Qnil;
  NamedCache::Handle hCache = getCache(vself);

  String::View vsKey = RSTRING_PTR(vkey);
  try {
    String::View vsGet = cast<String::View>(hCache->get(vsKey));
    vval = rb_str_new2(vsGet->getCString());
  } catch (const std::exception& e) {
    // don't throw anything just yet
    // std::cerr << "error: " << e.what() << std::endl;
  }

  return vval;
}

static VALUE cNamedCache_delete(VALUE vself, VALUE vkey){
  NamedCache::Handle hCache = getCache(vself);

  String::View vsKey = RSTRING_PTR(vkey);
  try {
    hCache->remove(vsKey);
  } catch (const std::exception& e) {
    // don't throw anything just yet
    // std::cerr << "error: " << e.what() << std::endl;
  }

  return Qnil;
}

static VALUE cNamedCache_size(VALUE vself){
  NamedCache::Handle hCache = getCache(vself);

  VALUE vsize = INT2NUM(hCache->size());

  return vsize;
}

static VALUE cNamedCache_clear(VALUE vself){
  NamedCache::Handle hCache = getCache(vself);

  hCache->clear();

  return Qnil;
}

static VALUE cNamedCache_keys(VALUE vself){
  VALUE vary = rb_ary_new();
  NamedCache::Handle hCache = getCache(vself);

  for (Iterator::Handle hIter = hCache->entrySet()->iterator();
       hIter->hasNext(); )
  {
    Map::Entry::View vEntry = cast<Map::Entry::View>(hIter->next());
    String::View vKey = cast<String::View>(vEntry->getKey());
    rb_ary_push(vary, rb_str_new2(vKey->getCString()));
  }

  return vary;
}

static VALUE cNamedCache_values(VALUE vself){
  NamedCache::Handle hCache = getCache(vself);
  VALUE vary = rb_ary_new();

  for (Iterator::Handle hIter = hCache->entrySet()->iterator();
       hIter->hasNext(); )
  {
    Map::Entry::View vEntry = cast<Map::Entry::View>(hIter->next());
    String::View vValue = cast<String::View>(vEntry->getValue());
    rb_ary_push(vary, rb_str_new2(vValue->getCString()));
  }

  return vary;
}

static VALUE cNamedCache_each(VALUE vself){
  if(!rb_block_given_p()) rb_raise(rb_eArgError, "no block given");

  NamedCache::Handle hCache = getCache(vself);
  VALUE vrv;

  for (Iterator::Handle hIter = hCache->entrySet()->iterator();
       hIter->hasNext(); )
  {
    Map::Entry::View vEntry = cast<Map::Entry::View>(hIter->next());
    String::View vKey = cast<String::View>(vEntry->getKey());
    String::View vValue = cast<String::View>(vEntry->getValue());
    vrv = rb_yield_values(2, rb_str_new2(vKey->getCString()), rb_str_new2(vValue->getCString()));
  }

  return vrv;
}

static VALUE cNamedCache_initialize(int argc, VALUE *argv, VALUE vself){
  VALUE cache_name;

  rb_scan_args(argc, argv, "01", &cache_name);
  if(NIL_P(cache_name)) cache_name = rb_str_new2("local-hello");
  rb_iv_set(vself, "@cache_name", cache_name);

  return Qtrue;
}

VALUE mCoherence;
VALUE cNamedCache;

extern "C" void Init_coherence() {
  mCoherence = rb_define_module("Coherence");
  rb_define_private_method(mCoherence, "initialize", (VALUE(*)(...))cNamedCache_initialize, -1);

  cNamedCache = rb_define_class_under(mCoherence, "NamedCache", rb_cObject);
  rb_include_module(cNamedCache, mCoherence);

  rb_define_method(cNamedCache, "put", (VALUE(*)(...))cNamedCache_put, 2);
  rb_define_alias(cNamedCache, "[]=", "put");
  rb_define_method(cNamedCache, "get", (VALUE(*)(...))cNamedCache_get, 1);
  rb_define_alias(cNamedCache, "[]", "get");
  rb_define_method(cNamedCache, "size", (VALUE(*)(...))cNamedCache_size, 0);
  rb_define_method(cNamedCache, "clear", (VALUE(*)(...))cNamedCache_clear, 0);
  rb_define_method(cNamedCache, "delete", (VALUE(*)(...))cNamedCache_delete, 1);
  rb_define_method(cNamedCache, "keys", (VALUE(*)(...))cNamedCache_keys, 0);
  rb_define_method(cNamedCache, "values", (VALUE(*)(...))cNamedCache_values, 0);
  rb_define_method(cNamedCache, "each", (VALUE(*)(...))cNamedCache_each, 0);
}
