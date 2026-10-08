#pragma once

#include <napi.h>

#include <QPointer>

#include "Extras/Export/export.h"
#include "QtWidgets/QGraphicsEffect/qgraphicseffect_macro.h"
#include "ngraphicscolorizeeffect.hpp"

class QGraphicsColorizeEffectWrap
    : public Napi::ObjectWrap<QGraphicsColorizeEffectWrap> {
  QGRAPHICSEFFECT_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<NGraphicsColorizeEffect> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QGraphicsColorizeEffectWrap(const Napi::CallbackInfo& info);
  ~QGraphicsColorizeEffectWrap();
  NGraphicsColorizeEffect* getInternalInstance();
  static Napi::FunctionReference constructor;

  // Wrapped methods
  Napi::Value color(const Napi::CallbackInfo& info);
  Napi::Value setColor(const Napi::CallbackInfo& info);
};