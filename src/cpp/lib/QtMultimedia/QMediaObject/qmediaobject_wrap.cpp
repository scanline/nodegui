#include "Extras/Utils/nutils.h"
#include "QtCore/QObject/qobject_wrap.h"
#include "QtMultimedia/QMediaObject/qmediaobject_wrap.hpp"
#include "QtMultimedia/QMediaObject/qmediaobject_macro.h"
#include "core/WrapperCache/wrappercache.h"

Napi::FunctionReference QMediaObjectWrap::constructor;
Napi::Object QMediaObjectWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QMediaObject";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {// QOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaObjectWrap)
       /* QMEDIAOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaObjectWrap)*/});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(QMediaObject, QMediaObjectWrap);
  return exports;
}
QMediaObjectWrap::QMediaObjectWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QMediaObjectWrap>(info) {}
QMediaObjectWrap::~QMediaObjectWrap() {}

void QMediaObjectWrap::connectSignalsToEventEmitter() {
  /* QOBJECT_SIGNALS_ON_TARGET(this->instance.data());
   QMEDIAOBJECT_SIGNALS_ON_TARGET(this->instance.data());*/
}