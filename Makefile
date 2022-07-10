f = -ggdb3 -O0 -Werror -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported 	-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor 	-Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 	-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused	-Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs  -fsized-deallocation	-fstack-protector  -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -pie -Wlarger-than=16384 -Wstack-usage=16384

all: 
	g++ $(f) main.cpp binaryTreeLib/drawTree.cpp binaryTreeLib/tree.cpp game/akinator.cpp -o exec/bebra

openDB:
	vim exec/akinator.txt

prepMain:
	g++ main.cpp  -E -o bebra.i

run: 
	./exec/bebra

runv:
	valgrind --leak-check=full --show-leak-kinds=all ./exec/bebra

dot:
	dot -Tpng -o dotDraw/out.png dotDraw/tree.dot
	display dotDraw/out.png
