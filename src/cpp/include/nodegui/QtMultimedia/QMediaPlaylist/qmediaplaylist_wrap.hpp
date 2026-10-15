#pragma once
#include <napi.h>

#include <QMediaPlaylist>
#include <QPointer>

#include "QtCore/QObject/qobject_macro.h"

class DLL_EXPORT QMediaPlaylistWrap
    : public Napi::ObjectWrap<QMediaPlaylistWrap>,
      public EventWidget {
 private:
  QPointer<QMediaPlaylist> instance;
  QOBJECT_WRAPPED_METHODS_DECLARATION_WITH_EVENT_SOURCE(this)
  QOBJECT_SET_PARENT_IMPL
  // QOBJECT_WRAPPED_METHODS_DECLARATION <- old way before above

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QMediaPlaylistWrap(const Napi::CallbackInfo& info);
  QMediaPlaylist* getInternalInstance();

  virtual void connectSignalsToEventEmitter();
  // Wrapped methods
  Napi::Value addMedia(const Napi::CallbackInfo& info);
  Napi::Value clear(const Napi::CallbackInfo& info);
  Napi::Value isEmpty(const Napi::CallbackInfo& info);
  Napi::Value playbackMode(const Napi::CallbackInfo& info);
};