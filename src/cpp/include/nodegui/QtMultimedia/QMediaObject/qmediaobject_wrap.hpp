#pragma once
#include <napi.h>

#include <QMediaObject>
#include <QPointer>

#include "QtCore/QObject/qobject_macro.h"
#include "QtMultimedia/QMediaObject/qmediaobject_macro.h"

class DLL_EXPORT QMediaObjectWrap : public Napi::ObjectWrap<QMediaObjectWrap>,
                                    public EventWidget {
 private:
  // QOBJECT_WRAPPED_METHODS_DECLARATION
  // QMEDIAOBJECT_WRAPPED_METHODS_DECLARATION

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QMediaObjectWrap(const Napi::CallbackInfo& info);
  ~QMediaObjectWrap();

  virtual void connectSignalsToEventEmitter();
};