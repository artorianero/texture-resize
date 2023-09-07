texture-resize:resize.o
	g++ build/resize.o -o bin/texture-resize -I /usr/local/include/opencv4/ -l opencv_core -l opencv_highgui -l opencv_imgproc -l opencv_imgcodecs

resize.o:src/resize.cpp
	g++ -c src/resize.cpp -o build/resize.o -I /usr/local/include/opencv4/ -l opencv_core -l opencv_highgui -l opencv_imgproc -l opencv_imgcodecs

.PHONY:clean
clean:
	-rm build/*.o bin/texture-resize
