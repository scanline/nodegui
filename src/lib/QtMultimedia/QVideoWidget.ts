import addon from '../utils/addon';
import { NativeElement } from '../core/Component';
import { checkIfNativeElement } from '../utils/helpers';
import { QObject } from '../QtCore/QObject';
import { QWidget } from '../QtWidgets/QWidget';
import { wrapperCache } from '../core/WrapperCache';
import { AspectRatioMode } from '../QtEnums/AspectRatioMode';
export class QVideoWidget extends QWidget {
    constructor(arg?: QObject | NativeElement) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg != null) {
            const parent = arg as QObject;
            native = new addon.QVideoWidget(parent.native);
        } else {
            native = new addon.QVideoWidget();
        }
        super(native);
    }
    setAspectRatioMode(mode: AspectRatioMode): void {
        this.native.setAspectRatioMode(mode);
    }
    /*
		load(url) {
			this.setProperty("url", url);
		}
		url() {
			return QUrl.fromQVariant(this.property("url"));
		}
		settings() {
			return new QWebEngineSettings(this.native.settings());
		}

		page() {
			return new QWebEnginePage(this.native.page());
		}

		setZoomFactor(factor) {
			this.native.setZoomFactor(factor);
		}

		zoomFactor() {
			return this.native.zoomFactor();
		}*/
}
wrapperCache.registerWrapper('QVideoWidgetWrap', QVideoWidget);
