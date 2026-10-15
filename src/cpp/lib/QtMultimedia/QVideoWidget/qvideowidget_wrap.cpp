#include "QtMultimedia/QVideoWidget/qvideowidget_wrap.hpp"

#include <Extras/Utils/nutils.h>
#include <QtWidgets/QWidget/qwidget_wrap.h>

#include <QWidget>

Napi::FunctionReference QVideoWidgetWrap::constructor;

Napi::Object QVideoWidgetWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QVideoWidget";
  Napi::Function func =
      DefineClass(env, CLASSNAME,
                  {InstanceMethod("setAspectRatioMode",
                                  &QVideoWidgetWrap::setAspectRatioMode),
                   QWIDGET_WRAPPED_METHODS_EXPORT_DEFINE(QVideoWidgetWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

NVideoWidget* QVideoWidgetWrap::getInternalInstance() { return this->instance; }

QVideoWidgetWrap::QVideoWidgetWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QVideoWidgetWrap>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() == 1) {
    Napi::Object parentObject = info[0].As<Napi::Object>();
    QWidgetWrap* parentWidgetWrap =
        Napi::ObjectWrap<QWidgetWrap>::Unwrap(parentObject);
    this->instance = new NVideoWidget(parentWidgetWrap->getInternalInstance());
  } else if (info.Length() == 0) {
    this->instance = new NVideoWidget();
  } else {
    Napi::TypeError::New(env,
                         "NodeGui: QVideoWidget: Wrong number of arguments")
        .ThrowAsJavaScriptException();
  }
  this->rawData = extrautils::configureQWidget(
      this->getInternalInstance(),  // this->getInternalInstance()->getFlexNode(),
      true);
}

QVideoWidgetWrap::~QVideoWidgetWrap() {
  extrautils::safeDelete(this->instance);
}

Napi::Value QVideoWidgetWrap::setAspectRatioMode(
    const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  Napi::Number mode = info[0].As<Napi::Number>();
  this->instance->setAspectRatioMode(
      static_cast<Qt::AspectRatioMode>(mode.Int32Value()));
  return env.Null();
}