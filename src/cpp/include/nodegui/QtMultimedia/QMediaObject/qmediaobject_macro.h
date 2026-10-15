#pragma once
#include <QDebug>
#include <QMultimedia>

#include "Extras/Utils/nutils.h"
#include "QtCore/QVariant/qvariant_wrap.h"
#include "core/Events/eventwidget_macro.h"

#ifndef QMEDIAOBJECT_WRAPPED_METHODS_DECLARATION
#define QMEDIAOBJECT_WRAPPED_METHODS_DECLARATION                           \
  Napi::Value isMetaDataAvailable(const Napi::CallbackInfo& info) {        \
    Napi::Env env = info.Env();                                            \
    this->instance->isMetaDataAvailable();                                 \
    return Napi::Boolean::New(env, this->instance->isMetaDataAvailable()); \
  }                                                                        \
  Napi::Value availableMetaData(const Napi::CallbackInfo& info) {          \
    Napi::Env env = info.Env();                                            \
    QStringList metadata = this->instance->availableMetaData();            \
    Napi::Array metadataNapi = Napi::Array::New(env, metadata.size());     \
    for (int i = 0; i < metadata.size(); i++) {                            \
      metadataNapi[i] = Napi::String::New(env, metadata[i].toStdString()); \
    }                                                                      \
    return metadataNapi;                                                   \
  }                                                                        \
  Napi::Value metaData(const Napi::CallbackInfo& info) {                   \
    Napi::Env env = info.Env();                                            \
    QVariant data = this->instance->metaData(                              \
        info[0].As<Napi::String>().Utf8Value().c_str());                   \
    auto instance = QVariantWrap::constructor.New(                         \
        {Napi::External<QVariant>::New(env, new QVariant(data))});         \
    return instance;                                                       \
  }
#endif  // QMEDIAOBJECT_WRAPPED_METHODS_DECLARATION

#ifndef QMEDIAOBJECT_WRAPPED_METHODS_EXPORT_DEFINE
#define QMEDIAOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(ComponentWrapName) \
  InstanceMethod("isMetaDataAvailable",                               \
                 &ComponentWrapName::isMetaDataAvailable),            \
      InstanceMethod("availableMetaData",                             \
                     &ComponentWrapName::availableMetaData),          \
      InstanceMethod("metaData", &ComponentWrapName::metaData),
#endif  // QMEDIAOBJECT_WRAPPED_METHODS_EXPORT_DEFINE

#ifndef QMEDIAOBJECT_SIGNALS_ON_TARGET
#define QMEDIAOBJECT_SIGNALS_ON_TARGET(target)                                \
  QObject::connect(                                                           \
      target, qOverload<bool>(&QMediaObject::availabilityChanged),            \
      [=](bool available) {                                                   \
        Napi::Env env = this->emitOnNode.Env();                               \
        Napi::HandleScope scope(env);                                         \
        this->emitOnNode.Call({Napi::String::New(env, "availabilityChanged"), \
                               Napi::Boolean::New(env, available)});          \
      });                                                                     \
  QObject::connect(target, &QMediaObject::metaDataAvailableChanged,           \
                   [=](bool available) {                                      \
                     Napi::Env env = this->emitOnNode.Env();                  \
                     Napi::HandleScope scope(env);                            \
                     this->emitOnNode.Call(                                   \
                         {Napi::String::New(env, "metaDataAvailableChanged"), \
                          Napi::Boolean::New(env, available)});               \
                   });                                                        \
  QObject::connect(                                                           \
      target, qOverload<>(&QMediaObject::metaDataChanged), [=]() {            \
        Napi::Env env = this->emitOnNode.Env();                               \
        Napi::HandleScope scope(env);                                         \
        this->emitOnNode.Call({Napi::String::New(env, "metaDataChanged")});   \
      });
#endif  // QMEDIAOBJECT_SIGNALS_ON_TARGET