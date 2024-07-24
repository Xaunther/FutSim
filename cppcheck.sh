# Runs cppcheck over all source files
find . \( -name "*.h" -o -name "*.cpp" \) -a \( -path "./src/*" -o -path "./include/*" -o -path "./tests/*" \) |
	cppcheck --language=c++ --file-list=- -I include -I src -I tests --enable=performance,portability,warning,style --suppress=internalAstError --suppress=unusedStructMember