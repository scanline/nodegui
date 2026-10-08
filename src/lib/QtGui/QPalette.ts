import { Component, NativeElement } from '../core/Component';
import addon from '../utils/addon';
import { checkIfNativeElement } from '../utils/helpers';
import { QColor } from './QColor';

export enum ColorGroup {
    Disabled = 1,
    Active = 0,
    Inactive = 2,
    Normal = 0,
}

export enum ColorRole {
    WindowText = 0,
    Button = 1,
    Light = 2,
    Midlight = 3,
    Dark = 4,
    Mid = 5,
    Text = 6,
    BrightText = 7,
    ButtonText = 8,
    Base = 9,
    Window = 10,
    Shadow = 11,
    Highlight = 12,
    HighlightedText = 13,
    Link = 14,
    LinkVisited = 15,
    AlternateBase = 16,
    NoRole = 17,
    ToolTipBase = 18,
    ToolTipText = 19,
    PlaceholderText = 20,
}

export class QPalette extends Component {
    constructor();
    constructor(nativeElement: NativeElement);
    constructor(arg?: NativeElement | number | string) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else {
            native = new addon.QPalette();
        }
        super(native);
    }
    color(group: ColorGroup, role: ColorRole): QColor {
        return new QColor(this.native.color(group, role));
    }
    setColor(group: ColorGroup, role: ColorRole, color: QColor): void;
    setColor(role: ColorRole, color: QColor): void;
    setColor(groupOrRole: ColorGroup | ColorRole, roleOrColor: ColorRole | QColor, color?: QColor): void {
        if (arguments.length === 2) {
            this.native.setColor(groupOrRole as ColorRole, (roleOrColor as QColor).native);
        } else if (arguments.length === 3) {
            this.native.setColor(groupOrRole as ColorGroup, roleOrColor as ColorRole, color.native);
        }
    }
}
