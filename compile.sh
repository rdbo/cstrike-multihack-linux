if [ ! -d /tmp/libcshack ]; then
    mkdir /tmp/libcshack
fi

gcc -g -m32 -shared -fPIC $(find ./src -type f -name "*.c") -o /tmp/libcshack/libcshack.so -Wall -Wpedantic -Wextra
