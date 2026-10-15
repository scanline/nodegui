#pragma once
#include <napi.h>

#include <QPointer>

#include "QtCore/QObject/qobject_macro.h"
#include "nmediaplayer.hpp"

class DLL_EXPORT QMediaPlayerWrap : public Napi::ObjectWrap<QMediaPlayerWrap> {
 private:
  QPointer<NMediaPlayer> instance;

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QMediaPlayerWrap(const Napi::CallbackInfo& info);
  NMediaPlayer* getInternalInstance();
  ~QMediaPlayerWrap();

  // Wrapped methods
  Napi::Value setPlaylist(const Napi::CallbackInfo& info);
  Napi::Value setVideoOutput(const Napi::CallbackInfo& info);
  Napi::Value setMedia(const Napi::CallbackInfo& info);
  Napi::Value play(const Napi::CallbackInfo& info);
  Napi::Value stop(const Napi::CallbackInfo& info);
  Napi::Value pause(const Napi::CallbackInfo& info);
  Napi::Value state(const Napi::CallbackInfo& info);
  QOBJECT_WRAPPED_METHODS_DECLARATION
  QMEDIAOBJECT_WRAPPED_METHODS_DECLARATION
};