import addon from '../utils/addon';
import { NativeElement, Component } from '../core/Component';
import { checkIfNativeElement } from '../utils/helpers';
import { QObject } from '../QtCore/QObject';
import { QUrl } from '../QtCore/QUrl';

export class QMediaContent extends Component {
    constructor(arg?: NativeElement | QObject) {
        let native: NativeElement;
        if (!arg) {
            native = new addon.QMediaContent();
        } else if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg.native) {
            native = new addon.QMediaContent(arg.native);
        } else {
            native = new addon.QMediaContent();
        }
        super(native);
    }

    canonicalUrl(): QUrl {
        const test: QUrl = this.native.canonicalUrl();
        console.log(test);
        return test;
    }
}
