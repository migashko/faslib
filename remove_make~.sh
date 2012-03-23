./remove~.sh
rm -f -r build
rm -f -r doc
rm -f faslib.kdevelop.pcs
find ./ -name "Makefile.in" -exec rm {} -f \;
find ./ -name "Makefile" -exec rm {} -f \;
find ./ -name "*.cmake" -exec rm {} -f \;
find ./ -name "CMakeFiles" -exec rm {} -r -f \;
find ./ -name "_CPack_Packages" -exec rm {} -r -f \;
find ./ -name "CMakeCache.txt" -exec rm {} -f \;
find ./ -name "install_manifest.txt" -exec rm {} -f \;
find ./ -name "html" -exec rm {} -r -f \;
find ./ -name "latex" -exec rm {} -r -f \;

