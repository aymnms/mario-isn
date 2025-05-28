<!-- Improved compatibility of back to top link -->
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
    <img src="img/sdl_icone.png" alt="Logo" width="80" height="80">
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
      <ul>
        <li><a href="#built-with">Technologies Used</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
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

Initially developed in 2017/2018 with 2 fellow students, the project has been updated in SDL2.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Technologies Used

* C
* CMake
* SDL2, SDL2_image, SDL2_mixer

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

Here are the steps to run the project locally (currently only on macOS ARM64 - windows and linux in progress).

### Prerequisites

* C
* CMake
* SDL2, SDL2_image, SDL2_mixer

#### macOS (arm - Apple Silicon):
* [Homebrew](https://brew.sh/) to manage dependencies

### Installation

1. **Clone the repository**

```sh
git clone https://github.com/aymnms/mario-isn.git
cd mario-isn
```

2. **Install dependencies**

macOS
```sh
brew install sdl2 sdl2_image sdl2_mixer
```

3. **Config CMake**

macOS:
```sh
cmake -B build-arm -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="arm64"
```

4. **Build**

macOS:
```sh
cmake --build build-arm --config Release
```

5. **Run the game**

macOS:
```sh
cd build-arm
./mario-isn
```

### Download release

#### macOS (only arm)

ℹ️ **Note for distribution**: The generated `.app` may be marked as coming from an unidentified source (attribute `com.apple.quarantine`). To run the application directly:

```
xattr -d com.apple.quarantine ./mario_isn.app
```

Or you can go to system settings to “execute anyway”.

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

<!-- ROADMAP -->
## Roadmap

- [x] Redesign of the graphical interface
- [x] Added animations for the player
- [x] Collision handling with enemies
- [ ] Rendering optimization
- [ ] Adding additional levels

See the [open issues](https://github.com/aymnms/mario-isn/issues) for more.

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
[product-screenshot-1]: img/screenshot-1.png
[product-screenshot-2]: img/screenshot-2.png
[product-screenshot-3]: img/screenshot-3.png
[product-screenshot-4]: img/screenshot-4.png
[product-screenshot-5]: img/screenshot-5.png
[product-screenshot-6]: img/screenshot-6.png
[product-screenshot-7]: img/screenshot-7.gif
[product-screenshot-8]: img/screenshot-8.png
