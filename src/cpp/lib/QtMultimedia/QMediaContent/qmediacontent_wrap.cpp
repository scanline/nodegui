#include "QtMultimedia/QMediaContent/qmediacontent_wrap.hpp"

#include "Extras/Utils/nutils.h"
#include "QtCore/QUrl/qurl_wrap.h"

Napi::FunctionReference QMediaContentWrap::constructor;

Napi::Object QMediaContentWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QMediaContent";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {// InstanceMethod("setColor", &QMediaContentWrap::setColor)
       InstanceMethod("canonicalUrl", &QMediaContentWrap::canonicalUrl),
       COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaContentWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

QMediaContentWrap::QMediaContentWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QMediaContentWrap>(info) {
  Napi::Env env = info.Env();
  if (info.Length() == 2) {
    // basiert teilweise auf qurl_wrap.cpp und qgraphicsblureffect_wrap.cpp so
    // mit isExternal und so ;) ursprünglich war da nur this->instance =
    // std::make_unique<QMediaContent>(); was auf qpen_wrap.cpp basiert
    // TODO!

    int32_t type = info[1].As<Napi::Number>().Int32Value();
    switch (type) {
      case 0:
        this->instance = std::unique_ptr<QMediaContent>(
            info[0].As<Napi::External<QMediaContent>>().Data());
        break;

      case 1:

        QUrlWrap* qurlWrap =
            Napi::ObjectWrap<QUrlWrap>::Unwrap(info[0].As<Napi::Object>());

        QUrl* qurl = qurlWrap->getInternalInstance();

        this->instance = std::make_unique<QMediaContent>(*qurl);
        break;
    }

  } else if (info.Length() == 1) {
    if (info[0].IsExternal()) {
      this->instance = std::unique_ptr<QMediaContent>(
          info[0].As<Napi::External<QMediaContent>>().Data());
    }
  } else {
    Napi::TypeError::New(
        env, "NodeGui: QMediaContentWrap: Wrong number of arguments")
        .ThrowAsJavaScriptException();
  }
  this->rawData = extrautils::configureComponent(this->getInternalInstance());
}

QMediaContentWrap::~QMediaContentWrap() { this->instance.reset(); }

QMediaContent* QMediaContentWrap::getInternalInstance() {
  return this->instance.get();
}

Napi::Value QMediaContentWrap::canonicalUrl(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QUrl qurl = this->instance->canonicalUrl();
  auto instance = QUrlWrap::constructor.New(
      {Napi::External<QUrl>::New(env, new QUrl(qurl))});
  return instance;
}