#!/bin/bash

# Smart Hotel Management System - Build Script
# Supports Linux, macOS, and Windows (Git Bash/WSL)

echo "╔════════════════════════════════════════════════════╗"
echo "║  Smart Hotel Management System - Build Script       ║"
echo "║  Northern Heights Hotel & Resort                    ║"
echo "╚════════════════════════════════════════════════════╝"
echo ""

# Check if C++ compiler is available
if ! command -v g++ &> /dev/null; then
    echo "❌ Error: g++ compiler not found!"
    echo "Please install GCC compiler:"
    echo "  - Ubuntu/Debian: sudo apt-get install build-essential"
    echo "  - macOS: brew install gcc"
    echo "  - Windows: Install MinGW or use WSL"
    exit 1
fi

echo "✓ Found g++ compiler"
echo ""

# Display compiler version
echo "Compiler Version:"
g++ --version | head -1
echo ""

# Create bin directory if it doesn't exist
if [ ! -d "bin" ]; then
    mkdir bin
    echo "✓ Created 'bin' directory"
fi

# Compile all source files
echo "Compiling source files..."
echo "========================="

SOURCE_FILES="main.cpp Person.cpp Guest.cpp Employee.cpp Room.cpp Service.cpp Booking.cpp Bill.cpp Hotel.cpp"
COMPILE_FAILED=false

for file in $SOURCE_FILES; do
    if [ -f "$file" ]; then
        echo -n "  Compiling $file... "
        if g++ -std=c++11 -c "$file" -o "bin/${file%.cpp}.o" 2>/dev/null; then
            echo "✓"
        else
            echo "✗"
            COMPILE_FAILED=true
        fi
    else
        echo "  ✗ File $file not found!"
        COMPILE_FAILED=true
    fi
done

echo ""

# Check if compilation was successful
if [ "$COMPILE_FAILED" = true ]; then
    echo "❌ Compilation failed! Please check the errors above."
    exit 1
fi

# Link object files
echo "Linking object files..."
echo "======================"

OBJECT_FILES="bin/*.o"
if g++ $OBJECT_FILES -o bin/hotel_system 2>/dev/null; then
    echo "✓ Linking successful"
else
    echo "✗ Linking failed!"
    exit 1
fi

echo ""
echo "╔════════════════════════════════════════════════════╗"
echo "║  ✓ BUILD SUCCESSFUL!                              ║"
echo "╚════════════════════════════════════════════════════╝"
echo ""
echo "To run the application:"
echo "  ./bin/hotel_system"
echo ""
echo "To clean build files:"
echo "  rm -rf bin/*.o"
echo "  rm bin/hotel_system"
echo ""
