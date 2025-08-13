#!/bin/bash

# Vérification d'argument
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 {build|run}"
    exit 1
fi

case "$1" in
    build)
        echo "📦 Compilation du projet..."
        cmake -S . -B build -G Ninja
        cmake --build build
        ;;
    run)
        echo "🚀 Lancement du projet..."
        # MAUVAIS COMPORTEMENT
        # NORMALEMENT PAS BESOIN D'ÊTRE DANS DOSSIER POUR EXECUTER
        if [ -f build/mario_isn.app/Contents/MacOS/mario_isn ]; then
            cd build/mario_isn.app/Contents/MacOS/
            ./mario_isn
            cd ../../../../
        else
            echo "Erreur: le projet n'est pas compilé. Lancez '$0 build' d'abord."
            exit 1
        fi
        ;;
    *)
        echo "Argument invalide: $1"
        echo "Usage: $0 {build|run}"
        exit 1
        ;;
esac