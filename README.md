<!-- Improved compatibility of back to top link -->
<a id="readme-top"></a>

<!-- PROJECT SHIELDS -->
[![Build][build-shield]][build-url]
[![Release][release-shield]][release-url]
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![License][license-shield]][license-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/aymnms/mario-isn">
    <img src=".github/images/sdl_icone.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Mario-ISN</h3>

  <p align="center">
    A Mario Bros game in C, ISN scientific project
    <br />
    <a href="https://github.com/aymnms/mario-isn/releases"><strong>Download the latest release »</strong></a>
    <br />
    <br />
    <img src=".github/images/screenshot-7.gif" alt="Gameplay demo" width="600" height="500">
    <br />
    <a href="https://github.com/aymnms/mario-isn/issues/new?labels=bug&template=bug-report---.md">Report a bug</a>
    &middot;
    <a href="https://github.com/aymnms/mario-isn/issues/new?labels=enhancement&template=feature-request---.md">Suggest a feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About the Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#platform-support">Platform Support</a></li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li>
      <a href="#building-from-source">Building From Source</a>
      <ul>
        <li><a href="#macos-apple-silicon">macOS (Apple Silicon)</a></li>
        <li><a href="#macos-intel">macOS (Intel)</a></li>
        <li><a href="#linux">Linux</a></li>
        <li><a href="#windows">Windows</a></li>
      </ul>
    </li>
    <li><a href="#architecture">Architecture</a></li>
    <li><a href="#releases">Releases</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About the Project

**Mario-ISN** is a project for the baccalauréat scientifique, specializing in ISN (Computer Science and Numerical Sciences).
The goal is to recreate a Mario Bros-type game in C language, using the SDL2 library.

The project received the **second prize of Labex Digicosme**:
🔗 [Read the article (french)](https://digicosme.cnrs.fr/concours-isn2018/)

Initially developed in 2017/2018 with 2 fellow students, the project has since been updated to SDL2 and given a modern,
fully automated build/release pipeline: every push to `main` is built, packaged and published for four platforms
without any manual step.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

[![C][C-badge]][C-url]
[![CMake][CMake-badge]][CMake-url]
[![SDL2][SDL2-badge]][SDL2-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- PLATFORM SUPPORT -->
## Platform Support

| OS | Runs | Verified by CI |
|---|---|---|
| macOS (Apple Silicon) | ✅ | ✅ |
| macOS (Intel) | ✅ | ✅ — cross-compiled via Rosetta 2 on a `macos-latest` runner (no reliable native Intel runner is available from GitHub anymore) |
| Linux | ✅ | ✅ |
| Windows | ✅ | ✅ — dependencies resolved via [vcpkg](https://github.com/microsoft/vcpkg) |

Every push to a build-relevant path (source, assets, CMake/Makefile, build scripts) is verified end-to-end on all four
targets — see [`.github/workflows/build.yml`](.github/workflows/build.yml). Every downloaded release is fully
self-contained: SDL2/SDL2_image/SDL2_mixer are bundled into the artifact, so **there is nothing to install** on the
target machine.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

The fastest way to play is to grab a pre-built binary for your platform from the [releases page][release-url]. The
sections below ([Building From Source](#building-from-source)) are for compiling it yourself instead.

### Prerequisites

None — every release artifact bundles its own SDL2/SDL2_image/SDL2_mixer libraries, so there is nothing to install
first.

### Installation

Go to the [**Releases**][release-url] page and download the asset matching your OS:

| OS | Download | Then |
|---|---|---|
| macOS (Apple Silicon / Intel) | `MarioISN-macos-{arm,intel}.zip` | Extract, run the `.app` |
| Windows | `MarioISN-windows-setup.exe` | Run it — installs to your user folder (no admin needed) with a Start Menu shortcut |
| Linux (x86_64) | `MarioISN-x86_64.AppImage` | `chmod +x MarioISN-x86_64.AppImage`, then run it — no installation needed |

ℹ️ **Note for macOS**: the downloaded `.app` may be marked as coming from an unidentified source (`com.apple.quarantine`). Go to System Settings → Privacy & Security to "Open Anyway".

ℹ️ **Note for Windows**: the installer isn't code-signed (no publisher certificate), so Windows SmartScreen may show a "Windows protected your PC" warning. Click "More info" → "Run anyway" to launch it.

[![Game screenshot][product-screenshot-8]](#)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE -->
## Usage

The game launches in windowed mode, with a main menu (the size of which cannot be changed).
Use the keyboard arrows to move the player, jump and interact with enemies.

| [![Game screenshot][product-screenshot-1]](#) | [![Game screenshot][product-screenshot-2]](#) | [![Game screenshot][product-screenshot-3]](#) |
|-----------------------------------------------|-----------------------------------------------|-----------------------------------------------|
| [![Game screenshot][product-screenshot-4]](#) | [![Game screenshot][product-screenshot-5]](#) | [![Game screenshot][product-screenshot-6]](#) |

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- BUILDING FROM SOURCE -->
## Building From Source

```sh
git clone https://github.com/aymnms/mario-isn.git
cd mario-isn
```

Every OS below installs [CMake](https://cmake.org/) ≥ 3.20, [Ninja](https://ninja-build.org/) (macOS/Linux) and
SDL2/SDL2_image/SDL2_mixer, then delegates to the [`Makefile`](Makefile), which wraps the CMake configure/build
steps. `make run` (no arguments) does a quick debug build and launches the game — useful while developing; the
per-OS targets below produce the same optimized, self-contained bundle CI publishes to releases.

### macOS (Apple Silicon)

```sh
xcode-select --install                                 # Apple tools (clang, lldb…)
brew install cmake ninja pkg-config sdl2 sdl2_image sdl2_mixer
make prod-arm
```

### macOS (Intel)

The Intel build is cross-compiled from Apple Silicon via Rosetta 2 — `clang -arch x86_64` compiles natively without
Rosetta, but Homebrew's default `/opt/homebrew` prefix only ships arm64 libs, so a second, x86_64 Homebrew installed
under Rosetta at `/usr/local` provides the SDL2 stack. See [Architecture](#architecture) for why.

```sh
softwareupdate --install-rosetta --agree-to-license   # if not already installed
arch -x86_64 /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
arch -x86_64 /usr/local/bin/brew install sdl2 sdl2_image sdl2_mixer
make prod-intel
```

### Linux

```sh
sudo apt-get install cmake ninja-build pkg-config patchelf \
  libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
make prod-linux
```

### Windows

Dependencies are resolved via [vcpkg](https://github.com/microsoft/vcpkg):

```powershell
git clone https://github.com/microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install sdl2 sdl2-image sdl2-mixer --triplet x64-windows

cmake -S . -B build-win -A x64 -DCMAKE_TOOLCHAIN_FILE="$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build build-win --config Release
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ARCHITECTURE -->
## Architecture

```
mario-isn/
├── src/                  # Game source (C)
│   ├── main.c            # Entry point, SDL init, main loop
│   ├── display.c         # Rendering
│   ├── path.c            # Portable asset path resolution
│   ├── menu/              # Main menu
│   └── game/               # Gameplay: player, enemies, collisions, levels
├── include/              # Headers matching src/
├── ressources/           # Images, music, level files, macOS icon
├── cmake/                # CMake helper modules (macOS lib bundling)
├── scripts/              # Build/release helper scripts (Linux lib bundling, version bump)
├── CMakeLists.txt        # Build definition, per-OS packaging/bundling logic
├── Makefile              # Convenience wrapper around CMake
└── .github/workflows/    # CI build matrix + automated release pipeline
```

Assets and their platform-specific SDL2 libraries are bundled next to the executable at build time (`.app` bundle on
macOS, alongside the binary on Linux/Windows), so a downloaded release runs standalone — see
[`cmake/FixupBundleMacOS.cmake`](cmake/FixupBundleMacOS.cmake) and
[`scripts/bundle_libs_linux.sh`](scripts/bundle_libs_linux.sh) for how.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- RELEASES -->
## Releases

Releases are fully automated with [semantic-release](https://semantic-release.gitbook.io/): every push to `main`
that touches a build-relevant path computes the next version from commit messages, publishes a GitHub Release with
an auto-generated [`CHANGELOG.md`](./CHANGELOG.md), and attaches pre-built binaries for all four supported platforms.

Commit messages must follow [Conventional Commits](https://www.conventionalcommits.org/):

| Prefix | Effect |
|---|---|
| `feat:` | Minor version bump |
| `fix:`, `perf:` | Patch version bump |
| `feat!:` / `fix!:` / `BREAKING CHANGE:` footer | Major version bump |
| `docs:`, `chore:`, `ci:`, `test:`, `style:`, `refactor:`, `build:` | No release triggered |

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

- [ ] Isolated CI smoke test (container without SDL2 installed) for the Linux bundling
- [ ] Cache the vcpkg dependency tree in CI instead of rebuilding SDL2 from source on every Windows run
- [ ] Suppress the console window that opens alongside the game on Windows
- [ ] `clang-format`/`.editorconfig` for consistent C style
- [ ] Extract a testable game-logic core, decoupled from SDL, so gameplay code can have unit tests

See the [open issues](https://github.com/aymnms/mario-isn/issues) for the full list of proposed features and known
issues, and [`PLAN.md`](./PLAN.md) / [`AUDIT.md`](./AUDIT.md) for the detailed engineering history behind the
multi-platform build and release pipeline.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTRIBUTING -->
## Contributing

Contributions, issues and feature requests are welcome.

1. Fork the project
2. Create your feature branch (`git checkout -b feat/amazing-feature`)
3. Commit your changes following [Conventional Commits](https://www.conventionalcommits.org/) (`git commit -m 'feat: add amazing feature'`) — this is what drives automated versioning, see [Releases](#releases)
4. Push to your branch (`git push origin feat/amazing-feature`)
5. Open a Pull Request

### Initial contributors

- Aymerick Michelet - [@aymnms](https://github.com/aymnms)
- Anthony Quéré - [@Anthony-Jhoiro](https://github.com/Anthony-Jhoiro)
- Léo LIRZIN

### And others... (or not 🥲)

<a href="https://github.com/aymnms/mario-isn/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=aymnms/mario-isn" alt="Contributors" />
</a>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See [`LICENSE`](LICENSE) for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* The ISN teaching team
* Labex Digicosme
* [SDL2](https://www.libsdl.org/)
* [Best-README-Template](https://github.com/othneildrew/Best-README-Template) — this README's structure is based on it

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
[build-shield]: https://img.shields.io/github/actions/workflow/status/aymnms/mario-isn/build.yml?branch=main&style=for-the-badge&label=build
[build-url]: https://github.com/aymnms/mario-isn/actions/workflows/build.yml
[release-shield]: https://img.shields.io/github/v/release/aymnms/mario-isn.svg?style=for-the-badge
[release-url]: https://github.com/aymnms/mario-isn/releases
[contributors-shield]: https://img.shields.io/github/contributors/aymnms/mario-isn.svg?style=for-the-badge
[contributors-url]: https://github.com/aymnms/mario-isn/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/aymnms/mario-isn.svg?style=for-the-badge
[forks-url]: https://github.com/aymnms/mario-isn/network/members
[stars-shield]: https://img.shields.io/github/stars/aymnms/mario-isn.svg?style=for-the-badge
[stars-url]: https://github.com/aymnms/mario-isn/stargazers
[issues-shield]: https://img.shields.io/github/issues/aymnms/mario-isn.svg?style=for-the-badge
[issues-url]: https://github.com/aymnms/mario-isn/issues
[license-shield]: https://img.shields.io/github/license/aymnms/mario-isn.svg?style=for-the-badge
[license-url]: https://github.com/aymnms/mario-isn/blob/main/LICENSE
[C-badge]: https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white
[C-url]: https://en.wikipedia.org/wiki/C_(programming_language)
[CMake-badge]: https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white
[CMake-url]: https://cmake.org/
[SDL2-badge]: https://img.shields.io/badge/SDL2-000000?style=for-the-badge
[SDL2-url]: https://www.libsdl.org/
[product-screenshot-1]: .github/images/screenshot-1.png
[product-screenshot-2]: .github/images/screenshot-2.png
[product-screenshot-3]: .github/images/screenshot-3.png
[product-screenshot-4]: .github/images/screenshot-4.png
[product-screenshot-5]: .github/images/screenshot-5.png
[product-screenshot-6]: .github/images/screenshot-6.png
[product-screenshot-7]: .github/images/screenshot-7.gif
[product-screenshot-8]: .github/images/screenshot-8.png
