#pragma once

#include <napi.h>

#include <QPointer>

#include "Extras/Export/export.h"
#include "QtWidgets/QGraphicsEffect/qgraphicseffect_macro.h"
#include "ngraphicsopacityeffect.hpp"

class QGraphicsOpacityEffectWrap
    : public Napi::ObjectWrap<QGraphicsOpacityEffectWrap> {
  QGRAPHICSEFFECT_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<NGraphicsOpacityEffect> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QGraphicsOpacityEffectWrap(const Napi::CallbackInfo& info);
  ~QGraphicsOpacityEffectWrap();
  NGraphicsOpacityEffect* getInternalInstance();
  static Napi::FunctionReference constructor;
};