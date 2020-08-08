if [ ! -d /tmp/libcshack ]; then
    mkdir /tmp/libcshack
fi

clang -g -m32 -shared -fPIC $(find -type f -name "*.c") -o /tmp/libcshack/libcshack.so
