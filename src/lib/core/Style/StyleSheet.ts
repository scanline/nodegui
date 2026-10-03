import postcss from 'postcss';
import crypto from "node:crypto";
import nodeguiAutoPrefixer from 'postcss-nodegui-autoprefixer';
import { QWidget, QWidgetSignals } from '../../QtWidgets/QWidget';

let counter = 0;

function randomBase36(length: number): string {
  let result = "";

  while (result.length < length) {
    const bytes = crypto.randomBytes(length);
    for (const byte of bytes) {
      result += (byte % 36).toString(36);
      if (result.length === length) break;
    }
  }

  return result;
}

function cuid(): string {
  const timestamp = Date.now().toString(36);
  const count = (counter++ % 36 ** 4).toString(36).padStart(4, "0");
  const random = randomBase36(10);

  return `c${timestamp}${count}${random}`;
}

export class StyleSheet {
    static create(cssString: string): string {
        try {
            return postcss([nodeguiAutoPrefixer()]).process(cssString).css;
        } catch (err) {
            console.error(err);
            return '';
        }
    }
}

export function prepareInlineStyleSheet<Signals extends QWidgetSignals>(
    widget: QWidget<Signals>,
    rawStyle: string,
): string {
    const inlineStyle = StyleSheet.create(rawStyle);
    // Make sure to not calculate ObjectName in the same pass of event loop as other props (incase of react) since the order will matter in that case
    // So doing it in multiple passes of event loop allows objectName to be set before using it. The above await solves it.
    let cssId = widget.objectName();
    if (!cssId) {
        cssId = cuid();
        widget.setObjectName(cssId);
    }
    return `
      #${cssId} {
        ${inlineStyle}
      }
  `;
}
