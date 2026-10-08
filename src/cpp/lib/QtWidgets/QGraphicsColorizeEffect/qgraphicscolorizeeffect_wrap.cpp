#include "QtWidgets/QGraphicsColorizeEffect/qgraphicscolorizeeffect_wrap.h"

#include "Extras/Utils/nutils.h"
#include "QtCore/QObject/qobject_wrap.h"
#include "QtGui/QColor/qcolor_wrap.h"
#include "QtWidgets/QWidget/qwidget_wrap.h"

Napi::FunctionReference QGraphicsColorizeEffectWrap::constructor;

Napi::Object QGraphicsColorizeEffectWrap::init(Napi::Env env,
                                               Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QGraphicsColorizeEffect";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {InstanceMethod("color", &QGraphicsColorizeEffectWrap::color),
       InstanceMethod("setColor", &QGraphicsColorizeEffectWrap::setColor),
       QGRAPHICSEFFECT_WRAPPED_METHODS_EXPORT_DEFINE(
           QGraphicsColorizeEffectWrap)});

  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

NGraphicsColorizeEffect* QGraphicsColorizeEffectWrap::getInternalInstance() {
  return this->instance;
}

QGraphicsColorizeEffectWrap::~QGraphicsColorizeEffectWrap() {
  extrautils::safeDelete(this->instance);
}

QGraphicsColorizeEffectWrap::QGraphicsColorizeEffectWrap(
    const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QGraphicsColorizeEffectWrap>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() == 1) {
    Napi::Object parentObject = info[0].As<Napi::Object>();
    QObjectWrap* parentObjectWrap =
        Napi::ObjectWrap<QObjectWrap>::Unwrap(parentObject);
    this->instance =
        new NGraphicsColorizeEffect(parentObjectWrap->getInternalInstance());
  } else if (info.Length() == 0) {
    this->instance = new NGraphicsColorizeEffect();
  } else {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
  }

  this->rawData = extrautils::configureQObject(this->getInternalInstance());
}

Napi::Value QGraphicsColorizeEffectWrap::color(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QColor color = this->instance->color();
  auto instance = QColorWrap::constructor.New(
      {Napi::External<QColor>::New(env, new QColor(color))});
  return instance;
}

Napi::Value QGraphicsColorizeEffectWrap::setColor(
    const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QColorWrap* colorWrap =
      Napi::ObjectWrap<QColorWrap>::Unwrap(info[0].As<Napi::Object>());
  QColor* col = colorWrap->getInternalInstance();
  this->instance->setColor(*col);

  return env.Null();
}