@echo off
echo -Cr�ation ressources.o
windres others\ressources.rc -o others\ressources.o
echo Ressources.o OKAY

echo -Cr�ation Mario.exe
gcc src\*.c src\menu\*.c src\game\*.c src\game\mechant\*.c src\game\joueur\*.c others\ressources.o -o Mario.exe -I include -L lib -lmingw32 -lSDLmain -lSDL -lSDL_mixer -mwindows
echo Mario.exe OKAY
pause
