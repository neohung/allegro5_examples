all:
	g++ main.cpp -o hello -Iallegro/include -Lallegro/lib -lallegro -lallegro_font -lallegro_ttf -lallegro_color -lallegro_primitives
clean:
	rm -f hello.exe