import { QObject, QObjectSignals } from '../QtCore/QObject';
import { QVariant } from '../QtCore/QVariant';

export abstract class QMediaObject<Signals extends QMediaObjectSignals> extends QObject<Signals> {
    isMetaDataAvailable(): boolean {
        return this.native.isMetaDataAvailable();
    }
    availableMetaData(): string[] {
        return this.native.availableMetaData();
    }
    metaData(key: string): QVariant {
        return new QVariant(this.native.metaData(key));
    }
    notifyInterval(): number {
        return this.property('notifyInterval').toInt();
    }
    setNotifyInterval(milliSeconds: number): void {
        this.setProperty('notifyInterval', milliSeconds);
    }
}

export interface QMediaObjectSignals extends QObjectSignals {
    availabilityChanged: (available: boolean) => void;
    metaDataAvailableChanged: (available: boolean) => void;
    metaDataChanged: () => void;
}
