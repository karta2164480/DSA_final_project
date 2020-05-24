all:
	g++ DSA_final_project_main.cpp -o DSA_final_project

run:
	./DSA_final_project <input >ouput

clean:
	rm -rf DSA_final_project
	rm -rf ouput
