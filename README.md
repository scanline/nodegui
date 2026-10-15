# NodeGui

This is a modified version of [NodeGui](https://github.com/nodegui/nodegui) v0.57.3 - which is the last version using QT5. Unfortunately it ain't being actively enhanced anymore, so this repo adds some missing functionality.
The package's version number will stay hardcoded at 0.57.3 as it otherwise might interfere with NodeGui's internal tooling. Instead there's an internal version number starting at 1.0.0, which is also reflected in the releases.



## Installation

Instead of using

```
npm install @nodegui/nodegui@0.57.3
```

to install the original version, use
```
npm install github:scanline/nodegui
```

to install it from this repo.
Please note though that pre-built binaries are only available for Windows.


## Enhancements

### QApplication Class

#### Public Functions

| Return type | Function |
| --- | --- |
| void | setPalette(palette: QPalette) |

### QComboBox Class

#### Public Functions

| Return type | Function |
| --- | --- |
| void | setItemData(index: number, value: QVariantType, role?: [ItemDataRole](https://docs.nodegui.org/docs/api/generated/enums/itemdatarole/)) |

### QGraphicsColorizeEffect Class

#### Constructors

| Return type | Constructor |
| --- | --- |
| QGraphicsColorizeEffect | QGraphicsColorizeEffect() |
| QGraphicsColorizeEffect | QGraphicsColorizeEffect(object: QObject) |
| QGraphicsColorizeEffect | QGraphicsColorizeEffect(element: NativeElement) |

#### Public Functions

| Return type | Function |
| --- | --- |
| QColor | color() |
| void | setColor(color: QColor) |
| void | setStrength(strength: number) |
| number | strength() |

#### Signals

| Return type | Function |
| --- | --- |
| void | colorChanged(color: QColor) |
| void | strengthChanged(strength: number) |

### QGraphicsOpacityEffect Class

#### Constructors

| Return type | Constructor |
| --- | --- |
| QGraphicsOpacityEffect | QGraphicsOpacityEffect() |
| QGraphicsOpacityEffect | QGraphicsOpacityEffect(object: QObject) |
| QGraphicsOpacityEffect | QGraphicsOpacityEffect(element: NativeElement) |

#### Public Functions

| Return type | Function |
| --- | --- |
| number | opacity() |
| QBrush | opacityMask() |
| void | setOpacity(opacity: number) |
| void | setOpacityMask(brush: QBrush) |

#### Signals

| Return type | Function |
| --- | --- |
| void | opacityChanged(opacity: number) |
| void | opacityMaskChanged(mask: QBrush) |

### QHBoxLayout Class

#### Constructors

| Return type | Constructor |
| --- | --- |
| QHBoxLayout | QHBoxLayout() |
| QHBoxLayout | QHBoxLayout(element: NativeElement) |
| QHBoxLayout | QHBoxLayout(widget: QWidget) |

### QMediaContent Class

#### Constructors

| Return type | Constructor |
| --- | --- |
| QMediaContent | QMediaContent() |
| QMediaContent | QMediaContent(element: NativeElement) |
| QMediaContent | QMediaContent(object: QObject) |

#### Public Functions

| Return type | Function |
| --- | --- |
| QUrl | canonicalUrl() |

### QMediaObject Class (abstract)

#### Public Functions

| Return type | Function |
| --- | --- |
| string[] | availableMetaData() |
| boolean | isMetaDataAvailable() |
| QVariant | metaData(key: string) |
| number | notifyInterval() |
| void | setNotifyInterval(milliSeconds: number) |

#### Signals

| Return type | Function |
| --- | --- |
| void | availabilityChanged(available: boolean) |
| void | metaDataAvailableChanged(available: boolean) |
| void | metaDataChanged() |

### QMediaPlayer Class (extends QMediaObject)

#### Constructors

| Return type | Constructor |
| --- | --- |
| QMediaPlayer | QMediaPlayer() |
| QMediaPlayer | QMediaPlayer(object: QObject) |
| QMediaPlayer | QMediaPlayer(element: NativeElement) |

#### Public Functions

| Return type | Function |
| --- | --- |
| boolean | isAudioAvailable() |
| boolean | isMuted() |
| boolean | isSeekable() |
| boolean | isVideoAvailable() |
| void | pause() |
| void | play() |
| number | playbackRate() |
| number | position() |
| void | setMedia(media: QUrl) |
| void | setMuted(muted: boolean) |
| void | setPlaylist(playlist: QMediaPlaylist) |
| void | setPosition(position: number) |
| void | setVideoOutput(output: QVideoWidget) |
| void | setVolume(volume: number) |
| QMediaPlayer.State | state() |
| void | stop() |
| number | volume() |

#### Signals

| Return type | Function |
| --- | --- |
| void | audioAvailableChanged(available: boolean) |
| void | bufferStatusChanged(percentFilled: number) |
| void | error(error: Error) |
| void | mediaStatusChanged(status: MediaStatus) |
| void | mutedChanged(muted: boolean) |
| void | playbackRateChanged(rate: number) |
| void | positionChanged(position: number) |
| void | seekableChanged(seekable: boolean) |
| void | stateChanged(state: State) |
| void | videoAvailableChanged(available: boolean) |
| void | volumeChanged(volume: number) |

### QMediaPlaylist Class

#### Constructors

| Return type | Constructor |
| --- | --- |
| QMediaPlaylist | QMediaPlaylist() |
| QMediaPlaylist | QMediaPlaylist(object: QObject) |
| QMediaPlaylist | QMediaPlaylist(element: NativeElement) |

#### Public Functions

| Return type | Function |
| --- | --- |
| boolean | addMedia(content: QUrl \| QMediaContent \| string \| NativeElement) |
| boolean | clear() |
| boolean | isEmpty() |
| QMediaPlaylist.PlaybackMode | playbackMode() |
| void | setPlaybackMode(mode: QMediaPlaylist.PlaybackMode \| number) |

#### Signals

| Return type | Function |
| --- | --- |
| void | currentIndexChanged(position: number) |
| void | loaded() |
| void | loadFailed() |
| void | mediaChanged(start: number,  end: number) |
| void | mediaInserted(start: number,  end: number) |
| void | mediaRemoved(start: number,  end: number) |

### QPalette Class

#### Public Functions

| Return type | Function |
| --- | --- |
| void | setColor(group: ColorGroup, role: ColorRole, color: QColor) |
| void | setColor(role: ColorRole, color: QColor) |

### QVBoxLayout Class

#### Constructors

| Return type | Constructor |
| --- | --- |
| QVBoxLayout | QVBoxLayout() |
| QVBoxLayout | QVBoxLayout(element: NativeElement) |
| QVBoxLayout | QVBoxLayout(widget: QWidget) |

### QWidget Class

#### Public Functions

| Return type | Function |
| --- | --- |
| QLayout \| null | layout() |