COMPILER=g++
OBJS_PATH=objs
APP_PATH=.
LIB_PATH=lib


OTHERLIBS= -lm -lstdc++

APPCSRC=$(wildcard $(APP_PATH)/*.c)

APPCPPSRC=$(wildcard $(APP_PATH)/*.cpp)

APPCOBJS=$(patsubst $(APP_PATH)/%.c, $(OBJS_PATH)/%.o, $(APPCSRC))

APPCPPOBJS=$(patsubst $(APP_PATH)/%.cpp, $(OBJS_PATH)/%.o, $(APPCPPSRC))	

OBJS:=$(APPCOBJS) $(APPCPPOBJS)

INCLUDE_PATH=-I$(APP_PATH)

$(OBJS_PATH)/%.o: $(APP_PATH)/%.c  
	g++ -fPIC  -o $@  $(INCLUDE_PATH) -c $^ -g
	
$(OBJS_PATH)/%.o: $(APP_PATH)/%.cpp 
	g++ -fPIC  -o $@  $(INCLUDE_PATH) -c $^ -g

$(LIB_PATH)/libTinyXml.so:$(OBJS)
	$(COMPILER) -shared -fPIC -o $@ $(INCLUDE_PATH) $^ $(OTHERLIBS) -g

all:$(LIB_PATH)/libTinyXml2.so



clean:
	rm -f $(OBJS_PATH)/*.o
	rm -f $(LIB_PATH)/libTinyXml2.so


