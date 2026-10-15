#pragma once
#include <QtWidgets/QWidget/qwidget_macro.h>
#include <napi.h>

#include <QPointer>

#include "Extras/Export/export.h"
#include "nvideowidget.hpp"

class DLL_EXPORT QVideoWidgetWrap : public Napi::ObjectWrap<QVideoWidgetWrap> {
 private:
  QPointer<NVideoWidget> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QVideoWidgetWrap(const Napi::CallbackInfo& info);
  ~QVideoWidgetWrap();
  NVideoWidget* getInternalInstance();
  static Napi::FunctionReference constructor;
  // wrapped methods
  // Napi::Value showMessage(const Napi::CallbackInfo &info);
  Napi::Value setAspectRatioMode(const Napi::CallbackInfo& info);
  QWIDGET_WRAPPED_METHODS_DECLARATION
};