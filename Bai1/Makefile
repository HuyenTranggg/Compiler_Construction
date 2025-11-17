CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = indexer
SRC = indexer.c

# File mặc định
INPUT ?= alice30.txt
OUTPUT ?= output.txt

# Biên dịch chương trình
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Chạy chương trình
run: $(TARGET)
	./$(TARGET) $(INPUT) $(OUTPUT)

# Dọn dẹp
clean:
	rm -f $(TARGET) $(TARGET).exe *.o || del /Q $(TARGET).exe *.o 2>nul || echo Cleaned

.PHONY: all run clean
