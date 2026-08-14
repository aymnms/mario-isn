## [1.2.1](https://github.com/aymnms/mario-isn/compare/v1.2.0...v1.2.1) (2026-08-14)


### Bug Fixes

* suppress the Windows console window ([57a2d27](https://github.com/aymnms/mario-isn/commit/57a2d2772bf080a51be71f04f884776a893b81a2))

# [1.2.0](https://github.com/aymnms/mario-isn/compare/v1.1.0...v1.2.0) (2026-08-14)


### Bug Fixes

* **build:** link SDL2main so the Windows executable resolves main() ([c52a7b3](https://github.com/aymnms/mario-isn/commit/c52a7b37a8f207d0d2f01c457c9e4fa9982dc1d5))
* **ci:** authenticate and flatten cross-run artifact download in release workflow ([522977d](https://github.com/aymnms/mario-isn/commit/522977d0e128b0709e3078ddf32c8c9e99b99fc9)), closes [#16](https://github.com/aymnms/mario-isn/issues/16) [#16](https://github.com/aymnms/mario-isn/issues/16) [#15](https://github.com/aymnms/mario-isn/issues/15) [#8](https://github.com/aymnms/mario-isn/issues/8) [#9](https://github.com/aymnms/mario-isn/issues/9)
* **ci:** bump release workflow to Node 22 ([f127cad](https://github.com/aymnms/mario-isn/commit/f127cad7233d022281c726c04e7d8605e79df448))
* **ci:** fix Windows generator detection and Linux bundling pipefail bug ([d50b152](https://github.com/aymnms/mario-isn/commit/d50b15248436ed70cc6917b4269abcaa5132ae7e))


### Features

* **build:** add macOS Intel build via Rosetta cross-compile ([fa751cc](https://github.com/aymnms/mario-isn/commit/fa751cc54c79b47df1aa53668b5edffea5967033)), closes [#15](https://github.com/aymnms/mario-isn/issues/15)
* **build:** bundle SDL2 libs into release artifacts (macOS + Linux) ([9200837](https://github.com/aymnms/mario-isn/commit/9200837a6dee87cd081870d10df7ac31a45b9884)), closes [#15](https://github.com/aymnms/mario-isn/issues/15)
* **ci:** add Windows build to the CI matrix ([#8](https://github.com/aymnms/mario-isn/issues/8), [#9](https://github.com/aymnms/mario-isn/issues/9)) ([ee28795](https://github.com/aymnms/mario-isn/commit/ee287955be328c484ab1bb1c240f1962c1235800))

# [1.1.0](https://github.com/aymnms/mario-isn/compare/v1.0.0...v1.1.0) (2025-08-17)


### Features

* centralize global variables ([4f3a3aa](https://github.com/aymnms/mario-isn/commit/4f3a3aac698f7c819233a7cf80d31f4ed5dde0e3))
* compile on linux ([7716ca0](https://github.com/aymnms/mario-isn/commit/7716ca066df393b287de81ea745fecf6aa4cd939))
* Modify the existing sementic release pipeline to add builds for the multi-OS pipline. ([8bb896d](https://github.com/aymnms/mario-isn/commit/8bb896d792d1a19ce2a057ebd16831ae3c40ac0e))
* Modify the macos pipeline into a multi-OS pipeline to build on github actions ([79d72bb](https://github.com/aymnms/mario-isn/commit/79d72bb00d9319b1e3e0178b343c9ce9541a65ed))

# 1.0.0 (2025-08-14)


### Bug Fixes

* add void image to remove the image of the villain at the start of the level ([d533fef](https://github.com/aymnms/mario-isn/commit/d533fef641f527b84662829802f042e7660268ce))
* coin display info ([e22a4ad](https://github.com/aymnms/mario-isn/commit/e22a4adf609b467258399af53a649ce07f0a18cc))
* modify chronometer display ([10c56b0](https://github.com/aymnms/mario-isn/commit/10c56b092ecbc0848c897ff13ce229ef5c4d1b25))
* remove carre texture ([5d980e1](https://github.com/aymnms/mario-isn/commit/5d980e1ab07479d75ce3390b685655baf48894ad))


### Features

* add license ([105ad7e](https://github.com/aymnms/mario-isn/commit/105ad7e29d30a3e7c0506d4c75aac1333373fffc))
* add Makefile ([5590f1d](https://github.com/aymnms/mario-isn/commit/5590f1dde95188a3b70c63edeb10b8ecf44cffe6))
* add script.sh ([6edbf29](https://github.com/aymnms/mario-isn/commit/6edbf2984678aabd21aea942556ab9700c43036b))
* add SDL2 lib & start to implement main.c ([85426f9](https://github.com/aymnms/mario-isn/commit/85426f924be2de76526f16378b585c1b812bbfa2))
* add workflow to build app on macos intel & arm ([c295c84](https://github.com/aymnms/mario-isn/commit/c295c846792db22682eb90a725e2f286a8994163))
* build .app ([8643d66](https://github.com/aymnms/mario-isn/commit/8643d66c443fa8477f7660ac7752224304900e5e))
* game included with display ([2cc110f](https://github.com/aymnms/mario-isn/commit/2cc110f88b7b2959d30b46aa3d59a67ba75db9f8))
* game included without display ([eff7c15](https://github.com/aymnms/mario-isn/commit/eff7c15c194d964afd75392e8bb8d0d45116ef71))
* hello world ([bb415a0](https://github.com/aymnms/mario-isn/commit/bb415a06096b3e41f593164122ff5bdf46306a1e))
* implement semantic release [#7](https://github.com/aymnms/mario-isn/issues/7) ([2cf4465](https://github.com/aymnms/mario-isn/commit/2cf4465a510781983657dd4e2f4d15a329184a78))
* init_game included ([787e210](https://github.com/aymnms/mario-isn/commit/787e21062e70b7c4ea6844f91acef3e3fa679d7c))
* init_menu.c & music.c implemented ([eac3cfc](https://github.com/aymnms/mario-isn/commit/eac3cfcf3549efdd5ebb0995a0c511859795c147))
* menu implemented ([ad45ce8](https://github.com/aymnms/mario-isn/commit/ad45ce8610b2994984734ae94a9aba0916c13a02))
* modify build-macos.yml ([cdf80dd](https://github.com/aymnms/mario-isn/commit/cdf80ddadb7ed6a88b0e1edc7f214a88facdb109))
* modify cicd macos-arm ([39fe6e1](https://github.com/aymnms/mario-isn/commit/39fe6e1b8697133c6299d945938edbbb8671e586))
* modify readme ([dd5637b](https://github.com/aymnms/mario-isn/commit/dd5637bb25fcc13e6d2fde62e80699b0d41acf2e))
* modify readme ([77073cd](https://github.com/aymnms/mario-isn/commit/77073cd7097f78102e815273d36b693dc55d595f))
* modify readme ([49fb7da](https://github.com/aymnms/mario-isn/commit/49fb7da2e313962b3493afad3110c9767156cb3b))
* modify Readme ([6f119e1](https://github.com/aymnms/mario-isn/commit/6f119e16b9754d061f496a8327c92110e4978478))
* remove build cicd on pull_request ([c9dc932](https://github.com/aymnms/mario-isn/commit/c9dc932768fcb7518d505f0849e1a6736dc6ba64))
* remove macos intelworkflow ([492731b](https://github.com/aymnms/mario-isn/commit/492731b253a286b4c30443ccad5871bf6b8f88d0))
* Remove quarantine attribute and Sign app into workflow ([9ae652a](https://github.com/aymnms/mario-isn/commit/9ae652aa80124608b7941615a770950e7fab125b))
* remove SDL icon ([c06ebe3](https://github.com/aymnms/mario-isn/commit/c06ebe37f5994b2741bc3c093d2b968a48429256))
* update Readme ([f9e7d14](https://github.com/aymnms/mario-isn/commit/f9e7d145ce7e3e8d3156c7449b83f7aaac378cde))
* update README ([c31dc5c](https://github.com/aymnms/mario-isn/commit/c31dc5cffdb44d4306516540e2335d2131c24f21))
