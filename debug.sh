target_process="hl_linux"
target_pid=""
libpath="/tmp/libcshack/libcshack.so"

if [ "$EUID" -ne 0 ]; then
    echo "[!] Run as root"
    exit 0
fi

if [ ! command -v gdb &> /dev/null ]; then
    echo "[!] Unable to find GDB, make sure you have it installed"
    exit 0
fi

if ! target_pid=$(pgrep $target_process) > /dev/null 2>&1; then
    echo "[!] The target process is not running"
    exit 0
fi

if [ ! -f $libpath ]; then
    echo "[!] Invalid shared library file"
    exit 0
fi

gdb \
  -ex "attach $target_pid" \
  -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
  -ex "call \$dlopen(\"$libpath\", 1)"

echo "[*] done"
