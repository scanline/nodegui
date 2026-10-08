import addon from '../utils/addon';
import { NativeElement } from '../core/Component';
import { checkIfNativeElement } from '../utils/helpers';
import { QObject } from '../QtCore/QObject';
import { QColor } from '../QtGui/QColor';
import { QGraphicsEffect, QGraphicsEffectSignals } from './QGraphicsEffect';
import { wrapperCache } from '../core/WrapperCache';

export class QGraphicsColorizeEffect extends QGraphicsEffect<QGraphicsColorizeEffectSignals> {
    constructor(arg?: QObject | NativeElement) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg != null) {
            const parent = arg as QObject;
            native = new addon.QGraphicsColorizeEffect(parent.native);
        } else {
            native = new addon.QGraphicsColorizeEffect();
        }
        super(native);
    }
    color(): QColor {
        return new QColor(this.native.color());
    }
    setColor(color: QColor): void {
        this.native.setColor(color.native);
    }
    strength(): number {
        return this.property('strength').toDouble();
    }

    setStrength(strength: number): void {
        this.setProperty('strength', strength);
    }
}
wrapperCache.registerWrapper('QGraphicsColorizeEffectWrap', QGraphicsColorizeEffect);

export interface QGraphicsColorizeEffectSignals extends QGraphicsEffectSignals {
    colorChanged: (color: QColor) => void;
    strengthChanged: (strength: number) => void;
}
