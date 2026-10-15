#pragma once

#include <QtWidgets/QFrame/qframe_macro.h>
#include <QtWidgets/QWidget/qwidget_macro.h>
#include <core/NodeWidget/nodewidget.h>

#include <QVideoWidget>

class DLL_EXPORT NVideoWidget : public QVideoWidget, public NodeWidget {
 public:
  Q_OBJECT
  NODEWIDGET_IMPLEMENTATIONS(QVideoWidget)
 public:
  using QVideoWidget::QVideoWidget;  // inherit all constructors of QVideoWidget

  void connectSignalsToEventEmitter() {
    QWIDGET_SIGNALS
    QOBJECT_SIGNALS
    QObject::connect(
        this, &QVideoWidget::brightnessChanged, [=](int brightness) {
          Napi::Env env = this->emitOnNode.Env();
          Napi::HandleScope scope(env);
          this->emitOnNode.Call({Napi::String::New(env, "brightnessChanged"),
                                 Napi::Number::New(env, brightness)});
        });

    QObject::connect(this, &QVideoWidget::contrastChanged, [=](int contrast) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "contrastChanged"),
                             Napi::Number::New(env, contrast)});
    });

    QObject::connect(
        this, &QVideoWidget::fullScreenChanged, [=](bool fullScreen) {
          Napi::Env env = this->emitOnNode.Env();
          Napi::HandleScope scope(env);
          this->emitOnNode.Call({Napi::String::New(env, "fullScreenChanged"),
                                 Napi::Boolean::New(env, fullScreen)});
        });

    QObject::connect(this, &QVideoWidget::hueChanged, [=](int hue) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call(
          {Napi::String::New(env, "hueChanged"), Napi::Number::New(env, hue)});
    });

    QObject::connect(
        this, &QVideoWidget::saturationChanged, [=](int saturation) {
          Napi::Env env = this->emitOnNode.Env();
          Napi::HandleScope scope(env);
          this->emitOnNode.Call({Napi::String::New(env, "saturationChanged"),
                                 Napi::Number::New(env, saturation)});
        });
  }
};