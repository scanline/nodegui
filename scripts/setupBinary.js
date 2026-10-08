#!/usr/bin/env node

const os = require('os');
const fs = require('fs');
const path = require('path');
const {
	setupArtifact
} = require('@nodegui/artifact-installer');
const tar = require('tar');
const SETUP_DIR = path.resolve(__dirname, '..', 'build', 'Release');
const packageJson = require('../package');

async function setupBinary() {
	const internalVersion = packageJson.internalVersion;
	const tarballName = `nodegui-binary-v${internalVersion}-${os.platform()}-${os.arch()}.tar.gz`;
	const url = `https://github.com/scanline/nodegui/releases/download/v${internalVersion}/${tarballName}`;

	await setupArtifact({
		outDir: SETUP_DIR,
		id: 'nodegui-core',
		displayName: `Precompiled NodeGui binary`,
		downloadLink: url,
		skipSetup: () => false,
	});
	const tarPath = path.join(SETUP_DIR, tarballName.slice(0, -3));
	tar.extract({
		cwd: SETUP_DIR,
		file: tarPath,
		sync: true,
	});
	fs.unlinkSync(tarPath);
}

setupBinary()
	.catch((err) => {
		console.error(err);
		process.exit(1);
	})
	.then(() => {
		process.exit(0);
	});