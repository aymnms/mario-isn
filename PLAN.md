# Plan — mario-isn

> Ce fichier est la seule source de vérité de l'avancement. Il doit refléter la réalité à tout moment. Commit à chaque mise à jour.

## Raisonnement du découpage

Les jalons suivent directement les 4 issues GitHub ouvertes, dans l'ordre de dépendance et d'effort identifié en `AUDIT.md` §7. J1 (fix release) est traité en premier car il bloque toute distribution du projet et est de faible effort/risque isolé (un seul paramètre CI, cf. AUDIT.md §4-5). J2 (bundling des libs) est ensuite nécessaire pour qu'une release distribuée soit réellement utilisable (AUDIT.md §4, #15). J3 (Windows) est traité en dernier car c'est le chantier le plus large (nouveau job CI jamais validé, cf. AUDIT.md §3) et le moins bloquant dans l'immédiat (aucune régression actuelle, juste une plateforme absente).

## Jalons

- **J1** — Fix pipeline de release — corriger le téléchargement d'artefact dans `release.yml` pour que `semantic-release` publie enfin une release (#16).
- **J2** — Bundler les libs SDL2 — embarquer SDL2/SDL2_image/SDL2_mixer dans les artefacts macOS et Linux pour une exécution sans dépendances système (#15).
- **J3** — Build et CI Windows — réactiver le job Windows de `build.yml` (vcpkg + build + packaging) (#8, #9).
- **J4** — Build macOS Intel via Rosetta — demande explicite de l'utilisateur (hors des 4 issues initiales), sur le modèle d'une recette déjà validée sur un autre de ses projets (PyInstaller/Python) : cross-compilation `clang -arch x86_64` depuis le runner Apple Silicon `macos-latest` (pas de runner Intel natif fiable disponible), avec un second Homebrew x86_64 sous Rosetta pour les libs SDL2.
- **J5** — Fiabilisation et dette technique post-v1.2.0 — les 4 issues initiales sont livrées (release v1.2.0) ; ce jalon reprend les points laissés en dette dans `AUDIT.md` §6-7 et la Roadmap du README, phasés par risque/effort :
  - **Phase 1 (fiabiliser ce qui est livré)** : smoke test CI isolé validant le bundling Linux en conditions réelles (`J2-3`), cache vcpkg pour ne pas recompiler SDL2 à chaque run Windows (`J3-6`).
  - **Phase 2 (hygiène rapide, effort faible)** : supprimer la console Windows superflue (`J3-5`), `clang-format`/`.editorconfig` (AUDIT §7 reco #4).
  - **Phase 3 (dette technique de fond, effort élevé)** : extraire un noyau de logique de jeu découplé de SDL, prérequis bloquant pour tout test unitaire (AUDIT §7 reco #5).

## 🔵 En cours

- [ ] `J2-3` Ajouter un smoke test CI isolé (conteneur Linux sans SDL2 installé, Xvfb) validant que l'artefact packagé démarre sans les libs système — en cours sur `feat/ci-linux-smoke-test`

## ⬜ À faire

- [ ] Fermer manuellement les issues #16, #15, #8, #9 sur GitHub — corrigées et vérifiées (release v1.2.0), mais aucun token disponible dans cette session pour les clore via l'API

### J5 — Phase 2 (hygiène rapide)

- [ ] `J5-1` `clang-format`/`.editorconfig` pour un style C homogène (AUDIT §7 reco #4)

### J5 — Phase 3 (dette technique de fond)

- [ ] `J5-2` Extraire un noyau de logique de jeu (déplacement, collisions, IA ennemis) découplé de SDL, dans un module dédié (`domain/`) — prérequis bloquant pour tout test unitaire (AUDIT §7 reco #5)

## ✅ Terminé

- [x] `J0-1` Audit du dépôt (`AUDIT.md`)
- [x] `J1-1` Ajouter `github-token` au step `download-artifact@v4` de `release.yml`
- [x] `J2-1` Bundling macOS : `cmake/FixupBundleMacOS.cmake` (CMake `BundleUtilities`/`fixup_bundle`), Release-only, vérifié localement et en CI (`otool -L` confirme `@executable_path/../Frameworks/...`, 114 dylibs copiées/réécrites, binaire lancé avec succès)
- [x] `J2-2` Bundling Linux : `scripts/bundle_libs_linux.sh` (copie récursive via `ldd` + rpath `patchelf`), Release-only, no-op si `patchelf` absent ; vérifié en CI après correction d'un piège `pipefail`/`grep`
- [x] `J3-1` Job Windows dans `build.yml` : installation SDL2/SDL2_image/SDL2_mixer via vcpkg (triplet `x64-windows`), vérifié en CI (~2 min d'install)
- [x] `J3-2` Configure/build CMake Windows : générateur Visual Studio auto-détecté (pas de version figée, pour survivre aux mises à niveau d'image runner) + toolchain vcpkg + link `SDL2::SDL2main`, vérifié en CI (19 fichiers compilés, link réussi)
- [x] `J3-3` Packaging (7z, tout le dossier `Release/` — exe + DLLs déployées automatiquement par `VCPKG_APPLOCAL_DEPS` + assets) et upload d'artefact Windows ; `windows-latest` ajouté à la matrice ; workflow renommé `Build MarioISN` (et `release.yml` mis à jour en conséquence pour rester déclenché) ; vérifié en CI
- [x] `J3-4` Valider que le build Windows compile réellement en CI — 3 runs, 2 bugs réels trouvés et corrigés à partir des logs collés par l'utilisateur (générateur CMake figé sur une version de VS absente du runner ; `SDL2::SDL2main` manquant). Run 3 (31819979158) : **macOS ✅ / Linux ✅ / Windows ✅**, les 3 OS buildent et publient leur artefact pour la première fois.
- [x] `J4-1` Build macOS Intel via Rosetta : `make prod-intel` (cross-compile `clang -arch x86_64`, `SDL2_DIR`/`SDL2_image_DIR`/`SDL2_mixer_DIR` pointés explicitement vers le second Homebrew x86_64 sous Rosetta à `/usr/local`), job CI ajouté (`build.yml`), asset ajouté (`.releaserc.json`). Vérifié en CI dès le premier run (31821880623) : **macOS ARM ✅ / macOS Intel ✅ / Linux ✅ / Windows ✅** — les 4 cibles buildent et publient leur artefact avec succès.
- [x] `J3-6` Cache `actions/cache` du binary cache vcpkg (`~/AppData/Local/vcpkg/archives`, clé `run_id` + restore-keys en préfixe). Vérifié en CI : les 3 OS buildent toujours (run 31827750421). Mergé dans `main`.
- [x] `J3-5` Subsystem `WIN32` sur la cible CMake pour supprimer la console Windows superflue. Vérifié en CI : les 3 OS buildent toujours (run 31827885237). Mergé dans `main`.

## Journal

- 2026-08-14 — `J0-1` déplacé en ✅ Terminé — audit complet du dépôt et des 4 issues GitHub ouvertes, cause racine de #16 identifiée via les logs CI publics.
- 2026-08-14 — `J1-1` déplacé en 🔵 En cours puis ✅ Terminé — ajout de `github-token: ${{ secrets.GITHUB_TOKEN }}` au step de téléchargement d'artefact dans `release.yml`.
- 2026-08-14 — `J2-1`/`J2-2` déplacés en 🔵 En cours puis ✅ Terminé — bundling SDL2 macOS (fixup_bundle) validé localement en conditions réelles ; bundling Linux (patchelf) implémenté, restreint aux builds Release pour ne pas ralentir `make run` (mesuré : +5,6s par relink Debug si non restreint). `J2-3` (smoke test CI isolé) laissé en backlog, hors périmètre réalisable dans cette session.
- 2026-08-14 — `J3-1`/`J3-2`/`J3-3` déplacés en 🔵 En cours puis ✅ Terminé (implémentation) — job Windows vcpkg + build.yml élargi à `windows-latest`.
- 2026-08-14 — CI ouverte à toutes les branches (`build.yml` sans filtre de branche) à la demande de l'utilisateur, pour pouvoir tester le job Windows sans passer par une PR.
- 2026-08-14 — Run CI 1 (31808483132) : Linux et Windows échouent, macOS ✅. Logs collés par l'utilisateur → diagnostic : Linux, piège `pipefail`+`grep` sans match dans `bundle_libs_linux.sh` (le build avait pourtant réussi) ; Windows, générateur CMake figé `"Visual Studio 17 2022"` introuvable sur le runner `windows-2025-vs2026` (VS2026 installé). Les deux corrigés et repoussés.
- 2026-08-14 — Run CI 2 (31819481890) : Linux ✅ et macOS ✅ définitivement verts. Windows échoue encore, mais plus loin (vcpkg + compilation OK) : `LNK2019: unresolved external symbol main`, causé par `SDL.h` qui redéfinit `main` en `SDL_main` sur Windows sans `SDL2::SDL2main` lié. Corrigé et repoussé.
- 2026-08-14 — Run CI 3 (31819979158) : **macOS ✅ / Linux ✅ / Windows ✅** — `J3-4` déplacé en ✅ Terminé. Les 4 issues GitHub (#16, #15, #8, #9) ont désormais une implémentation vérifiée en CI réelle, sur 3 branches distinctes prêtes à être revues/mergées.
- 2026-08-14 — Demande utilisateur hors périmètre initial : build macOS Intel, sur le modèle d'une recette déjà validée sur un autre projet (Python/PyInstaller + Rosetta), adaptée au C/CMake. Nouvelle branche `feat/macos-intel-build`, `J4` ajouté au plan.
- 2026-08-14 — L'utilisateur colle les logs d'un run `release.yml` sur `main` (indépendant de ce chantier) qui échoue pour deux raisons : (1) `main` n'a pas encore le fix `github-token`/`merge-multiple` de `fix/release-artifact-download` (normal, pas mergé) ; (2) bug réel et nouveau — `semantic-release` exige Node ≥22.14, `release.yml` était figé sur Node 20. Fix Node 22 ajouté sur `fix/release-artifact-download` et propagé par merge successif sur les 3 autres branches.
- 2026-08-14 — Run CI (31821880623) sur `feat/macos-intel-build` : **macOS ARM ✅ / macOS Intel ✅ / Linux ✅ / Windows ✅** dès la première tentative — `J4-1` déplacé en ✅ Terminé. Les 4 branches sont maintenant à jour du fix Node 22 et prêtes à être revues/mergées vers `main`.
- 2026-08-14 — Stratégie de merge : les 4 branches étant empilées séquentiellement (chacune contient la précédente), `main` (non divergé) est fast-forward directement vers `feat/macos-intel-build` en un seul push, pour n'avoir qu'un seul cycle build→release plutôt que 4 en cascade. Les 4 branches sont supprimées (local + remote) une fois mergées. Release **v1.2.0** publiée avec succès, 4 artefacts attachés — les issues #16, #15, #8, #9 sont résolues (fermeture manuelle sur GitHub à faire par l'utilisateur, pas de token disponible pour le faire depuis cette session).
- 2026-08-14 — Suite à la demande de l'utilisateur : réécriture complète du `README.md` (gabarit du skill), restriction du déclencheur `release.yml` à `head_branch == 'main'` uniquement (évite des runs `Release` inutiles sur les autres branches), puis restriction de `build.yml` à ne se déclencher que sur des changements de chemins pertinents pour le build (`src/`, `include/`, `ressources/`, `cmake/`, `scripts/`, `CMakeLists.txt`, `Makefile`, le workflow lui-même) — un commit `docs:`/`ci:` seul (README, PLAN, config release) ne lance plus toute la matrice 4 OS. Vérifié en CI : les commits `docs:`/`ci:` de cette étape n'ont déclenché ni build inutile après le filtre, ni nouvelle release (toujours v1.2.0).
- 2026-08-14 — `J5` ajouté au plan à la demande de l'utilisateur (roadmap post-v1.2.0), phasé en 3 sous-groupes par risque/effort à partir de `AUDIT.md` §7 et de la Roadmap du README. `J2-3`/`J3-5`/`J3-6` reclassés sous `J5` (Phases 1/2), `J5-1`/`J5-2` ajoutés (Phases 2/3) pour couvrir les recommandations #4/#5 de l'audit, jusque-là non trackées comme tâches.
- 2026-08-14 — 4 tâches Phase 1/2 de `J5` lancées en parallèle sur des branches dédiées, chacune vérifiée par un run CI complet avant merge : `J3-6` (cache vcpkg) et `J3-5` (subsystem Windows) verts sur les 3 OS, mergés dans `main` (conflit `PLAN.md` résolu manuellement). `J5-1` (clang-format) vert sur les 3 OS, formatage appliqué à `src/`/`include/`, vérifié en local (`make run` compile et le jeu tourne) avant merge. `J2-3` (smoke test Linux isolé) encore en cours de vérification CI au moment du merge des trois autres.
