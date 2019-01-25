all:
	g++ main.cpp -o hello -Iallegro/include -Lallegro/lib -lallegro -lallegro_font -lallegro_ttf -lallegro_color -lallegro_primitives -lallegro_image -lallegro_dialog
clean:
	rm -f hello.exe