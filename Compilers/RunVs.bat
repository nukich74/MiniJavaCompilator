@echo off
echo Добавляем путь к GnuWin32 в PATH
set GNUWIN32=C:\GnuWin32
set PATH=%PATH%;%GNUWIN32%\bin

echo Запускаем студию (можно прописать и сам solution)
start devenv.exe Compilers.sln
rem start Compilers.sln