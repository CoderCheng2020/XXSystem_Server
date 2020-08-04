COMPILER=g++
OBJS_PATH=objs
APP_PATH=.
LIB_PATH=lib
BIN_PATH=bin
INCLUDE_PATH=include
TRANSPORTATIONLIB_PATH=transportation
TINYXML_PATH=tinyXml

COMPILE_PARAM= -std=c++11 -g

OTHERLIBS= -lm -lstdc++  -lpthread -lmysqlclient -lTinyXml

APPCSRC=$(wildcard $(APP_PATH)/*.c)

APPCPPSRC=$(wildcard $(APP_PATH)/*.cpp)

APPCOBJS=$(patsubst $(APP_PATH)/%.c, $(OBJS_PATH)/%.o, $(APPCSRC))

APPCPPOBJS=$(patsubst $(APP_PATH)/%.cpp, $(OBJS_PATH)/%.o, $(APPCPPSRC))	

OBJS:=$(APPCOBJS) $(APPCPPOBJS)

INCLUDE_PATH=-I$(APP_PATH) -I../include -I$(APP_PATH)/$(TINYXML_PATH)



	
$(OBJS_PATH)/%.o: $(APP_PATH)/%.c  
	g++ -fPIC  -o $@  $(INCLUDE_PATH) -c $^ $(COMPILE_PARAM)
	
$(OBJS_PATH)/%.o: $(APP_PATH)/%.cpp 
	g++ -fPIC  -o $@  $(INCLUDE_PATH) -c $^ $(COMPILE_PARAM)




	
	




make_tinyXml:
	make -C tinyXml



all:make_tinyXml $(BIN_PATH)/XX_Server


$(BIN_PATH)/XX_Server:$(OBJS)
	g++ -o $@ $(INCLUDE_PATH) $^ -L $(TINYXML_PATH)/$(LIB_PATH) -Wl,-rpath=src/$(TINYXML_PATH)/$(LIB_PATH) $(OTHERLIBS) $(COMPILE_PARAM)





	
clean:
	make clean -C tinyXml
	rm -f $(OBJS_PATH)/*.o
	rm -f $(BIN_PATH)/*




