# Audit — mario-isn

> Dernière mise à jour : 2026-08-14
> Statut de l'audit : ✅ Terminé

## 0. Résumé exécutif

Mario-ISN est un jeu type Mario Bros en C99/SDL2, projet de bac ISN (2017/2018) modernisé récemment (build CMake/Ninja, CI multi-OS, semantic-release). La mission est de reprendre le dépôt et le faire avancer à partir des 4 issues GitHub ouvertes : un pipeline de release cassé (#16), une release non portable car elle dépend des libs SDL2 installées sur la machine cible (#15), et l'absence de build/CI Windows (#8, #9). Le code applicatif fonctionne (macOS arm64 et Linux buildent en CI) ; les manques sont côté outillage (packaging, portabilité, CI), pas côté logique de jeu.

## 1. Cartographie

- **Stack technique réelle** : C99 (`CMAKE_C_STANDARD 99`), build CMake 3.20+ / Ninja, dépendances SDL2 + SDL2_image + SDL2_mixer (résolues via config CMake Homebrew/vcpkg, repli sur pkg-config pour Linux). Tooling annexe en Node.js/npm uniquement pour `semantic-release` (aucune dépendance runtime Node côté jeu).
- **Arborescence et points d'entrée** :
  - `src/main.c` — point d'entrée, boucle SDL.
  - `src/menu/` — menu principal (`MENU.c`, `init_menu.c`).
  - `src/game/` — logique de jeu (`GAME.c`, `init_game.c`, `conditions.c`), sous-dossiers `joueur/` (déplacement, saut, animation, musique, niveau) et `mechant/` (ennemis, Bowser, collisions, déplacement).
  - `src/display.c`, `src/globals.c`, `src/path.c` — rendu, état global, résolution de chemins d'assets.
  - `include/` — headers correspondants, dont `path.h` (résolution d'assets portable) et `MARIO_variables.h`/`globals.h` (état global partagé).
  - `ressources/` (24 Mo) — images, musiques, niveaux (`bin/`), icône macOS ; copiés dans le bundle/à côté de l'exécutable au build (voir `CMakeLists.txt`).
  - `scripts/update_version.sh` — bump de version dans `CMakeLists.txt`, appelé par semantic-release.
  - `.github/workflows/build.yml` — build matrix macOS/Linux (Windows commenté).
  - `.github/workflows/release.yml` — déclenché par `workflow_run` sur le build, télécharge les artefacts et lance `semantic-release`.
- **Découpage actuel entre logique métier et code d'intégration** : faible séparation — la logique de jeu (déplacement, collisions, IA ennemis) est directement mêlée aux appels SDL (rendu, entrées clavier, son) dans les mêmes fichiers `.c`. Il n'existe pas de couche "domaine pur" isolée de SDL. C'est cohérent avec un projet de jeu SDL simple, mais cela signifie qu'aucun test unitaire classique n'est possible sans un minimum de refactoring (hors périmètre des 4 issues actuelles).

## 2. Fonctionnement bout-en-bout

1. `main.c` initialise SDL/SDL_image/SDL_mixer, crée la fenêtre, appelle le menu (`menu/MENU.c`).
2. Le menu (boutons rendus via SDL) permet de lancer une partie → `game/GAME.c` prend la main, avec une boucle de jeu classique (poll des événements clavier, mise à jour physique joueur/ennemis, détection de collisions, rendu).
3. Les niveaux sont chargés depuis `ressources/bin/*.lvl` via `path_bin()` (résolution de chemin par `src/path.c`, basée sur `SDL_GetBasePath()` avec repli sur 1-2 niveaux de remontée de dossier pour gérer le layout `.app` macOS vs exécution en dev).
4. Les assets (images `ressources/img/`, musiques `ressources/musique/`) sont chargés de la même façon via `path_img()`/`path_music()`.
5. Le build CMake copie `ressources/{img,musique,bin}` dans le bundle `.app` (macOS) ou à côté de l'exécutable (Linux/Windows) en post-build, donc les assets sont toujours livrés avec le binaire.
6. En CI (`build.yml`), chaque OS de la matrice build, package (zip macOS, tar.gz Linux) puis uploade l'artefact. `release.yml` se déclenche ensuite sur la fin de ce workflow, télécharge les artefacts et exécute `semantic-release` qui bump la version, génère le changelog et publie la release GitHub avec les binaires attachés.

## 3. Dépendances

- **Bibliothèques tierces (runtime jeu)** : SDL2, SDL2_image, SDL2_mixer — dynamiquement liées (`.dylib`/`.so`), **non embarquées** dans l'artefact distribué.
- **Outils de build** : CMake, Ninja, un compilateur C (clang/gcc), `pkg-config` (Linux).
- **Toolchain de release** : Node 20 + npm, `semantic-release` et plugins (`commit-analyzer`, `release-notes-generator`, `changelog`, `exec`, `git`, `github`) — utilisés uniquement en CI, aucun impact sur le runtime du jeu.
- **Éléments spécifiques à un environnement** :
  - macOS : bundle `.app`, icône `.icns`, signature ad-hoc (`codesign --force --deep --sign -`) en CI.
  - Résolution de chemin (`path.c`) dépend de `SDL_GetBasePath()` — comportement différent par OS (bundle `.app` vs dossier plat), déjà anticipé avec repli générique.
  - Aucune dépendance Windows testée : le job Windows de `build.yml` est entièrement commenté, `vcpkg` esquissé mais jamais exécuté.

## 4. Contraintes et blocages vis-à-vis de l'objectif de la mission

Les 4 issues ouvertes définissent le périmètre de la mission :

- **#16 — le workflow de release ne trouve pas l'artefact** : `release.yml` télécharge "0 artifact(s)" (confirmé par les logs du run échoué et la capture jointe à l'issue). Deux causes racines identifiées :
  1. `actions/download-artifact@v4`, quand on cible un `run-id` différent du run courant (cas de `workflow_run`), nécessite un `github-token` explicite pour s'authentifier auprès de l'API — sans ce paramètre, l'action ne trouve aucun artefact du run cible, même si celui-ci en contient. Le step ne le passait pas.
  2. Même une fois le token ajouté, `download-artifact@v4` place par défaut chaque artefact dans un sous-dossier nommé d'après l'artefact (ex. `dist/MarioISN-macos-arm/MarioISN-macos-arm.zip`) alors que `.releaserc.json` attend un chemin plat (`dist/MarioISN-macos-arm.zip`) — il faut `merge-multiple: true` pour aplatir.
- **#15 — bundler les libs dans le build** : SDL2/SDL2_image/SDL2_mixer sont liées dynamiquement et ne sont pas embarquées dans l'artefact. Sur une machine qui n'a pas installé ces libs via Homebrew/apt, l'exécutable ne démarre pas (`dyld: Library not loaded` / `.so not found`). Bloque une distribution grand public de la release.
- **#8 / #9 — build et CI Windows** : aucun code n'est spécifiquement incompatible Windows (pas d'appel POSIX-only repéré dans les fichiers audités), mais rien n'a jamais été testé/compilé sur Windows. `build.yml` a un job Windows entièrement commenté (dépendances vcpkg, configure/build, packaging), à réactiver et fiabiliser. Cela dépend implicitement d'un lieur SDL2 fonctionnel via vcpkg en CI — jamais validé.

## 5. Questions structurantes tranchées par cet audit

- **Question** : pour #15, faut-il lier SDL2 statiquement ou embarquer les `.dylib`/`.so` dynamiques à côté du binaire (rpath local) ?
  **Décision** : embarquer les bibliothèques dynamiques dans l'artefact (copie post-build + réécriture du chemin de chargement, ex. `install_name_tool`/`otool` sur macOS, `patchelf`/`LD_LIBRARY_PATH` relatif sur Linux) plutôt que passer en link statique.
  **Justification** : Homebrew ne fournit pas de libs SDL2 statiques par défaut (le `find_package(... CONFIG)` actuel résout des `.dylib` partagées) ; forcer un link statique demanderait de compiler SDL2 soi-même ou de changer de gestionnaire de dépendances (vcpkg partout), ce qui dépasse largement le "faible effort" attendu pour cette issue et risque de casser le build macOS/Linux qui fonctionne déjà. Le bundling dynamique est l'approche standard pour ce genre de projet CMake+SDL2 et s'intègre au mécanisme de copie de ressources déjà en place dans `CMakeLists.txt`.
- **Question** : pour #16, faut-il changer le déclencheur de release (`workflow_run`) plutôt que de corriger le téléchargement d'artefact ?
  **Décision** : garder `workflow_run` et corriger uniquement le step `download-artifact` en lui passant `github-token`.
  **Justification** : le déclencheur `workflow_run` n'est pas en cause (les logs montrent que le job démarre bien et identifie le bon run) ; seule l'authentification cross-run du téléchargement d'artefact est en faute. Changer de déclencheur serait une réécriture non justifiée par le diagnostic.

## 6. Qualité générale du code

- **Tests existants** : aucun (`find . -iname "*test*"` ne remonte rien côté code applicatif). Cohérent avec le fort couplage logique/SDL relevé en §1 — non traité ici car hors périmètre des 4 issues, mais noté en dette technique.
- **Gestion d'erreurs** : basique (retours SDL vérifiés par endroits dans `main.c`/`init_game.c`), pas de stratégie homogène de logging/diagnostic.
- **Configuration** : pas de fichier de config runtime, pas de secrets dans le repo. CI utilise `secrets.GITHUB_TOKEN` standard.
- **Dette technique repérée (hors périmètre)** : pas de séparation domaine/SDL (bloquerait des tests unitaires futurs) ; pas de linter/formatter C configuré (`clang-format`, `clang-tidy` absents) ; pas de `.editorconfig`.

## 7. Recommandations priorisées

| # | Recommandation | Effort | Risque si non traité | Lié à la mission actuelle ? |
|---|---|---|---|---|
| 1 | Corriger `download-artifact@v4` dans `release.yml` (ajouter `github-token`) | Faible | Aucune release publiée depuis le passage à ce pipeline — le projet reste bloqué en `1.1.0-alpha` | Oui — #16 |
| 2 | Embarquer les libs SDL2/SDL2_image/SDL2_mixer dans les artefacts macOS/Linux | Moyen | Binaire distribué inutilisable sur une machine sans les libs préinstallées | Oui — #15 |
| 3 | Réactiver et fiabiliser le job Windows dans `build.yml` (vcpkg + configure/build/package) | Moyen | Windows reste non supporté malgré la demande explicite | Oui — #8/#9 |
| 4 | Ajouter `clang-format`/`.editorconfig` | Faible | Dérive de style au fil des contributions | Non (dette technique générale) |
| 5 | Extraire un noyau de logique de jeu testable indépendamment de SDL | Élevé | Toute évolution de la logique de jeu reste non testable | Non (dette technique générale) |

## 8. Questions ouvertes réellement bloquantes

- Aucune. Les 4 issues ont un diagnostic et une décision d'implémentation clairs à partir du code et des logs CI disponibles publiquement.

## 9. Audit complémentaire — qualité du code (2026-08-15)

Suite à la demande explicite de l'utilisateur de "nettoyer le code" (repris de la dette `J5-3` laissée en `⬜ À faire`), audit ciblé sur la qualité/correction du code C, au-delà des 4 issues d'origine. Méthode : compilation avec `-Wall -Wextra -Wpedantic -Wshadow -Wconversion` (aucun de ces flags n'est actuellement activé dans `CMakeLists.txt` — le projet compile "propre" uniquement parce que rien ne vérifie), puis lecture ciblée des zones suspectes.

- **199 avertissements** avec les flags stricts ci-dessus, dominés par `-Wstrict-prototypes` (161 occurrences) : quasiment toutes les déclarations de fonctions sans paramètres sont écrites `void f();` au lieu de `void f(void);` — en C (contrairement au C++), `()` dans une déclaration signifie "liste d'arguments non spécifiée", pas "aucun argument" : ça désactive la vérification des arguments à l'appel, un vrai risque de correction, pas un simple style.
- **Code mort compilé** : `src/game/mechant/addElem.c` est intégralement commenté (l'auteur d'origine avait écrit `// TO DELETE` en tête), mais toujours listé dans `CMakeLists.txt` et donc compilé (`-Wempty-translation-unit`) ; `include/MARIO_mechant.h` déclare encore les prototypes orphelins `addChamp()`/`grow()` qui n'existent plus nulle part. `include/MARIO_variables.h` est un header entier jamais `#include`é par aucun fichier du build (`grep` confirmé) — copie obsolète et incohérente des globals réels (tailles `[10]` au lieu des vraies `[20]`).
- **Collision de symboles globaux** (trouvaille la plus sérieuse) : `double x` (`src/globals.c`, variable de progression utilisée par la physique du saut dans `saut_joueur.c`) et `int x` (`src/menu/MENU.c`, coordonnée de clic souris dans `start_game()`) sont **deux variables globales distinctes portant le même nom**, ni l'une ni l'autre déclarée `static`. Ça compile et link aujourd'hui sans erreur (le linker fusionne un symbole "tentative" non initialisé — le `int x` de MENU.c, jamais initialisé à la déclaration — avec la définition initialisée `double x = 0` de `globals.c`, un comportement de fusion de symboles communs non garanti par le standard C mais toléré par la plupart des toolchains dont MSVC), et reste bénin en pratique uniquement parce que le code de saut réinitialise `x` explicitly avant de l'utiliser à chaque saut. Reste une vraie violation de règle de portée (One Definition Rule) qui pourrait casser silencieusement sur un futur changement de toolchain/optimisation.
- **Tailles de tableaux `extern` incohérentes avec la vraie définition** : `statue`/`tableau_mechant`/`direction_mechant` sont définis une fois dans `main.c` avec une taille réelle de 20, mais re-déclarés `extern ... [10]` dans `GAME.c`/`init_game.c` — même classe de comportement indéfini que le bug Bowser corrigé en `J11` (déclarations conflictuelles), qui n'a pas encore causé de crash observé mais reste un vrai risque latent.
- **`char lvl[10][140]`** (grille du niveau courant) définie sans `extern` directement dans le header `MARIO_niveau.h`, inclus par plusieurs fichiers `.c` — fonctionne aujourd'hui par fusion de "définitions tentatives" (même mécanisme fragile que le point `x` ci-dessus), au lieu d'une définition unique dans un `.c` avec un `extern` propre dans le header (le pattern déjà correctement utilisé pour `perso`, `img`, `cadre`, etc. dans `globals.h`/`globals.c`).
- **Reste** (moins critique, à traiter au cas par cas) : `-Wfloat-conversion`/`-Wimplicit-int-conversion`/`-Wsign-conversion`/`-Wsign-compare` (conversions numériques implicites dans la physique du saut et le parsing des niveaux — probablement inoffensives mais jamais rendues explicites), `-Wshadow` (4 occurrences, dont un paramètre de fonction nommé `x` qui masque justement le `double x` global ci-dessus), `-Wlogical-op-parentheses` (4 occurrences de `&&` dans un `||` sans parenthésage explicite — précédence correcte en C mais ambiguë à la lecture).
- **Recommandation** : traiter par lots indépendants et vérifiables (code mort → prototypes → symboles/tailles incohérents → conversions/masquage → activation permanente de `-Wall -Wextra` en CI comme garde-fou), dans cet ordre de risque croissant, avant de reprendre l'extraction de logique métier prévue à l'origine par `J5-3` (qui reste le chantier le plus risqué : toucher la logique de jeu elle-même, pas juste sa forme).

## 10. Audit de suivi — état du code après `J5-3` (2026-08-16)

Nouvel audit demandé par l'utilisateur une fois `J5-3` (a-g) fusionné, pour vérifier honnêtement ce qui a été fait vs ce qui reste. Méthode : lecture directe du code réel (pas confiance aveugle en `PLAN.md`), build propre vérifié (`-Wall -Wextra -Werror`, `ctest` 53/53).

**Confirmé propre** : les classes de bug ciblées par `J5-3`/`J10`/`J11` (fuites de texture, `SDL_Rect` non initialisées dans `go()`/`goM()`/`goB()`/`niveauSelect()`, collision de symboles globaux, tailles `extern` incohérentes) sont bien résolues, vérifié par lecture directe.

- **Bug réel trouvé et corrigé immédiatement** (sévérité haute, effort faible) : dans `goB()` (`bowser.c`), un copier-coller raté laisse `BSSO` jamais décalée (reste à l'origine brute de Bowser) et décale `BSO` deux fois (250px de décalage en y au lieu de 100px prévu). Utilisé comme points de test pour "y a-t-il un trou sous Bowser" (`case 666`, vérifié à chaque frame) et "y a-t-il un mur à gauche" (`case -1`) — ces deux vérifications lisaient la mauvaise ligne de tuiles. Même fichier que le crash Windows corrigé en `J11`, bug différent, resté actif jusqu'ici. Corrigé (renommage de 2 variables), vérifié build + `ctest` + Docker CI-exact.
- **Trouvaille moyenne, non corrigée** : `niveauSelect()` (`niveau.c`) boucle sur `fgetc()` sans jamais vérifier `feof()` — si le marqueur `#<niveau>` attendu est absent du fichier `niveau.lvl` (asset corrompu/tronqué), le jeu boucle indéfiniment au lieu d'échouer proprement.
- **Trouvaille moyenne, non corrigée** : les indices de `lvl[10][140]` ne sont jamais bornés avant lecture (`go()`, `goM()`, `goB()`) ; les limites de scroll (`decalage < 6700`, `pos_perso.x < 500`, dans `domain/movement.c`) donnent une position monde max de 7200px, soit `(7200+40)/50 ≈ 144` — 4-5 colonnes au-delà des 140 valides. Lecture hors-limites latente sur un tableau global (comportement indéfini, pas de crash observé à ce jour).
- **Couplage SDL/logique** : le module `src/domain/` ne couvre que ~86 lignes sur ~2 030 dans `src/game/` (~4%) — `J5-3e` a délibérément extrait un périmètre étroit et sûr. `goB()` en particulier (collision/déplacement de Bowser) reste le plus gros morceau de logique non extraite et non testée de tout le dépôt.
- **Couverture de tests** : uniquement les 5 fichiers de `src/domain/`. Toute l'IA ennemie, l'intégration physique du joueur, le parsing de niveau et la boucle de jeu (`GAME.c`) restent à 0% de couverture automatisée.
- **Dette mineure identifiée** : constantes magiques bypassant `MAX_MECHANTS` (7 sites avec `<= 19`/`< 20` en dur) et absence d'équivalent pour la grille `10×140` (4 sites) ; `extern` redondants dans 13 fichiers (dont des doublons au sein d'un même fichier) — exactement l'habitude qui a causé les bugs `lvl`/`statue` corrigés en `J5-3c` ; globals `boolSB`/`taille` mortes (`deplacement_mechant.c`) — un `-Wunused-variable` ne les détecte pas car elles ont une liaison externe ; `srand(time(NULL))` appelé à chaque frame par méchant (jusqu'à ~100×/s) alors que `rand()` n'est appelé nulle part dans tout le dépôt ; 8 des 16 headers du projet (`MARIO_*.h`) n'ont aucun garde d'inclusion, contrairement au reste de l'arbre.
- **Non prioritaire** : gestion d'erreurs incohérente après chargement d'assets (`create_texture()` vérifié en interne mais son retour rarement vérifié par l'appelant ; `Mix_LoadMUS`/`Mix_LoadWAV` jamais vérifiés) ; `freeMusic()` ne libère qu'1 son sur 8 chargés (fuite en fin de process, sans gravité) ; mélange français/anglais dans les noms — cohérent avec l'origine ISN du projet, pas une vraie dette.
