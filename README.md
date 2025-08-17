<a id="readme-top"></a>

<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![License][license-shield]][license-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/aymnms/mario-isn">
    <img src="ressources/img/sdl_icone.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Mario-ISN</h3>

  <p align="center">
    A Mario Bros game in C, ISN scientific project
    <br />
    <a href="https://github.com/aymnms/mario-isn"><strong>Explore the documentation »</strong></a>
    <br />
    <br />
    <img src="img/screenshot-7.gif" alt="Logo" width="600" height="500">
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
    <li>
      <a href="#about-the-project">About the Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#commands">Commands</a></li>
        <li><a href="#download-release">Download release</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
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

Initially developed in 2017/2018 with 2 fellow students, the project has been updated in SDL2.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

Here are the steps to run the project locally (currently works on macOS ARM64 and Linux - Windows still in progress).

### Prerequisites

* C
* Makefile
* CMake
* Ninja
* SDL2, SDL2_image, SDL2_mixer
* homebrew (for macOS)
* apt (for Linux)

### Installation

**⚠️ Instructions are split for macOS and Linux**

#### macOS

1. **Clone the repository**

```sh
git clone https://github.com/aymnms/mario-isn.git
cd mario-isn
```

2. **Install dependencies**

```sh
xcode-select --install                                 # Outils Apple (clang, lldb…)
brew install cmake ninja sdl2 sdl2_image sdl2_mixer    # CMake + (optionnel) Ninja
```

3. **Build and Run**

```sh
make run
```

#### Linux

1. **Clone the repository**

```sh
git clone https://github.com/aymnms/mario-isn.git
cd mario-isn
```

2. **Install dependencies**

```sh
sudo apt update
sudo apt install build-essential cmake ninja-build libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
```

3. **Build and Run**

```sh
make run
```

### Commands

To know what command you can to execute
```sh
make
```


### Download release

#### macOS (only arm)

ℹ️ **Note for distribution**: The generated `.app` may be marked as coming from an unidentified source (attribute `com.apple.quarantine`). To run the application, go to system settings to “execute anyway”.

[![Game screenshot][product-screenshot-8]](#)

#### Linux

ℹ️ To run the Linux release, make sure you have SDL2, SDL2_image, and SDL2_mixer installed on your system. You can install them via your package manager (e.g., `apt`).

You can run the provided tarball release directly. If SDL2 libraries are not installed system-wide, you might need to set your `LD_LIBRARY_PATH` accordingly.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE -->
## Usage

The game launches in windowed mode, with a main menu (the size of which cannot be changed).
Use the keyboard arrows to move the player, jump and interact with enemies.

| [![Game screenshot][product-screenshot-1]](#) | [![Game screenshot][product-screenshot-2]](#) | [![Game screenshot][product-screenshot-3]](#) |
|-----------------------------------------------|-----------------------------------------------|-----------------------------------------------|
| [![Game screenshot][product-screenshot-4]](#) | [![Game screenshot][product-screenshot-5]](#) | [![Game screenshot][product-screenshot-6]](#) |


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTRIBUTING -->
## Contributing

### Initial contributors

- Aymerick Michelet - [@aymnms](https://github.com/aymnms)
- Anthony Quéré - [@Anthony-Jhoiro](https://github.com/Anthony-Jhoiro)
- Léo LIRZIN

### And others... (or not 🥲)

<a href="https://github.com/aymnms/mario-isn/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=aymnms/mario-isn" alt="Contributors" />
</a>


<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* The ISN teaching team
* Labex Digicosme

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
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
[product-screenshot-1]: ressources/img/screenshot-1.png
[product-screenshot-2]: ressources/img/screenshot-2.png
[product-screenshot-3]: ressources/img/screenshot-3.png
[product-screenshot-4]: ressources/img/screenshot-4.png
[product-screenshot-5]: ressources/img/screenshot-5.png
[product-screenshot-6]: ressources/img/screenshot-6.png
[product-screenshot-7]: ressources/img/screenshot-7.gif
[product-screenshot-8]: ressources/img/screenshot-8.png
