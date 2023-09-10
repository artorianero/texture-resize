texture-resize:resize.o
	# dynamic
	# g++ build/resize.o -o bin/texture-resize -I /usr/local/include/opencv4/ -l opencv_core -l opencv_highgui -l opencv_imgproc -l opencv_imgcodecs
	# static
	g++ build/resize.o -o bin/texture-resize -I /usr/local/include/opencv4/ -L /usr/local/lib/opencv4/3rdparty -static -l opencv_imgcodecs -l opencv_imgproc -l opencv_core -l IlmImf -l ittnotify -l libopenjp2 -l png16 -l tiff -l stdc++ -l m -l gcc -l c -l z -l jpeg -l webp -l zstd -l lzma -l Lerc -l jbig -l deflate

resize.o:src/resize.cpp
	g++ -c src/resize.cpp -o build/resize.o -I /usr/local/include/opencv4/

.PHONY:clean
clean:
	-rm build/*.o bin/*
