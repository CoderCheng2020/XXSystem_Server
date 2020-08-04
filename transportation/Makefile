COMPILER=g++
OBJS_PATH=objs
APP_PATH=.
LIB_PATH=lib
TEST_CPP=test_cpp/calcserver.cpp

OTHERLIBS= -lm -lstdc++

APPCSRC=$(wildcard $(APP_PATH)/*.c)

APPCPPSRC=$(wildcard $(APP_PATH)/*.cpp)

APPCOBJS=$(patsubst $(APP_PATH)/%.c, $(OBJS_PATH)/%.o, $(APPCSRC))

APPCPPOBJS=$(patsubst $(APP_PATH)/%.cpp, $(OBJS_PATH)/%.o, $(APPCPPSRC))	

OBJS:=$(APPCOBJS) $(APPCPPOBJS)

INCLUDE_PATH=-I$(APP_PATH)

$(OBJS_PATH)/%.o: $(APP_PATH)/%.c  
	g++ -fPIC  -o $@  $(INCLUDE_PATH) -c $^
	
$(OBJS_PATH)/%.o: $(APP_PATH)/%.cpp 
	g++ -fPIC  -o $@  $(INCLUDE_PATH) -c $^

$(LIB_PATH)/libWSServer.so:$(OBJS)
	$(COMPILER) -shared -fPIC -o $@ $(INCLUDE_PATH) $^ $(OTHERLIBS)

all:$(LIB_PATH)/WSServer.so

test_server:
	$(COMPILER) -o calcserver++ $(TEST_CPP) soapC.cpp soapcalcService.cpp stdsoap2.cpp $(OTHERLIBS)

clean:
	rm -f $(OBJS_PATH)/*.o
	rm -f calcserver++
	rm -f $(LIB_PATH)/libWSServer.so


