all:
	g++ DSA_final_project_main.cpp email.cpp parser.cpp trie.cpp -o run

run:
	./run < input > output

clean:
	rm -rf run
	rm -rf output
