CC = gcc
TARGET = encode_decode
SOURCES = encode_decode.c ../mantle.c ../mantle_crc.c

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)
	@rm $(TARGET)
