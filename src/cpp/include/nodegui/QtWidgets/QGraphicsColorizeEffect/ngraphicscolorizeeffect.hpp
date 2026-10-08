#pragma once

#include <QGraphicsColorizeEffect>

#include "Extras/Export/export.h"
#include "QtGui/QColor/qcolor_wrap.h"
#include "QtWidgets/QGraphicsEffect/qgraphicseffect_macro.h"
#include "core/Events/eventwidget.h"
#include "core/Events/eventwidget_macro.h"

class DLL_EXPORT NGraphicsColorizeEffect : public QGraphicsColorizeEffect,
                                           public EventWidget {
  Q_OBJECT
  EVENTWIDGET_IMPLEMENTATIONS(QGraphicsColorizeEffect)

 public:
  using QGraphicsColorizeEffect::QGraphicsColorizeEffect;

  virtual void connectSignalsToEventEmitter() {
    QGRAPHICSEFFECT_SIGNALS
    // Qt Connects: Implement all signal connects here
    QObject::connect(
        this, &QGraphicsColorizeEffect::colorChanged, [=](const QColor& color) {
          Napi::Env env = this->emitOnNode.Env();
          Napi::HandleScope scope(env);
          auto instance = QColorWrap::constructor.New(
              {Napi::External<QColor>::New(env, new QColor(color))});
          this->emitOnNode.Call(
              {Napi::String::New(env, "colorChanged"), instance});
        });
    QObject::connect(
        this, &QGraphicsColorizeEffect::strengthChanged, [=](qreal strength) {
          Napi::Env env = this->emitOnNode.Env();
          Napi::HandleScope scope(env);
          this->emitOnNode.Call({Napi::String::New(env, "strengthChanged"),
                                 Napi::Number::New(env, strength)});
        });
  }
};