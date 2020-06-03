all:
	g++ DSA_final_project_main.cpp email.cpp parser.cpp trie.cpp -o run

run:
	./run <input >ouput

clean:
	rm -rf run
	rm -rf ouput
