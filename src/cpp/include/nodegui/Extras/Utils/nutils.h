#pragma once

#include <napi.h>

#include <QPointer>
#include <QVariant>

#include "Extras/Export/export.h"
#include "core/FlexLayout/flexutils.h"
#include "deps/yoga/YGNode.h"

namespace extrautils {
DLL_EXPORT QVariant* convertToQVariant(Napi::Env& env, Napi::Value& value);
DLL_EXPORT bool isNapiValueInt(Napi::Env& env, Napi::Value& num);
DLL_EXPORT std::string getNapiObjectClassName(Napi::Object& object);
DLL_EXPORT void* configureQWidget(QWidget* widget, bool isLeafNode = false);
DLL_EXPORT void* configureQObject(QObject* object);
DLL_EXPORT void* configureComponent(void* component);
DLL_EXPORT uint64_t hashPointerTo53bit(const void* input);

template <typename T>
void safeDelete(QPointer<T>& component) {
  if (!component.isNull() && component->QObject::parent() == nullptr) {
    delete component;
  }
}
}  // namespace extrautils

class DLL_EXPORT NUtilsWrap : public Napi::ObjectWrap<NUtilsWrap> {
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  NUtilsWrap(const Napi::CallbackInfo& info);
  static Napi::FunctionReference constructor;
};

namespace StaticNUtilsWrapMethods {
DLL_EXPORT Napi::Value isNapiExternal(const Napi::CallbackInfo& info);
}  // namespace StaticNUtilsWrapMethods

#ifndef NODEGUI_LOGGER_H
#define NODEGUI_LOGGER_H

#include <napi.h>

#include <string>

inline Napi::Value ToJsValue(Napi::Env env, const char* value) {
  return Napi::String::New(env, value);
}

inline Napi::Value ToJsValue(Napi::Env env, const std::string& value) {
  return Napi::String::New(env, value);
}

template <typename T>
inline Napi::Value ToJsValue(Napi::Env env, T value) {
  return Napi::Number::New(env, static_cast<double>(value));
}

#define CONSOLE_LOG(env, value)                                        \
  do {                                                                 \
    Napi::Env _env = (env);                                            \
    Napi::Object _global = _env.Global();                              \
    Napi::Object _console = _global.Get("console").As<Napi::Object>(); \
    Napi::Function _log = _console.Get("log").As<Napi::Function>();    \
    _log.Call(_console, {ToJsValue(_env, (value))});                   \
  } while (0)

#endif