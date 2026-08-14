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
- [ ] `J3-1` Décommenter et fiabiliser l'installation des dépendances Windows via vcpkg dans `build.yml`
- [ ] `J3-2` Décommenter et adapter le configure/build CMake pour Windows (toolchain vcpkg)
- [ ] `J3-3` Décommenter et adapter le packaging (7z) + upload d'artefact Windows
- [ ] `J3-4` Valider que le build Windows compile réellement en CI (itérer sur les erreurs de compilation MSVC/MinGW le cas échéant)

## ✅ Terminé

- [x] `J0-1` Audit du dépôt (`AUDIT.md`)
- [x] `J1-1` Ajouter `github-token` au step `download-artifact@v4` de `release.yml`
- [x] `J2-1` Bundling macOS : `cmake/FixupBundleMacOS.cmake` (CMake `BundleUtilities`/`fixup_bundle`), Release-only, vérifié localement (`otool -L` confirme `@executable_path/../Frameworks/...`, 114 dylibs copiées/réécrites, binaire lancé avec succès)
- [x] `J2-2` Bundling Linux : `scripts/bundle_libs_linux.sh` (copie récursive via `ldd` + rpath `patchelf`), Release-only, no-op si `patchelf` absent ; `patchelf` ajouté aux dépendances CI Linux dans `build.yml`, artefact `tar.gz` inclut désormais `lib/`

## Journal

- 2026-08-14 — `J0-1` déplacé en ✅ Terminé — audit complet du dépôt et des 4 issues GitHub ouvertes, cause racine de #16 identifiée via les logs CI publics.
- 2026-08-14 — `J1-1` déplacé en 🔵 En cours puis ✅ Terminé — ajout de `github-token: ${{ secrets.GITHUB_TOKEN }}` au step de téléchargement d'artefact dans `release.yml`.
- 2026-08-14 — `J2-1`/`J2-2` déplacés en 🔵 En cours puis ✅ Terminé — bundling SDL2 macOS (fixup_bundle) validé localement en conditions réelles ; bundling Linux (patchelf) implémenté, restreint aux builds Release pour ne pas ralentir `make run` (mesuré : +5,6s par relink Debug si non restreint). `J2-3` (smoke test CI isolé) laissé en backlog, hors périmètre réalisable dans cette session.
