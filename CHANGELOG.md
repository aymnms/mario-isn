## [1.3.5](https://github.com/aymnms/mario-isn/compare/v1.3.4...v1.3.5) (2026-08-15)


### Bug Fixes

* **globals:** resolve global symbol inconsistencies found in J5-3 audit ([5ce7bc8](https://github.com/aymnms/mario-isn/commit/5ce7bc870acf09cc1f3d52aabd0d1c9cb8f605a3))
* **logic:** use logical || instead of bitwise | in boolean conditions ([b2a17dc](https://github.com/aymnms/mario-isn/commit/b2a17dc70f6b9b8399616739142b7d88948babf1))
* **logic:** zero-initialize locals GCC proves may be uninitialized at -O3 ([77cef68](https://github.com/aymnms/mario-isn/commit/77cef681bd61fea36ed1bba369acf7bb867d48df))

## [1.3.4](https://github.com/aymnms/mario-isn/compare/v1.3.3...v1.3.4) (2026-08-15)


### Bug Fixes

* **mechant:** initialize test4 in goB() before it's read ([6716ad2](https://github.com/aymnms/mario-isn/commit/6716ad269ff561fac6d3914f1b0fdd286e0e5fe2))

## [1.3.3](https://github.com/aymnms/mario-isn/compare/v1.3.2...v1.3.3) (2026-08-15)


### Bug Fixes

* **ci:** target the real mario_isn process, not the AppImage supervisor ([00ab401](https://github.com/aymnms/mario-isn/commit/00ab4015d50daca4d983c1ed29d7687a12821fe8))

## [1.3.2](https://github.com/aymnms/mario-isn/compare/v1.3.1...v1.3.2) (2026-08-15)


### Bug Fixes

* **rendering:** cache textures instead of recreating them every frame ([b8a8474](https://github.com/aymnms/mario-isn/commit/b8a8474c6bd613a7458fe9a69c551bb2d42910a3))

## [1.3.1](https://github.com/aymnms/mario-isn/compare/v1.3.0...v1.3.1) (2026-08-15)


### Bug Fixes

* **windows:** resolve NSIS OutFile to an absolute path so the installer is actually produced ([285a297](https://github.com/aymnms/mario-isn/commit/285a2972ef34f5728553bd23b360b98b03a48543))

# [1.3.0](https://github.com/aymnms/mario-isn/compare/v1.2.6...v1.3.0) (2026-08-15)


### Bug Fixes

* exclude makensis args from Git Bash's MSYS path conversion ([bfed518](https://github.com/aymnms/mario-isn/commit/bfed5180f5a15ec17babb8b0b449564d2744b0d6))
* install NSIS explicitly on the Windows runner ([fe41d60](https://github.com/aymnms/mario-isn/commit/fe41d60af7e30db736575755712ac4ea98b10598))
* pass an absolute icon path to the NSIS installer script ([1561bc8](https://github.com/aymnms/mario-isn/commit/1561bc823b393e9704abdecf36286e216368b0be))


### Features

* single-file distribution for Windows and Linux ([a140142](https://github.com/aymnms/mario-isn/commit/a1401420c678b72d0e0a212783ef2e05c3e57c60))

## [1.2.6](https://github.com/aymnms/mario-isn/compare/v1.2.5...v1.2.6) (2026-08-15)


### Bug Fixes

* bundle the MSVC runtime on Windows, target older glibc on Linux ([f266f09](https://github.com/aymnms/mario-isn/commit/f266f091f46384a131d225725b8a4fec9a43b9ac))

## [1.2.5](https://github.com/aymnms/mario-isn/compare/v1.2.4...v1.2.5) (2026-08-15)


### Bug Fixes

* bundle libSDL3.dylib, the runtime dependency fixup_bundle can't see ([862eb90](https://github.com/aymnms/mario-isn/commit/862eb90ab72240309e163b861f42b55091ccb004))

## [1.2.4](https://github.com/aymnms/mario-isn/compare/v1.2.3...v1.2.4) (2026-08-14)


### Bug Fixes

* preserve symlinks when zipping macOS release artifacts ([30d2371](https://github.com/aymnms/mario-isn/commit/30d237194ccc00084dc0ecfed308309140000aac))

## [1.2.3](https://github.com/aymnms/mario-isn/compare/v1.2.2...v1.2.3) (2026-08-14)


### Bug Fixes

* accept exit code 137 alongside 124 in the smoke test ([9bbd3f1](https://github.com/aymnms/mario-isn/commit/9bbd3f1577bb6c7cb768365d68b6ce5a6304f77f))
* drop the nested container from the Linux smoke test job ([3d5f453](https://github.com/aymnms/mario-isn/commit/3d5f4539e526bf5a8ff099dc6f5010f9de44451b))
* force-kill the smoke-tested game process with timeout --kill-after ([214112c](https://github.com/aymnms/mario-isn/commit/214112ce72a515dd3bc80a91edf586cc996e1876))
* unblock the Linux smoke test's apt-get install ([d2350ab](https://github.com/aymnms/mario-isn/commit/d2350aba815c9aef30e58e8810b2bd1715f6e13c))

## [1.2.2](https://github.com/aymnms/mario-isn/compare/v1.2.1...v1.2.2) (2026-08-14)


### Bug Fixes

* define SDL_MAIN_HANDLED in the domain_tests binary ([814c06d](https://github.com/aymnms/mario-isn/commit/814c06d04059af88588cc195c23df856cfd2dc45))

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
