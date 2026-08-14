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

- [ ] `J2-1` Ajouter la copie + réécriture des chemins de libs dynamiques SDL2 pour le bundle macOS (`install_name_tool`/`otool`)
- [ ] `J2-2` Ajouter la copie + `patchelf`/rpath relatif pour le build Linux
- [ ] `J2-3` Vérifier en CI que l'artefact packagé démarre sans les libs système (job de smoke test dans un environnement sans SDL2 préinstallé)
- [ ] `J3-1` Décommenter et fiabiliser l'installation des dépendances Windows via vcpkg dans `build.yml`
- [ ] `J3-2` Décommenter et adapter le configure/build CMake pour Windows (toolchain vcpkg)
- [ ] `J3-3` Décommenter et adapter le packaging (7z) + upload d'artefact Windows
- [ ] `J3-4` Valider que le build Windows compile réellement en CI (itérer sur les erreurs de compilation MSVC/MinGW le cas échéant)

## ✅ Terminé

- [x] `J0-1` Audit du dépôt (`AUDIT.md`)
- [x] `J1-1` Ajouter `github-token` au step `download-artifact@v4` de `release.yml`

## Journal

- 2026-08-14 — `J0-1` déplacé en ✅ Terminé — audit complet du dépôt et des 4 issues GitHub ouvertes, cause racine de #16 identifiée via les logs CI publics.
- 2026-08-14 — `J1-1` déplacé en 🔵 En cours puis ✅ Terminé — ajout de `github-token: ${{ secrets.GITHUB_TOKEN }}` au step de téléchargement d'artefact dans `release.yml`.
