<a name="readme-top"></a>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">

<h3 align="center">mario-isn</h3>

  <p align="center">
    mario bros in c
    <br />
    <a href="https://github.com/aymnms/art-ascii"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/aymnms/art-ascii/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    ·
    <a href="https://github.com/aymnms/art-ascii/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li><a href="#getting-started">Getting Started</a></li>
    <li><a href="#prerequisites">Prerequisites</a></li>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[EN 🇬🇧]
mario-isn is a Scientific Terminal project in ISN (Computing and digital sciences).
The objective being to recreate a mario bros in c.
The project has been rewarded by the second price of Digicosme Labex : https://digicosme.lri.fr/tiki-read_article.php?articleId=267

[FR 🇫🇷]
mario-isn est un projet de Terminal Scientifique en ISN (Informatique et sciences du numérique).
L'objectif etant de recréer un mario bros en c.
Le projet a été récompencé par le second prix du Labex Digicosme : https://digicosme.lri.fr/tiki-read_article.php?articleId=267

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

1. Clone the project

```bash
  git clone https://github.com/aymerickmichelet/mario-isn.git
```

2. Go to the project directory

```bash
  cd mario-isn
```

3. Compile the program

```bash
  ./compiler.sh
```

## Prerequisites

### macOS

#### Avec Homebrew

1. Install Homebrew :
   ```sh
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```
2. Install GCC :
   ```sh
   brew install gcc
   ```

#### Avec Xcode

1. Install Xcode from l'App Store.
2. Install command line tools :
```sh
xcode-select --install
```

### Windows

#### Avec MinGW

1. Download MinGW from [mingw.org](http://www.mingw.org/).
2. Follow installation instruction.
3. Add `C:\MinGW\bin` to the environment variable `PATH`.

#### Avec MSYS2

1. Download MSYS2 from [msys2.org](https://www.msys2.org/).
2. Follow installation instruction.
3. Open the console MSYS2 and install GCC :
```sh
pacman -Syu
pacman -S mingw-w64-x86_64-gcc
```
1. Add `C:\msys64\mingw64\bin` to the environment variable `PATH`.

### Linux

#### Debian/Ubuntu

1. Open Terminal and install development tools :
```sh
sudo apt update
sudo apt install build-essential
```

#### Fedora

1. Open Terminal and install development tools :
```sh
sudo dnf groupinstall "Development Tools"
```

#### Arch Linux

1. Open Terminal and install development tools :
```sh
sudo pacman -S base-devel
```


<!-- USAGE EXAMPLES -->
## Usage

1. Compile the program (getting started)

2. Run the program

```bash
  ./mario-isn <text>
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Collaborator

- [Aymerick Michelet](https://github.com/aymnms)
- [Anthony Quéré](https://github.com/Anthony-Jhoiro)
- Léo LIRZIN


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/aymnms/mario-isn.svg?style=for-the-badge
[contributors-url]: https://github.com/aymnms/mario-isn/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/aymnms/mario-isn.svg?style=for-the-badge
[forks-url]: https://github.com/aymnms/mario-isn/network/members
[stars-shield]: https://img.shields.io/github/stars/aymnms/mario-isn.svg?style=for-the-badge
[stars-url]: https://github.com/aymnms/mario-isn/stargazers
[issues-shield]: https://img.shields.io/github/issues/aymnms/mario-isn.svg?style=for-the-badge
[issues-url]: https://github.com/aymnms/mario-isn/issues
[license-shield]: https://img.shields.io/github/license/aymnms/mario-isn.svg?style=for-the-badge
[license-url]: https://github.com/aymnms/mario-isn/blob/master/LICENSE.txt
