all:
	g++ DSA_final_project_main.cpp -o run

run:
	./run <input >ouput

clean:
	rm -rf run
	rm -rf ouput
