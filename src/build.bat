@echo off

mkdir ..\..\build\fg
pushd ..\..\build\fg
cl -FC -Zi -EHsc -MDd ..\..\fg\src\main.cpp -I ../../_tools/SFML-2.3/include^
 -link User32.lib Gdi32.lib^
 -LIBPATH:../../_tools/SFML-2.3/lib winmm.lib sfml-system-d.lib opengl32.lib gdi32.lib sfml-window-d.lib freetype.lib jpeg.lib sfml-graphics-d.lib

popd