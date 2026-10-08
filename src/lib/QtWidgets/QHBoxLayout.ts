import addon from '../utils/addon';
import { QWidget } from './QWidget';
import { QBoxLayout } from './QBoxLayout';
import { NativeElement } from '../core/Component';
import { Direction } from '../QtEnums';
import { checkIfNativeElement } from '../utils/helpers';
//import { wrapperCache } from '../core/WrapperCache';

export class QHBoxLayout extends QBoxLayout {
    constructor(arg?: NativeElement | QWidget) {
        let native: NativeElement;

        if (checkIfNativeElement(arg)) {
            native = arg;
        } else if (arg instanceof QWidget) {
            native = new addon.QBoxLayout(Direction.LeftToRight, arg.native);
        } else {
            native = new addon.QBoxLayout(Direction.LeftToRight);
        }

        super(native);
    }
}
//wrapperCache.registerWrapper('QBoxLayoutWrap', QBoxLayout);
