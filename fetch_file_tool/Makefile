all:
	g++ fetch_file_tool.cpp -o out/fetch_file_tool
	
.PHONY:clean
clean:
	rm -rf out/* ./*.txt test_sample/dest_base test_sample/svn_base

.PHONY:prepare
prepare:
	cp -rf ./test_sample/source/dest_base ./test_sample/
	cp -rf ./test_sample/source/svn_base  ./test_sample/
