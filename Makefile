build:
	g++ -I/opt/homebrew/include/ -I/opt/homebrew/include/opencv4/ -L/opt/homebrew/lib/ -ljsoncpp -L/opt/homebrew/Cellar/opencv/4.8.0/lib -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_core -lopencv_highgui main.cpp -o main.o -std=c++17

clean:
	rm main.o
