#pragma once

#include <QGraphicsOpacityEffect>

#include "Extras/Export/export.h"
#include "QtGui/QBrush/qbrush_wrap.h"
#include "QtWidgets/QGraphicsEffect/qgraphicseffect_macro.h"
#include "core/Events/eventwidget.h"
#include "core/Events/eventwidget_macro.h"

class DLL_EXPORT NGraphicsOpacityEffect : public QGraphicsOpacityEffect,
                                          public EventWidget {
  Q_OBJECT
  EVENTWIDGET_IMPLEMENTATIONS(QGraphicsOpacityEffect)

 public:
  using QGraphicsOpacityEffect::QGraphicsOpacityEffect;

  virtual void connectSignalsToEventEmitter() {
    QGRAPHICSEFFECT_SIGNALS
    // Qt Connects: Implement all signal connects here
    QObject::connect(
        this, &QGraphicsOpacityEffect::opacityMaskChanged,
        [=](const QBrush& mask) {
          Napi::Env env = this->emitOnNode.Env();
          Napi::HandleScope scope(env);
          auto instance = QBrushWrap::constructor.New(
              {Napi::External<QBrush>::New(env, new QBrush(mask))});
          this->emitOnNode.Call(
              {Napi::String::New(env, "opacityMaskChanged"), instance});
        });
    QObject::connect(
        this, &QGraphicsOpacityEffect::opacityChanged, [=](qreal opacity) {
          Napi::Env env = this->emitOnNode.Env();
          Napi::HandleScope scope(env);
          this->emitOnNode.Call({Napi::String::New(env, "opacityChanged"),
                                 Napi::Number::New(env, opacity)});
        });
  }
};