@echo off

mkdir ..\..\build\fg
pushd ..\..\build\fg
cl -FC -Zi -EHsc ..\..\fg\src\main.cpp User32.lib Gdi32.lib

popd