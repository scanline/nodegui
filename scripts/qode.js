#!/usr/bin/env node

var path = require('path');
var qodeConfig = require('@nodegui/qode');
var qtConfig = require('../config/qtConfig');

var proc = require('child_process');

// Add Qt's bin to the ENVIRONMENT path of Qode so that it can find the dynamic libraries (.so, .dll, .dylib)
const envPATH = process.platform === 'win32' ? Object.keys(process.env).find(envPATH => /^path$/i.test(envPATH)) || 'Path' : 'PATH';
process.env[envPATH] = path.join(qtConfig.qtHome, 'bin') + path.delimiter + process.env[envPATH];

// Add Qt's lib to LD_LIBRARY_PATH so linux can find the libs when bundled with webpack
if(process.platform === 'linux') {
    var oldLD_PATH = process.env.LD_LIBRARY_PATH ?? "";
    process.env.LD_LIBRARY_PATH = oldLD_PATH + ":" + path.join(qtConfig.qtHome, 'lib');
}

var child = proc.spawn(qodeConfig.qodePath, process.argv.slice(2), {
    stdio: 'inherit',
    windowsHide: false,
    env: process.env,
});

child.on('close', function(code) {
    process.exit(code);
});

const handleTerminationSignal = function(signal) {
    process.on(signal, function signalHandler() {
        if (!child.killed) {
            child.kill(signal);
        }
    });
};

handleTerminationSignal('SIGINT');
handleTerminationSignal('SIGTERM');