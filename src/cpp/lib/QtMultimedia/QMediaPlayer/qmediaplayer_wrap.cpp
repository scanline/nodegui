#include "QtMultimedia/QMediaPlayer/qmediaplayer_wrap.hpp"

#include <QtCore/QUrl/qurl_wrap.h>

#include "Extras/Utils/nutils.h"
#include "QtCore/QVariant/qvariant_wrap.h"
#include "QtMultimedia/QMediaObject/qmediaobject_macro.h"
#include "QtMultimedia/QMediaPlaylist/qmediaplaylist_wrap.hpp"
#include "QtMultimedia/QVideoWidget/qvideowidget_wrap.hpp"

Napi::FunctionReference QMediaPlayerWrap::constructor;

Napi::Object QMediaPlayerWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QMediaPlayer";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {InstanceMethod("setVideoOutput", &QMediaPlayerWrap::setVideoOutput),
       InstanceMethod("setPlaylist", &QMediaPlayerWrap::setPlaylist),
       InstanceMethod("setMedia", &QMediaPlayerWrap::setMedia),
       InstanceMethod("play", &QMediaPlayerWrap::play),
       InstanceMethod("stop", &QMediaPlayerWrap::stop),
       InstanceMethod("pause", &QMediaPlayerWrap::pause),
       InstanceMethod("state", &QMediaPlayerWrap::state),
       /*
        InstanceMethod("initNodeEventEmitter",
&QMediaPlayerWrap::initNodeEventEmitter),
InstanceMethod("getNodeEventEmitter",
&QMediaPlayerWrap::getNodeEventEmitter),
InstanceMethod("subscribeToQtEvent",
&QMediaPlayerWrap::subscribeToQtEvent),
InstanceMethod("unSubscribeToQtEvent",
&QMediaPlayerWrap::unSubscribeToQtEvent),
       */
       QMEDIAOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaPlayerWrap)
           QOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaPlayerWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

NMediaPlayer* QMediaPlayerWrap::getInternalInstance() { return this->instance; }

QMediaPlayerWrap::QMediaPlayerWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QMediaPlayerWrap>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() == 1) {
    if (info[0].IsExternal()) {
      this->instance = info[0].As<Napi::External<NMediaPlayer>>().Data();
      // Instance was created elsewhere and shared with us.
    } else {
      Napi::Object parentObject = info[0].As<Napi::Object>();
      QObjectWrap* parentObjectWrap =
          Napi::ObjectWrap<QObjectWrap>::Unwrap(parentObject);
      this->instance =
          new NMediaPlayer(parentObjectWrap->getInternalInstance());
    }
  } else if (info.Length() == 0) {
    this->instance = new NMediaPlayer();
  } else {
    Napi::TypeError::New(env,
                         "qmediaplayer_wrap.cpp: Wrong number of arguments")
        .ThrowAsJavaScriptException();
  }
  this->rawData = extrautils::configureComponent(this->getInternalInstance());
}

QMediaPlayerWrap::~QMediaPlayerWrap() {
  extrautils::safeDelete(this->instance);
}

Napi::Value QMediaPlayerWrap::setVideoOutput(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  Napi::Object videoObject = info[0].As<Napi::Object>();

  QVideoWidgetWrap* videoWidgetWrap =
      Napi::ObjectWrap<QVideoWidgetWrap>::Unwrap(videoObject);
  // Napi::TypeError::New(env, "bin eine message").ThrowAsJavaScriptException();
  this->instance->setVideoOutput(
      static_cast<QVideoWidget*>(videoWidgetWrap->getInternalInstance()));
  return env.Null();
}

Napi::Value QMediaPlayerWrap::setPlaylist(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::HandleScope scope(env);
  Napi::Object playlistObject = info[0].As<Napi::Object>();
  QMediaPlaylistWrap* playlistWrap =
      Napi::ObjectWrap<QMediaPlaylistWrap>::Unwrap(playlistObject);
  QMediaPlaylist* playlist = playlistWrap->getInternalInstance();
  this->instance->setPlaylist(
      playlist);  // NOTE LOOK:
                  // https://codebrowser.dev/qt5/qtmultimedia/src/multimedia/playback/qmediaplayer.cpp.html#747
  return env.Null();
}

Napi::Value QMediaPlayerWrap::setMedia(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  // Napi::TypeError::New(env, "yeah").ThrowAsJavaScriptException();
  Napi::Object mediaObject = info[0].As<Napi::Object>();
  QUrlWrap* mediaWrap = Napi::ObjectWrap<QUrlWrap>::Unwrap(mediaObject);
  this->instance->setMedia(*mediaWrap->getInternalInstance());
  return env.Null();
}

Napi::Value QMediaPlayerWrap::play(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  this->instance->play();
  return env.Null();
}

Napi::Value QMediaPlayerWrap::stop(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  this->instance->stop();
  return env.Null();
}

Napi::Value QMediaPlayerWrap::pause(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  this->instance->pause();
  return env.Null();
}

Napi::Value QMediaPlayerWrap::state(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QMediaPlayer::State state = this->instance->state();
  return Napi::Value::From(env, static_cast<int>(state));
}