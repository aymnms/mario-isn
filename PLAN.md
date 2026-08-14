# Plan — mario-isn

> Ce fichier est la seule source de vérité de l'avancement. Il doit refléter la réalité à tout moment. Commit à chaque mise à jour.

## Raisonnement du découpage

Les jalons suivent directement les 4 issues GitHub ouvertes, dans l'ordre de dépendance et d'effort identifié en `AUDIT.md` §7. J1 (fix release) est traité en premier car il bloque toute distribution du projet et est de faible effort/risque isolé (un seul paramètre CI, cf. AUDIT.md §4-5). J2 (bundling des libs) est ensuite nécessaire pour qu'une release distribuée soit réellement utilisable (AUDIT.md §4, #15). J3 (Windows) est traité en dernier car c'est le chantier le plus large (nouveau job CI jamais validé, cf. AUDIT.md §3) et le moins bloquant dans l'immédiat (aucune régression actuelle, juste une plateforme absente).

## Jalons

- **J1** — Fix pipeline de release — corriger le téléchargement d'artefact dans `release.yml` pour que `semantic-release` publie enfin une release (#16).
- **J2** — Bundler les libs SDL2 — embarquer SDL2/SDL2_image/SDL2_mixer dans les artefacts macOS et Linux pour une exécution sans dépendances système (#15).
- **J3** — Build et CI Windows — réactiver le job Windows de `build.yml` (vcpkg + build + packaging) (#8, #9).

## 🔵 En cours

_(vide)_

## ⬜ À faire

- [ ] `J2-3` Ajouter un smoke test CI isolé (conteneur Linux sans SDL2 installé, Xvfb) validant que l'artefact packagé démarre sans les libs système — non fait dans cette session : nécessite d'itérer sur de vrais runs GitHub Actions (dlopen de libs X11/ALSA côté SDL2 à vérifier en conditions réelles), risque de flakiness à gérer avec plus de cycles CI que ce tour n'en permettait
- [ ] `J3-4` Valider que le build Windows compile réellement en CI — 3 runs jusqu'ici :
  - Run 1 (31808483132) : Linux et Windows échouent, macOS ✅.
  - Run 2 (31819481890) après fix générateur/pipefail : Linux ✅ et macOS ✅ (les deux définitivement verts), Windows échoue toujours mais **plus loin** — vcpkg installe SDL2/SDL2_image/SDL2_mixer, CMake détecte auto "Visual Studio 18 2026", les 19 fichiers `.c` compilent, mais le link échoue : `LNK2019: unresolved external symbol main`. Cause : `SDL.h` `#define main SDL_main` sur Windows ; il fallait lier `SDL2::SDL2main` (absent de `CMakeLists.txt`). Corrigé avec `$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>` (no-op sur macOS/Linux où la cible n'existe pas).
  - Run 3 : à surveiller.
- [ ] `J3-5` (optionnel, hors scope #8/#9) : lier `SDL2::SDL2main` + passer en subsystem `WINDOWS` pour supprimer la fenêtre console qui s'ouvre à côté du jeu sur Windows
- [ ] `J3-6` (optionnel) : cache `actions/cache` pour l'arbre vcpkg installé, le run Windows compile SDL2/SDL2_image/SDL2_mixer depuis les sources à chaque fois (~15-30 min sans cache)

## ✅ Terminé

- [x] `J0-1` Audit du dépôt (`AUDIT.md`)
- [x] `J1-1` Ajouter `github-token` au step `download-artifact@v4` de `release.yml`
- [x] `J2-1` Bundling macOS : `cmake/FixupBundleMacOS.cmake` (CMake `BundleUtilities`/`fixup_bundle`), Release-only, vérifié localement (`otool -L` confirme `@executable_path/../Frameworks/...`, 114 dylibs copiées/réécrites, binaire lancé avec succès)
- [x] `J2-2` Bundling Linux : `scripts/bundle_libs_linux.sh` (copie récursive via `ldd` + rpath `patchelf`), Release-only, no-op si `patchelf` absent ; `patchelf` ajouté aux dépendances CI Linux dans `build.yml`, artefact `tar.gz` inclut désormais `lib/`
- [x] `J3-1` Job Windows dans `build.yml` : installation SDL2/SDL2_image/SDL2_mixer via vcpkg (triplet `x64-windows`)
- [x] `J3-2` Configure/build CMake Windows : générateur Visual Studio 17 2022 (déjà présent sur `windows-latest`, évite d'installer Ninja) + toolchain vcpkg
- [x] `J3-3` Packaging (7z, tout le dossier `Release/` — exe + DLLs déployées automatiquement par `VCPKG_APPLOCAL_DEPS` + assets) et upload d'artefact Windows ; `windows-latest` ajouté à la matrice ; workflow renommé `Build MarioISN` (et `release.yml` mis à jour en conséquence pour rester déclenché)

## Journal

- 2026-08-14 — `J0-1` déplacé en ✅ Terminé — audit complet du dépôt et des 4 issues GitHub ouvertes, cause racine de #16 identifiée via les logs CI publics.
- 2026-08-14 — `J1-1` déplacé en 🔵 En cours puis ✅ Terminé — ajout de `github-token: ${{ secrets.GITHUB_TOKEN }}` au step de téléchargement d'artefact dans `release.yml`.
- 2026-08-14 — `J2-1`/`J2-2` déplacés en 🔵 En cours puis ✅ Terminé — bundling SDL2 macOS (fixup_bundle) validé localement en conditions réelles ; bundling Linux (patchelf) implémenté, restreint aux builds Release pour ne pas ralentir `make run` (mesuré : +5,6s par relink Debug si non restreint). `J2-3` (smoke test CI isolé) laissé en backlog, hors périmètre réalisable dans cette session.
- 2026-08-14 — `J3-1`/`J3-2`/`J3-3` déplacés en 🔵 En cours puis ✅ Terminé (implémentation) — job Windows vcpkg + Visual Studio generator ajouté à `build.yml`, `windows-latest` réactivé dans la matrice, `release.yml`/`.releaserc.json` mis à jour pour inclure l'artefact Windows. `J3-4` (validation réelle en CI) reste ouvert : aucune machine Windows locale ni accès aux logs CI détaillés (API anonyme) — l'utilisateur fournira les logs du run `windows-latest` en cas d'échec pour itérer.
