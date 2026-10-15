import addon from '../utils/addon';
import { NativeElement } from '../core/Component';
import { checkIfNativeElement } from '../utils/helpers';
import { QObject, QObjectSignals } from '../QtCore/QObject';
import { QUrl } from '../QtCore/QUrl';
import { wrapperCache } from '../core/WrapperCache';
import { QMediaContent } from './QMediaContent';

export class QMediaPlaylist extends QObject<QMediaPlaylist.QMediaPlaylistSignals> {
    constructor(arg?: QObject | NativeElement) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg != null) {
            const parent = arg as QObject;
            native = new addon.QMediaPlaylist(parent.native);
        } else {
            native = new addon.QMediaPlaylist();
        }
        super(native);
    }

    addMedia(content: QUrl | QMediaContent | string | NativeElement): boolean {
        console.log('addMedia', content);
        switch (true) {
            case checkIfNativeElement(content):
                break;

            case content instanceof QUrl:
                console.log('its QUrl');
                const test: QMediaContent = new addon.QMediaContent((content as QUrl).native, 1);
                const qurl: QUrl = test.canonicalUrl();
                console.log('asd', qurl.toString());
                const res: boolean = this.native.addMedia(test);
                console.log('res', res);
                break;

            case content instanceof QMediaContent:
                console.log('its QMediaContent');
                break;

            case typeof content === 'string':
                console.log('its string');
                const test2: QMediaContent = new addon.QMediaContent(new QUrl(content as string).native, 1);
                const qurl2: QUrl = test2.canonicalUrl();
                console.log('bsd', qurl2.toString());
                const res2: boolean = this.native.addMedia(test2);
                console.log('res2', res2);
                break;
        }
        return true;
    }

    clear(): boolean {
        return this.native.clear();
    }

    isEmpty(): boolean {
        return this.native.isEmpty();
    }

    playbackMode(): QMediaPlaylist.PlaybackMode {
        return this.native.playbackMode();
    }
    setPlaybackMode(mode: QMediaPlaylist.PlaybackMode | number): void {
        return this.native.setProperty('playbackMode', mode);
    }
}
wrapperCache.registerWrapper('QMediaPlaylistWrap', QMediaPlaylist);

// eslint-disable-next-line @typescript-eslint/no-namespace
export namespace QMediaPlaylist {
    export enum Error {
        NoError = 0,
        FormatError = 1,
        FormatNotSupportedError = 2,
        NetworkError = 3,
        AccessDeniedError = 4,
    }

    export enum PlaybackMode {
        CurrentItemOnce = 0,
        CurrentItemInLoop = 1,
        Sequential = 2,
        Loop = 3,
        Random = 4,
    }

    export interface QMediaPlaylistSignals extends QObjectSignals {
        //TODO: https://felgo.com/doc/qt5/qmediaplaylist/#signals
        currentIndexChanged: (position: number) => void;
        loadFailed: () => void;
        loaded: () => void;
        mediaChanged: (start: number, end: number) => void;
        mediaInserted: (start: number, end: number) => void;
        mediaRemoved: (start: number, end: number) => void;
    }
}
