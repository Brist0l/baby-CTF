baby_1:
	gcc src/baby_1.c src/cpu.c src/cpu.h src/helper.c src/helper.h -g -o baby_1
baby_2:
	gcc src/baby_2.c src/cpu.c src/cpu.h src/helper.c src/helper.h -g -o baby_2
clean:
	rm baby_1
	rm baby_2
