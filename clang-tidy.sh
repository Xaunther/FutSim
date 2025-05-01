# Runs clang-tidy over all source files
find . \( -name "*.h" -o -name "*.cpp" \) -a \( -path "./src/*" -o -path "./include/*" -o -path "./tests/*" \) |
	xargs clang-tidy --config-file=.clang-tidy -p build
