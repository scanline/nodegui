import addon from '../utils/addon';
import { NativeElement } from '../core/Component';
import { checkIfNativeElement } from '../utils/helpers';
import { QObject } from '../QtCore/QObject';
import { QBrush } from '../QtGui/QBrush';
import { QGraphicsEffect, QGraphicsEffectSignals } from './QGraphicsEffect';
import { wrapperCache } from '../core/WrapperCache';

export class QGraphicsOpacityEffect extends QGraphicsEffect<QGraphicsOpacityEffectSignals> {
    constructor(arg?: QObject | NativeElement) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg != null) {
            const parent = arg as QObject;
            native = new addon.QGraphicsOpacityEffect(parent.native);
        } else {
            native = new addon.QGraphicsOpacityEffect();
        }
        super(native);
    }
    opacity(): number {
        return this.property('opacity').toDouble();
    }
    opacityMask(): QBrush {
        return QBrush.fromQVariant(this.property('opacityMask'));
    }
    setOpacity(opacity: number): void {
        this.setProperty('opacity', opacity);
    }
    setOpacityMask(brush: QBrush): void {
        this.setProperty('opacityMask', brush.native);
    }
}
wrapperCache.registerWrapper('QGraphicsOpacityEffectWrap', QGraphicsOpacityEffect);

export interface QGraphicsOpacityEffectSignals extends QGraphicsEffectSignals {
    opacityChanged: (opacity: number) => void;
    opacityMaskChanged: (mask: QBrush) => void;
}
