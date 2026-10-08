# NodeGui

This is a modified version of [NodeGui](https://github.com/nodegui/nodegui) v0.57.3 - which is the last version using QT5. Unfortunately it ain't being actively enhanced anymore, so this repo adds some missing functionality.



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
| `void` | `setPalette(palette: QPalette)` |

### QComboBox Class

#### Public Functions

| Return type | Function |
| --- | --- |
| void | setItemData(index: number, variant: QVariantType, role: [ItemDataRole](https://docs.nodegui.org/docs/api/generated/enums/itemdatarole/)) |

### QGraphicsColorizeEffect Class

#### Constructors

| Return type | Constructor |
| --- | --- |
| QGraphicsColorizeEffect | QGraphicsColorizeEffect() |
| QGraphicsColorizeEffect | QGraphicsColorizeEffect(native: NativeElement) |
| QGraphicsColorizeEffect | QGraphicsColorizeEffect(parent: QWidget) |

#### Public Functions

| Return type | Function |
| --- | --- |
| `QColor` | `color()` |
| `number` | `strength()` |
| `void` | `setColor(color: QColor)` |
| `void` | `setStrength(strength: number)` |

#### Signals

| Return type | Function |
| --- | --- |
| `void` | `colorChanged(color: QColor)` |
| `void` | `strengthChanged(strength: number)` |

### QGraphicsOpacityEffect Class

#### Constructors

| Return type | Constructor |
| --- | --- |
| QGraphicsOpacityEffect | QGraphicsOpacityEffect() |
| QGraphicsOpacityEffect | QGraphicsOpacityEffect(native: NativeElement) |
| QGraphicsOpacityEffect | QGraphicsOpacityEffect(parent: QWidget) |

#### Public Functions

| Return type | Function |
| --- | --- |
| `number` | `opacity()` |
| `QBrush` | `opacityMask()` |
| `void` | `setOpacity(opacity: number)` |
| `void` | `setOpacityMask(mask: QBrush)` |

#### Signals

| Return type | Function |
| --- | --- |
| `void` | `opacityChanged(opacity: number)` |
| `void` | `opacityMaskChanged(mask: QBrush)` |

### QHBoxLayout Class

#### Constructors

| Return type | Constructor |
| --- | --- |
| QHBoxLayout | QHBoxLayout() |
| QHBoxLayout | QHBoxLayout(native: NativeElement) |
| QHBoxLayout | QHBoxLayout(parent: QWidget) |

### QPalette Class

#### Public Functions

| Return type | Function |
| --- | --- |
| `void` | `setColor(role: ColorRole, color: QColor)` |
| `void` | `setColor(group: ColorGroup, role: ColorRole, color: QColor)` |

### QVBoxLayout Class

#### Constructors

| Return type | Constructor |
| --- | --- |
| QVBoxLayout | QVBoxLayout() |
| QVBoxLayout | QVBoxLayout(native: NativeElement) |
| QVBoxLayout | QVBoxLayout(parent: QWidget) |

### QWidget Class

#### Public Functions

| Return type | Function |
| --- | --- |
| `QLayout` | `layout()` |
