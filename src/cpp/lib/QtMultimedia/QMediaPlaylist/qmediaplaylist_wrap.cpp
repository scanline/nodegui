#include "QtMultimedia/QMediaPlaylist/qmediaplaylist_wrap.hpp"

#include <QtCore/QObject/qobject_wrap.h>

#include "Extras/Utils/nutils.h"
#include "QtMultimedia/QMediaContent/qmediacontent_wrap.hpp"
// #include <QMediaContent>
Napi::FunctionReference QMediaPlaylistWrap::constructor;

Napi::Object QMediaPlaylistWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QMediaPlaylist";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {InstanceMethod("addMedia", &QMediaPlaylistWrap::addMedia),
       InstanceMethod("clear", &QMediaPlaylistWrap::clear),
       InstanceMethod("isEmpty", &QMediaPlaylistWrap::isEmpty),
       InstanceMethod("playbackMode", &QMediaPlaylistWrap::playbackMode),
       QOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaPlaylistWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(QMediaPlaylist, QMediaPlaylistWrap);
  return exports;
}

QMediaPlaylistWrap::QMediaPlaylistWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QMediaPlaylistWrap>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  if (info.Length() == 1) {
    if (info[0].IsExternal()) {
      this->instance = info[0].As<Napi::External<QMediaPlaylist>>().Data();

    } else {
      Napi::Object parentObject = info[0].As<Napi::Object>();
      QObjectWrap* parentObjectWrap =
          Napi::ObjectWrap<QObjectWrap>::Unwrap(parentObject);
      this->instance =
          new QMediaPlaylist(parentObjectWrap->getInternalInstance());
    }
  } else if (info.Length() == 0) {
    this->instance = new QMediaPlaylist();
  } else {
    Napi::TypeError::New(env,
                         "NodeGui: QMediaPlaylist: Wrong number of arguments")
        .ThrowAsJavaScriptException();
  }
  this->rawData = extrautils::configureComponent(this->getInternalInstance());
}

QMediaPlaylist* QMediaPlaylistWrap::getInternalInstance() {
  return this->instance;
}

void QMediaPlaylistWrap::connectSignalsToEventEmitter() {
  QOBJECT_SIGNALS_ON_TARGET(this->instance.data());

  QObject::connect(
      this->instance.data(), &QMediaPlaylist::currentIndexChanged,
      [=](int position) {
        Napi::Env env = this->emitOnNode.Env();

        Napi::HandleScope scope(env);
        this->emitOnNode.Call({Napi::String::New(env, "currentIndexChanged"),
                               Napi::Number::New(env, position)});
      });

  QObject::connect(this->instance.data(), &QMediaPlaylist::loadFailed, [=]() {
    Napi::Env env = this->emitOnNode.Env();
    Napi::HandleScope scope(env);
    this->emitOnNode.Call({Napi::String::New(env, "loadFailed")});
  });

  QObject::connect(this->instance.data(), &QMediaPlaylist::loaded, [=]() {
    Napi::Env env = this->emitOnNode.Env();
    Napi::HandleScope scope(env);
    this->emitOnNode.Call({Napi::String::New(env, "loaded")});
  });

  QObject::connect(
      this->instance.data(), &QMediaPlaylist::mediaAboutToBeInserted,
      [=](int start, int end) {
        Napi::Env env = this->emitOnNode.Env();
        Napi::HandleScope scope(env);
        this->emitOnNode.Call({Napi::String::New(env, "mediaAboutToBeInserted"),
                               Napi::Number::New(env, start),
                               Napi::Number::New(env, end)});
      });

  QObject::connect(
      this->instance.data(), &QMediaPlaylist::mediaAboutToBeRemoved,
      [=](int start, int end) {
        Napi::Env env = this->emitOnNode.Env();
        Napi::HandleScope scope(env);
        this->emitOnNode.Call({Napi::String::New(env, "mediaAboutToBeRemoved"),
                               Napi::Number::New(env, start),
                               Napi::Number::New(env, end)});
      });

  QObject::connect(
      this->instance.data(), &QMediaPlaylist::mediaChanged,
      [=](int start, int end) {
        Napi::Env env = this->emitOnNode.Env();
        Napi::HandleScope scope(env);
        this->emitOnNode.Call({Napi::String::New(env, "mediaChanged"),
                               Napi::Number::New(env, start),
                               Napi::Number::New(env, end)});
      });

  QObject::connect(
      this->instance.data(), &QMediaPlaylist::mediaInserted,
      [=](int start, int end) {
        Napi::Env env = this->emitOnNode.Env();
        Napi::HandleScope scope(env);
        this->emitOnNode.Call({Napi::String::New(env, "mediaInserted"),
                               Napi::Number::New(env, start),
                               Napi::Number::New(env, end)});
      });

  QObject::connect(
      this->instance.data(), &QMediaPlaylist::mediaRemoved,
      [=](int start, int end) {
        Napi::Env env = this->emitOnNode.Env();
        Napi::HandleScope scope(env);
        this->emitOnNode.Call({Napi::String::New(env, "mediaRemoved"),
                               Napi::Number::New(env, start),
                               Napi::Number::New(env, end)});
      });

  QObject::connect(
      this->instance.data(), &QMediaPlaylist::currentMediaChanged,
      [=](const QMediaContent& content) {
        Napi::Env env = this->emitOnNode.Env();
        Napi::HandleScope scope(env);
        auto instance = QMediaContentWrap::constructor.New(
            {Napi::External<QMediaContent>::New(env,
                                                new QMediaContent(content))});
        this->emitOnNode.Call(
            {Napi::String::New(env, "currentMediaChanged"), instance});
      });
}

Napi::Value QMediaPlaylistWrap::addMedia(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Object mediaContentObject = info[0].As<Napi::Object>();
  QMediaContentWrap* mediaContentWrap =
      Napi::ObjectWrap<QMediaContentWrap>::Unwrap(mediaContentObject);
  QMediaContent* content = mediaContentWrap->getInternalInstance();

  return Napi::Boolean::New(env, this->instance->addMedia(*content));
}

Napi::Value QMediaPlaylistWrap::clear(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::Boolean::New(env, this->instance->clear());
}

Napi::Value QMediaPlaylistWrap::isEmpty(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::Boolean::New(env, this->instance->isEmpty());
}

Napi::Value QMediaPlaylistWrap::playbackMode(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QMediaPlaylist::PlaybackMode mode = this->instance->playbackMode();
  return Napi::Value::From(env, static_cast<int>(mode));
}