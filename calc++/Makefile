cc=g++
all:
	cc -o calcclient++ calcclient.cpp  soapC.cpp soapcalcProxy.cpp -lgsoap++ -lm -lstdc++
	cc -o calcserver++ calcserver.cpp soapC.cpp soapcalcService.cpp -lgsoap++ -lm -lstdc++

clean:
	rm -f calclient++ calcserver++

