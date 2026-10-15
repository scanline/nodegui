import addon from '../utils/addon';
import { NativeElement } from '../core/Component';
import { checkIfNativeElement } from '../utils/helpers';
import { QObject } from '../QtCore/QObject';
import { QMediaObject, QMediaObjectSignals } from './QMediaObject';
import { QUrl } from '../QtCore/QUrl';
import { QVideoWidget } from './QVideoWidget';
import { QMediaPlaylist } from './QMediaPlaylist';
import { wrapperCache } from '../core/WrapperCache';

export class QMediaPlayer extends QMediaObject<QMediaPlayer.QMediaPlayerSignals> {
    constructor(arg?: QObject | NativeElement) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg != null) {
            const parent = arg as QObject;
            native = new addon.QMediaPlayer(parent.native);
        } else {
            native = new addon.QMediaPlayer();
        }
        super(native);
    }
    isAudioAvailable(): boolean {
        return this.property('audioAvailable').toBool();
    }
    isMuted(): boolean {
        return this.property('muted').toBool();
    }
    isSeekable(): boolean {
        return this.property('seekable').toBool();
    }
    isVideoAvailable(): boolean {
        return this.property('videoAvailable').toBool();
    }
    pause(): void {
        this.native.pause();
    }
    play(): void {
        this.native.play();
    }
    playbackRate(): number {
        return this.property('playbackRate').toDouble();
    }
    position(): number {
        return this.property('position').toInt();
    }
    setMedia(media: QUrl): void {
        this.native.setMedia(media.native);
    }
    setMuted(muted: boolean): void {
        this.setProperty('muted', muted);
    }
    setPlaylist(playlist: QMediaPlaylist): void {
        this.native.setPlaylist(playlist.native);
    }
    setPosition(position: number): void {
        this.setProperty('position', position);
    }
    setVideoOutput(output: QVideoWidget): void {
        this.native.setVideoOutput(output.native);
    }
    setVolume(volume: number): void {
        this.setProperty('volume', volume);
    }
    state(): QMediaPlayer.State {
        return this.native.state();
    }
    stop(): void {
        this.native.stop();
    }
    volume(): number {
        return this.property('volume').toInt();
    }
}
wrapperCache.registerWrapper('QMediaPlayerWrap', QMediaPlayer);

// eslint-disable-next-line @typescript-eslint/no-namespace
export namespace QMediaPlayer {
    export enum MediaStatus {
        UnknownMediaStatus = 0,
        NoMedia = 1,
        LoadingMedia = 2,
        LoadedMedia = 3,
        StalledMedia = 4,
        BufferingMedia = 5,
        BufferedMedia = 6,
        EndOfMedia = 7,
        InvalidMedia = 8,
    }

    export enum Error {
        NoError = 0,
        ResourceError = 1,
        FormatError = 2,
        NetworkError = 3,
        AccessDeniedError = 4,
        ServiceMissingError = 5,
    }

    export enum State {
        StoppedState = 0,
        PlayingState = 1,
        PausedState = 2,
    }

    export interface QMediaPlayerSignals extends QMediaObjectSignals {
        //TODO: https://felgo.com/doc/qt5/qmediaplayer/#signals
        audioAvailableChanged: (available: boolean) => void;
        bufferStatusChanged: (percentFilled: number) => void;
        error: (error: Error) => void;
        mediaStatusChanged: (status: MediaStatus) => void;
        mutedChanged: (muted: boolean) => void;
        playbackRateChanged: (rate: number) => void;
        positionChanged: (position: number) => void;
        seekableChanged: (seekable: boolean) => void;
        stateChanged: (state: State) => void;
        videoAvailableChanged: (available: boolean) => void;
        volumeChanged: (volume: number) => void;
    }
}
