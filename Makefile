BOARD_TAG = uno

# TWI library
ARDUINO_LIBS = Wire
ARDUINO_LIBS += SPI
ARDUINO_LIBS += USART

LOCAL_CPP_SRCS += $(wildcard libraries/Adafruit_GFX_Library/*.cpp)
LOCAL_CPP_SRCS += $(wildcard libraries/Adafruit_ILI9341/*.cpp)
LOCAL_CPP_SRCS += $(wildcard *.cpp)

# USER_LIB_PATH = /home/$(USER)/Arduino/libraries
# USER_LIB_PATH += $(realpath .)

include /usr/share/arduino/Arduino.mk
