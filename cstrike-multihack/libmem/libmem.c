//Made by rdbo
//https://github.com/rdbo/libmem
//C-compatible version of https://github.com/rdbo/Memory

#include "libmem.h"
#if defined(MEM_COMPATIBLE)
const mem_byte_t MEM_JMP[]        = ASM_GENERATE(_MEM_JMP);
const mem_byte_t MEM_JMP_RAX[]    = ASM_GENERATE(_MEM_JMP_RAX);
const mem_byte_t MEM_JMP_EAX[]    = ASM_GENERATE(_MEM_JMP_EAX);
const mem_byte_t MEM_CALL[]       = ASM_GENERATE(_MEM_CALL);
const mem_byte_t MEM_CALL_EAX[]   = ASM_GENERATE(_MEM_CALL_EAX);
const mem_byte_t MEM_CALL_RAX[]   = ASM_GENERATE(_MEM_CALL_RAX);
const mem_byte_t MEM_MOVABS_RAX[] = ASM_GENERATE(_MEM_MOVABS_RAX);
const mem_byte_t MEM_MOV_EAX[]    = ASM_GENERATE(_MEM_MOV_EAX);
const mem_byte_t MEM_PUSH[]       = ASM_GENERATE(_MEM_PUSH);
const mem_byte_t MEM_PUSH_RAX[]   = ASM_GENERATE(_MEM_PUSH_RAX);
const mem_byte_t MEM_PUSH_EAX[]   = ASM_GENERATE(_MEM_PUSH_EAX);
const mem_byte_t MEM_RET[]        = ASM_GENERATE(_MEM_RET);
const mem_byte_t MEM_BYTE[]       = ASM_GENERATE(_MEM_BYTE);
const mem_byte_t MEM_WORD[]       = ASM_GENERATE(_MEM_WORD);
const mem_byte_t MEM_DWORD[]      = ASM_GENERATE(_MEM_DWORD);
const mem_byte_t MEM_QWORD[]      = ASM_GENERATE(_MEM_QWORD);
#if defined(MEM_86)
const mem_byte_t MEM_MOV_REGAX[]  = ASM_GENERATE(_MEM_MOV_EAX);
#elif defined(MEM_64)
const mem_byte_t MEM_MOV_REGAX[]  = ASM_GENERATE(_MEM_MOVABS_RAX);
#endif

//mem_string_t
struct _mem_string_t mem_string_init()
{
    struct _mem_string_t _string;
    mem_size_t _size = sizeof(MEM_STR(""));
    _string.buffer         = (mem_char_t*)malloc(_size);
    _string.npos           = (mem_size_t)-1;
    memset(_string.buffer, '\0', _size);
    _string.clear          = &mem_string_clear;
    _string.empty          = &mem_string_empty;
    _string.size           = &mem_string_size;
    _string.resize         = &mem_string_resize;
    _string.length         = &mem_string_length;
    _string.begin          = &mem_string_begin;
    _string.end            = &mem_string_end;
    _string.find           = &mem_string_find;
    _string.rfind          = &mem_string_rfind;
    _string.at             = &mem_string_at;
    _string.c_set          = &mem_string_c_set;
    _string.value          = &mem_string_value;
    _string.c_str          = &mem_string_c_str;
    _string.substr         = &mem_string_substr;
    _string.compare        = &mem_string_compare;
    _string.is_initialized = mem_true;
    return _string;
}

struct _mem_string_t mem_string_new(const mem_char_t* c_string)
{
    struct _mem_string_t _str = mem_string_init();
    _str.buffer = (mem_char_t*)c_string;
    return _str;
}

mem_void_t mem_string_clear(struct _mem_string_t* p_string)
{
    if(p_string->is_initialized == mem_false) return;
    memset((void*)p_string->buffer, (int)0x0, (size_t)mem_string_size(p_string));
}

mem_void_t mem_string_empty(struct _mem_string_t* p_string)
{
    free(p_string->buffer);
    *p_string = mem_string_init();
}

mem_size_t mem_string_size(struct _mem_string_t* p_string)
{
    mem_size_t ret = (mem_size_t)MEM_BAD_RETURN;
    if(p_string->is_initialized)
    {
        ret = (mem_size_t)((mem_uintptr_t)mem_string_end(p_string) - (mem_uintptr_t)mem_string_begin(p_string));
    }

    return ret;
}

mem_void_t mem_string_resize(struct _mem_string_t* p_string, mem_size_t size)
{
    if(p_string->is_initialized != mem_true) return;
    size = size * sizeof(mem_char_t) + 1;
    mem_char_t* _buffer = (mem_char_t*)malloc(size);
    mem_size_t old_size = mem_string_size(p_string);
    memcpy((void*)_buffer, (void*)p_string->buffer, (size_t)(size > old_size ? old_size : size));
    _buffer[size - 1] = MEM_STR('\0');
    free(p_string->buffer);
    p_string->buffer = _buffer;
}

mem_size_t mem_string_length(struct _mem_string_t* p_string)
{
    return (p_string->is_initialized == mem_true ? MEM_STR_LEN(p_string->buffer) : MEM_BAD_RETURN);
}

mem_char_t* mem_string_begin(struct _mem_string_t* p_string)
{
    return (mem_char_t*)p_string->buffer;
}

mem_char_t* mem_string_end(struct _mem_string_t* p_string)
{
    return (mem_char_t*)((mem_uintptr_t)p_string->buffer + mem_string_length(p_string));
}

mem_size_t mem_string_find(struct _mem_string_t* p_string, const mem_char_t* substr, mem_size_t offset)
{
    mem_size_t ret = (mem_size_t)MEM_BAD_RETURN;
    if(p_string->is_initialized != mem_true) return ret;
    mem_size_t str_len    = mem_string_length(p_string) + 1;
    mem_size_t substr_len = MEM_STR_LEN(substr);
    for(; offset + substr_len <= str_len; offset++)
    {
        if(!MEM_STR_N_CMP((mem_char_t*)((mem_uintptr_t)p_string->buffer + offset), substr, substr_len))
        {
            ret = offset;
            break;
        }
    }

    return ret;
}

mem_size_t mem_string_rfind(struct _mem_string_t* p_string, const mem_char_t* substr, mem_size_t offset)
{
    mem_size_t ret = (mem_size_t)MEM_BAD_RETURN;
    if(offset == (mem_size_t)-1) offset = mem_string_length(p_string) + 1;
    if(p_string->is_initialized != mem_true) return ret;
    mem_size_t str_len    = mem_string_length(p_string) + 1;
    mem_size_t substr_len = MEM_STR_LEN(substr);
    for(; str_len > substr_len && offset > 0; offset--)
    {
        if(!MEM_STR_N_CMP((mem_char_t*)((mem_uintptr_t)p_string->buffer + offset), substr, substr_len))
        {
            ret = offset;
            break;
        }
    }

    return ret;
}

mem_char_t mem_string_at(struct _mem_string_t* p_string, mem_size_t pos)
{
    mem_char_t c = '\xFF';
    if(pos < mem_string_length(p_string))
        c = mem_string_c_str(p_string)[pos];
    return c;
}

mem_void_t mem_string_value(struct _mem_string_t* p_string, const mem_char_t* new_str)
{
    mem_size_t size = MEM_STR_LEN(new_str) + 1;
    if(size < 1) return;
    mem_char_t* _buffer = (mem_char_t*)malloc(size);
    memcpy(_buffer, new_str, size - 1);
    _buffer[size] = MEM_STR('\0');
    free(p_string->buffer);
    *p_string = mem_string_init();
    p_string->buffer = _buffer;
}

mem_char_t* mem_string_c_str(struct _mem_string_t* p_string)
{
    return p_string->buffer;
}

mem_void_t mem_string_c_set(struct _mem_string_t* p_string, mem_size_t pos, mem_char_t c)
{
    if(pos <= mem_string_length(p_string))
        p_string->buffer[pos] = c;
}

mem_bool_t mem_string_compare(struct _mem_string_t* p_string, struct _mem_string_t str)
{
    return (mem_bool_t)(MEM_STR_CMP(mem_string_c_str(p_string), mem_string_c_str(&str)) == 0);
}

struct _mem_string_t mem_string_substr(struct _mem_string_t* p_string, mem_size_t start, mem_size_t end)
{
    struct _mem_string_t new_str = mem_string_init();
    if(end == -1) end = mem_string_length(p_string) + 1;
    mem_size_t size = end - start;
    if(end > start && mem_string_length(p_string) > size)
    {
        mem_size_t buffer_size = size * sizeof(mem_char_t);
        mem_char_t* _buffer = (mem_char_t*)malloc(buffer_size);
        memcpy((void*)_buffer, (void*)((mem_uintptr_t)p_string->buffer + start), (size_t)size + 1);
        _buffer[buffer_size] = MEM_STR('\0');
        new_str.buffer = _buffer;
    }

    return new_str;
}

//mem_process_t

struct _mem_process_t mem_process_init()
{
    struct _mem_process_t _process;
    _process.name           = mem_string_init();
    _process.pid            = (mem_pid_t)MEM_BAD_RETURN;
    _process.is_valid       = &mem_process_is_valid;
    _process.compare        = &mem_process_compare;
    _process.is_initialized = mem_true;
    return _process;
}

mem_bool_t mem_process_is_valid(struct _mem_process_t* p_process)
{
    return (mem_bool_t)(
        p_process->is_initialized == mem_true &&
        MEM_STR_CMP(mem_string_c_str(&p_process->name), MEM_STR("")) &&
        p_process->pid != (mem_pid_t)MEM_BAD_RETURN
    );
}

mem_bool_t mem_process_compare(struct _mem_process_t* p_process, struct _mem_process_t process)
{
    return (mem_bool_t)(
        mem_string_compare(&p_process->name, process.name) == mem_true &&
        p_process->pid == process.pid
    );
}

//mem_module_t

struct _mem_module_t mem_module_init()
{
    struct _mem_module_t _mod;
    _mod.name           = mem_string_init();
    _mod.path           = mem_string_init();
    _mod.base           = (mem_voidptr_t)MEM_BAD_RETURN;
    _mod.size           = (mem_uintptr_t)MEM_BAD_RETURN;
    _mod.end            = (mem_voidptr_t)MEM_BAD_RETURN;
    _mod.is_valid       = &mem_module_is_valid;
    _mod.compare        = &mem_module_compare;
    _mod.is_initialized = mem_true;
    return _mod;
}

mem_bool_t mem_module_is_valid(struct _mem_module_t* p_mod)
{
    return (mem_bool_t)(
        p_mod->is_initialized                         &&
        MEM_STR_CMP(mem_string_c_str(&p_mod->name), MEM_STR("")) &&
        MEM_STR_CMP(mem_string_c_str(&p_mod->path), MEM_STR("")) &&
        p_mod->base != (mem_voidptr_t)MEM_BAD_RETURN  &&
        p_mod->size != (mem_uintptr_t)MEM_BAD_RETURN     &&
        p_mod->end  != (mem_voidptr_t)MEM_BAD_RETURN
    );
}

mem_bool_t mem_module_compare(struct _mem_module_t* p_mod, struct _mem_module_t mod)
{
    return (mem_bool_t)(
        mem_string_compare(&p_mod->name, mod.name) &&
        mem_string_compare(&p_mod->path, mod.path) &&
        p_mod->base == mod.base                    &&
        p_mod->size == mod.size                    &&
        p_mod->end  == mod.end                     
    );
}

//mem_alloc_t

struct _mem_alloc_t mem_alloc_init()
{
    struct _mem_alloc_t _alloc;
#   if defined(MEM_WIN)
    _alloc.protection = PAGE_EXECUTE_READWRITE;
    _alloc.type       = MEM_COMMIT | MEM_RESERVE;
#   elif defined(MEM_LINUX)
    _alloc.protection = PROT_EXEC | PROT_READ | PROT_WRITE;
    _alloc.type       = MAP_ANON  | MAP_PRIVATE;
#   endif

    _alloc.is_valid = &mem_alloc_is_valid;
    _alloc.is_initialized = mem_true;
    return _alloc;
}

mem_bool_t mem_alloc_is_valid(struct _mem_alloc_t* p_alloc)
{
    return (mem_bool_t)(
        p_alloc->is_initialized == mem_true &&
        p_alloc->protection     != (mem_prot_t)MEM_BAD_RETURN &&
        p_alloc->type           != (mem_prot_t)MEM_BAD_RETURN
    );
}

//mem_lib_t

struct _mem_lib_t mem_lib_init()
{
    struct _mem_lib_t _lib;
    _lib.path           = mem_string_init();
    _lib.is_valid       = &mem_lib_is_valid;
#   if defined(MEM_WIN)
#   elif defined(MEM_LINUX)
    _lib.mode = (mem_int_t)RTLD_LAZY;
#   endif
    _lib.is_initialized = mem_true;
    return _lib;
}

mem_bool_t mem_lib_is_valid(struct _mem_lib_t* p_lib)
{
    return (mem_bool_t)(
        p_lib->is_initialized &&
        !MEM_STR_CMP(mem_string_c_str(&p_lib->path), MEM_STR(""))
    );
}

//libmem

mem_string_t  mem_parse_mask(mem_string_t mask)
{
    mem_size_t size = mem_string_length(&mask);
    mem_string_t new_mask = mem_string_init();
    new_mask.resize(&new_mask, size + 1);
    for(mem_size_t i = 0; i <= size; i++)
    {
        mem_char_t c = mem_string_at(&mask, i);
        mem_string_c_set(&new_mask, i, (c == MEM_KNOWN_BYTE || c == toupper(MEM_KNOWN_BYTE) ? MEM_KNOWN_BYTE : MEM_UNKNOWN_BYTE));
    }

    mem_string_c_set(&new_mask, size, MEM_STR('\0'));
    return new_mask;
}

//ex
mem_pid_t mem_ex_get_pid(mem_string_t process_name)
{
    mem_pid_t pid = (mem_pid_t)MEM_BAD_RETURN;
#   if defined(MEM_WIN)
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!MEM_STR_CMP(procEntry.szExeFile, mem_string_c_str(&process_name)))
				{
					pid = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));

		}
	}
	CloseHandle(hSnap);
#   elif defined(MEM_LINUX)
    DIR* pdir = opendir("/proc");
	if (!pdir)
		return pid;

	struct dirent* pdirent;
	while (pid < 0 && (pdirent = readdir(pdir)))
	{
		pid_t id = atoi(pdirent->d_name);
		if (id > 0)
		{
			mem_string_t proc_name = mem_ex_get_process_name(id);
			if (mem_string_compare(&process_name, proc_name))
				pid = id;
		}
	}
	closedir(pdir);
#   endif
    return pid;
}

mem_string_t mem_ex_get_process_name(mem_pid_t pid)
{
    mem_string_t process_name = mem_string_init();
#   if defined(MEM_WIN)
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (pid == procEntry.th32ProcessID)
				{
					process_name = mem_string_new(procEntry.szExeFile);
                    process_name = mem_string_substr(&process_name, mem_string_rfind(&process_name, '\\', mem_string_length(&process_name)) + 1, mem_string_length(&process_name));
					//process_name = process_name.substr(process_name.rfind('\\', process_name.length()) + 1, process_name.length());
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
    CloseHandle(hSnap);
#   elif defined(MEM_LINUX)
    char path_buffer[64];
    snprintf(path_buffer, sizeof(path_buffer) - 1, "/proc/%i/maps", pid);
    int fd = open(path_buffer, O_RDONLY);
    if(fd == -1) return process_name;
    mem_string_t file_buffer = mem_string_init();
    mem_size_t   file_size   = 1;
    int read_check = 0;
    for(char c; (read_check = read(fd, &c, 1)) != -1 && read_check != 0; file_size++)
    {
        mem_string_resize(&file_buffer, file_size);
        mem_string_c_set(&file_buffer,  file_size, c);
        if(mem_string_at(&file_buffer, file_size) == '\n') break;
    }

    mem_size_t process_name_end = mem_string_find(&file_buffer, "\n", 0);
    mem_size_t process_name_pos = mem_string_rfind(&file_buffer, "/", process_name_end) + 1;
    if(process_name_end == (mem_size_t)MEM_BAD_RETURN || process_name_pos == (mem_size_t)MEM_BAD_RETURN || process_name_pos == (mem_size_t)(MEM_BAD_RETURN + 1)) return process_name;
    mem_string_empty(&process_name);
    process_name = mem_string_substr(&file_buffer, process_name_pos, process_name_end);
    mem_string_empty(&file_buffer);
    close(fd);
#   endif
    return process_name;
}

mem_process_t mem_ex_get_process(mem_pid_t pid)
{
    mem_process_t process = mem_process_init();
    process.pid  = pid;
    process.name = mem_ex_get_process_name(process.pid);
#	if defined(MEM_WIN)
	process.handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, process.pid);
#	elif defined(MEM_LINUX)
#	endif
    return process;
}

mem_module_t mem_ex_get_module(mem_process_t process, mem_string_t module_name)
{
    mem_module_t modinfo = mem_module_init();
#   if defined(MEM_WIN)
    HMODULE hMod;
	mem_char_t modpath[MAX_PATH];
	GetModuleHandleEx(NULL, mem_string_c_str(&module_name), &hMod);
	MODULEINFO module_info = { 0 };
	GetModuleInformation(process.handle, hMod, &module_info, sizeof(module_info));
	GetModuleFileName(hMod, modpath, sizeof(modpath) / sizeof(mem_char_t));
	modinfo.base = (voidptr_t)module_info.lpBaseOfDll;
	modinfo.size = (size_t)module_info.SizeOfImage;
	modinfo.end = (voidptr_t)((uintptr_t)modinfo.base + modinfo.size);
	modinfo.handle = (module_handle_t)hMod;
	modinfo.path = mem_string_new(modpath);
#   elif defined(MEM_LINUX)
    char path_buffer[64];
	snprintf(path_buffer, sizeof(path_buffer), "/proc/%i/maps", process.pid);
    int fd = open(path_buffer, O_RDONLY);
    if(fd == -1) return modinfo;
    mem_string_t file_buffer = mem_string_init();
    mem_size_t   file_size   = 1;
    int read_check = 0;
    for(char c; (read_check = read(fd, &c, 1)) != -1 && read_check != 0; file_size++)
    {
        mem_string_resize(&file_buffer, file_size);
        mem_string_c_set(&file_buffer,  file_size, c);
    }

    mem_size_t module_name_pos = 0;
    mem_size_t module_name_end = 0;
    mem_size_t next            = 0;
    mem_string_t module_name_str = mem_string_init();
    while((next = mem_string_find(&file_buffer, mem_string_c_str(&module_name), module_name_end)) != file_buffer.npos && (module_name_pos = mem_string_find(&file_buffer, "/", next)) != file_buffer.npos)
    {
        module_name_end = mem_string_find(&file_buffer, "\n", module_name_pos);
        module_name_pos = mem_string_rfind(&file_buffer, "/", module_name_end) + 1;
        module_name_str = mem_string_substr(&file_buffer, module_name_pos, module_name_end);
        if(mem_string_length(&module_name_str) >= mem_string_length(&module_name))
        {
            if(!MEM_STR_N_CMP(mem_string_c_str(&module_name_str), mem_string_c_str(&module_name), mem_string_length(&module_name)))
                break;
        }
    }

    if(module_name_pos == 0 || module_name_end == 0 || module_name_pos == file_buffer.npos || module_name_end == file_buffer.npos) return modinfo;
    mem_size_t module_name_str_match_size = mem_string_length(&module_name_str) + 2;
    mem_char_t* module_name_str_match = (mem_char_t*)malloc(module_name_str_match_size);
    module_name_str_match[0] = '/';
    memcpy((void*)(module_name_str_match + 1), (void*)mem_string_c_str(&module_name_str), module_name_str_match_size - 2);
    module_name_str_match[module_name_str_match_size - 1] = '\n';
    module_name_str_match[module_name_str_match_size] = '\0';

    mem_size_t   base_address_pos = mem_string_rfind(&file_buffer, "\n", mem_string_find(&file_buffer, module_name_str_match, 0)) + 1;
    mem_size_t   base_address_end = mem_string_find(&file_buffer, "-", base_address_pos);
    if(base_address_pos == file_buffer.npos || base_address_end == file_buffer.npos) return modinfo;
    mem_string_t base_address_str = mem_string_substr(&file_buffer, base_address_pos, base_address_end);

    mem_size_t   end_address_pos = mem_string_rfind(&file_buffer, "\n", mem_string_rfind(&file_buffer, module_name_str_match, mem_string_length(&file_buffer)));
    end_address_pos = mem_string_find(&file_buffer, "-", end_address_pos) + 1;
    mem_size_t   end_address_end = mem_string_find(&file_buffer, " ", end_address_pos);
    if(end_address_pos == file_buffer.npos || end_address_end == file_buffer.npos) return modinfo;
    mem_string_t end_address_str = mem_string_substr(&file_buffer, end_address_pos, end_address_end);

    mem_size_t   module_path_pos = mem_string_find(&file_buffer, "/", end_address_end);
    mem_size_t   module_path_end = mem_string_find(&file_buffer, "\n", module_path_pos);
    if(module_path_pos == 0 || module_path_end == 0 || module_path_pos == file_buffer.npos || module_path_end == file_buffer.npos) return modinfo;
    mem_string_t module_path_str = mem_string_substr(&file_buffer, module_path_pos, module_path_end);

    mem_uintptr_t base_address = (mem_uintptr_t)MEM_BAD_RETURN;
    mem_uintptr_t end_address  = (mem_uintptr_t)MEM_BAD_RETURN;

#   if defined(MEM_86)
	base_address = strtoul(mem_string_c_str(&base_address_str), NULL, 16);
	end_address = strtoul(mem_string_c_str(&end_address_str), NULL, 16);
#   elif defined(MEM_64)
	base_address = strtoul(mem_string_c_str(&base_address_str), NULL, 16);
	end_address = strtoul(mem_string_c_str(&end_address_str), NULL, 16);
#   endif

    mem_module_handle_t handle = (mem_module_handle_t)MEM_BAD_RETURN;
    if(MEM_STR_CMP(mem_string_c_str(&process.name), mem_string_c_str(&module_name_str)))
	    handle = (mem_module_handle_t)dlopen(mem_string_c_str(&module_path_str), RTLD_LAZY);

    modinfo.name = module_name_str;
	modinfo.base = (mem_voidptr_t)base_address;
	modinfo.end  = (mem_voidptr_t)end_address;
	modinfo.size = end_address - base_address;
	modinfo.path = module_path_str;
	modinfo.handle = handle;

    free(module_name_str_match);
    file_buffer.empty(&file_buffer);
    close(fd);

#   endif
    return modinfo;
}

mem_bool_t mem_ex_is_process_running(mem_process_t process)
{
    mem_bool_t ret = mem_false;
    if(!mem_process_is_valid(&process)) return ret;
#   if defined(MEM_WIN)
    DWORD exit_code;
	GetExitCodeProcess(process.handle, &exit_code);
	ret = (mem_bool_t)(exit_code == STILL_ACTIVE);
#   elif defined(MEM_LINUX)
    struct stat sb;
	char path_buffer[64];
	snprintf(path_buffer, sizeof(path_buffer), "/proc/%i", process.pid);
	stat(path_buffer, &sb);
	ret = (mem_bool_t)S_ISDIR(sb.st_mode);
#   endif

    return ret;
}

mem_int_t mem_ex_read(mem_process_t process, mem_voidptr_t src, mem_voidptr_t dst, mem_size_t size)
{
    mem_int_t ret = (mem_int_t)MEM_BAD_RETURN;
#   if defined(MEM_WIN)
    ret = (mem_int_t)ReadProcessMemory(process.handle, (LPCVOID)src, (LPVOID)dst, (SIZE_T)size, NULL);
#   elif defined(MEM_LINUX)
    struct iovec iosrc;
	struct iovec iodst;
	iodst.iov_base = dst;
	iodst.iov_len = size;
	iosrc.iov_base = src;
	iosrc.iov_len = size;
	ret = (mem_int_t)process_vm_readv(process.pid, &iodst, 1, &iosrc, 1, 0);
#   endif

    return ret;
}

mem_int_t mem_ex_write(mem_process_t process, mem_voidptr_t src, mem_voidptr_t data, mem_size_t size)
{
    mem_int_t ret = (mem_int_t)MEM_BAD_RETURN;
    if(!mem_process_is_valid(&process)) return ret;
#   if defined(MEM_WIN)
    ret = (mem_int_t)WriteProcessMemory(process.handle, (LPVOID)src, (LPCVOID)data, (SIZE_T)size, NULL);
#   elif defined(MEM_LINUX)
    struct iovec iosrc;
	struct iovec iodst;
	iosrc.iov_base = data;
	iosrc.iov_len = size;
	iodst.iov_base = src;
	iodst.iov_len = size;
	ret = (mem_int_t)process_vm_writev(process.pid, &iosrc, 1, &iodst, 1, 0);
#   endif

    return ret;
}

mem_int_t mem_ex_set(mem_process_t process, mem_voidptr_t src, mem_byte_t byte, mem_size_t size)
{
    mem_int_t ret = (mem_int_t)MEM_BAD_RETURN;
    mem_byte_t data[size];
    memset(data, byte, size);
    ret = (mem_int_t)mem_ex_write(process, src, data, size);
    return ret;
}

mem_int_t mem_ex_protect(mem_process_t process, mem_voidptr_t src, mem_size_t size, mem_prot_t protection)
{
    mem_int_t ret = (mem_int_t)MEM_BAD_RETURN;
    if(!mem_process_is_valid(&process)) return ret;
#	if defined(MEM_WIN)
	DWORD old_protect;
	if (process.handle == (HANDLE)NULL || src <= (mem_voidptr_t)NULL || size == 0 || protection <= NULL) return ret;
	ret = (mem_int_t)VirtualProtectEx(process.handle, (LPVOID)src, (SIZE_T)size, (DWORD)protection, &old_protect);
#	elif defined(MEM_LINUX)
#	endif
	return ret;
}

mem_voidptr_t mem_ex_pattern_scan(mem_process_t process, mem_bytearray_t pattern, mem_string_t mask, mem_voidptr_t base, mem_voidptr_t end)
{
    mem_voidptr_t ret = (mem_voidptr_t)MEM_BAD_RETURN;
    if(!mem_process_is_valid(&process)) return ret;
    mask = mem_parse_mask(mask);
	mem_uintptr_t scan_size = (mem_uintptr_t)end - (mem_uintptr_t)base;

	for (mem_uintptr_t i = 0; i < scan_size; i++)
	{
		mem_bool_t found = mem_true;
		int8_t pbyte;
		for (mem_uintptr_t j = 0; j < MEM_STR_LEN(pattern); j++)
		{
			mem_ex_read(process, (mem_voidptr_t)((mem_uintptr_t)base + i + j), &pbyte, 1);
			found &= mem_string_c_str(&mask)[j] == MEM_UNKNOWN_BYTE || pattern[j] == pbyte;
		}

		if (found)
		{
			ret = (mem_voidptr_t)((mem_uintptr_t)base + i);
			break;
		}
	}

	return ret;
}

//in

mem_pid_t mem_in_get_pid()
{
    mem_pid_t pid = (mem_pid_t)MEM_BAD_RETURN;
#   if defined(MEM_WIN)
    pid = (mem_pid_t)GetCurrentProcessId();
#   elif defined(MEM_LINUX)
    pid = (mem_pid_t)getpid();
#   endif
    return pid;
}

mem_process_t mem_in_get_process()
{
    mem_process_t process = mem_process_init();
    process.pid  = mem_in_get_pid();
    process.name = mem_in_get_process_name();
#   if defined(MEM_WIN)
    process.handle = GetCurrentProcess();
#   elif defined(MEM_LINUX)
#   endif
    return process;
}

mem_string_t mem_in_get_process_name()
{
    mem_string_t process_name = mem_string_init();
#   if defined(MEM_WIN)
    char_t buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, sizeof(buffer)/sizeof(char_t));
    process_name = mem_string_new(buffer);
    process_name = mem_string_substr(&process_name, mem_string_rfind(&process_name, "\\", mem_string_length(&process_name)), mem_string_length(&process_name));
#   elif defined(MEM_LINUX)
    process_name = mem_ex_get_process_name(mem_in_get_pid());
#   endif
    return process_name;
}

mem_module_t mem_in_get_module(mem_string_t module_name)
{
    mem_module_t modinfo = mem_module_init();
#   if defined(MEM_WIN)
    MODULEINFO module_info;
	HMODULE hmod = GetModuleHandle(mem_string_c_str(&module_name));
	HANDLE cur_handle = mem_in_get_process().handle;
	if (hmod == NULL) return modinfo;
    mem_char_t path_buffer[MAX_PATH];
	GetModuleInformation(cur_handle, hmod, &module_info, sizeof(module_info));
    GetModuleFileName(hmod, &path_buffer, sizeof(path_buffer)/sizeof(mem_char_t));
    modinfo.name = mem_string_new(path_buffer);
    modinfo.name = mem_string_substr(&modinfo.name, mem_string_rfind(&modinfo.name, "\\", mem_string_length(&modinfo.name)), mem_string_length(&modinfo.name));
    modinfo.path = mem_string_new(path_buffer);
	modinfo.base = (mem_voidptr_t)module_info.lpBaseOfDll;
	modinfo.size = (mem_size_t)module_info.SizeOfImage;
	modinfo.end = (mem_voidptr_t)((uintptr_t)modinfo.base + modinfo.size);
	modinfo.handle = hmod;
#   elif defined(MEM_LINUX)
    modinfo = mem_ex_get_module(mem_in_get_process(), module_name);
#   endif
    return modinfo;
}

mem_void_t mem_in_read(mem_voidptr_t src, mem_voidptr_t dst, mem_size_t size)
{
    memcpy(dst, src, size);
}

mem_void_t mem_in_write(mem_voidptr_t src, mem_voidptr_t data, mem_size_t size)
{
    memcpy(src, data, size);
}

mem_void_t mem_in_set(mem_voidptr_t src, mem_byte_t byte, mem_size_t size)
{
    memset(src, byte, size);
}

mem_int_t mem_in_protect(mem_voidptr_t src, mem_size_t size, mem_prot_t protection)
{
    mem_int_t ret = (mem_int_t)MEM_BAD_RETURN;
    if(src == (mem_voidptr_t)MEM_BAD_RETURN || size == (mem_size_t)MEM_BAD_RETURN || size == 0 || protection == (mem_prot_t)MEM_BAD_RETURN) return ret;
#   if defined(MEM_WIN)
    ret = (mem_int_t)VirtualProtect((LPVOID)src, (SIZE_T)size, (DWORD)protection, &old_protect);
#   elif defined(MEM_LINUX)
    long pagesize = sysconf(_SC_PAGE_SIZE);
	uintptr_t src_page = (uintptr_t)src - ((uintptr_t)src % pagesize);
	ret = (mem_int_t)mprotect((void*)src_page, size, protection);
#   endif
    return ret;
}

mem_voidptr_t mem_in_allocate(mem_size_t size, mem_alloc_t allocation)
{
    mem_voidptr_t addr = (mem_voidptr_t)MEM_BAD_RETURN;
#   if defined(MEM_WIN)
    addr = (mem_voidptr_t)VirtualAlloc(NULL, (SIZE_T)size, allocation.type, (DWORD)allocation.protection);
#   elif defined(MEM_LINUX)
    addr = (mem_voidptr_t)mmap(NULL, size, allocation.protection, allocation.type, -1, 0);
#   endif

    return addr;
}

mem_bool_t mem_in_compare(mem_voidptr_t pdata1, mem_voidptr_t pdata2, mem_size_t size)
{
    return (mem_bool_t)(memcmp(pdata1, pdata2, size) == 0);
}

mem_voidptr_t mem_in_scan(mem_voidptr_t data, mem_voidptr_t base, mem_voidptr_t end, mem_size_t size)
{
    mem_voidptr_t ret = (mem_voidptr_t)MEM_BAD_RETURN;
	for(mem_uintptr_t i = 0; (mem_uintptr_t)base + i < (mem_uintptr_t)end; i += size)
	{
		if(mem_in_compare(data, (mem_voidptr_t)((mem_uintptr_t)base + i), size))
		{
			ret = (mem_voidptr_t)((mem_uintptr_t)base + i);
			break;
		}
	}

	return ret;
}

mem_voidptr_t mem_in_pattern_scan(mem_bytearray_t pattern, mem_string_t mask, mem_voidptr_t base, mem_size_t size)
{
    mem_voidptr_t ret = (mem_voidptr_t)MEM_BAD_RETURN;
	mask = mem_parse_mask(mask);
	mem_uintptr_t scan_size = size;

	for (mem_uintptr_t i = 0; i < scan_size; i++)
	{
		mem_bool_t found = mem_true;
		for (mem_uintptr_t j = 0; j < scan_size; j++)
		{
			found &= mem_string_c_str(&mask)[j] == MEM_UNKNOWN_BYTE || pattern[j] == *(mem_int8_t*)((mem_uintptr_t)base + i + j);
		}

		if (found)
		{
			ret = (mem_voidptr_t)((mem_uintptr_t)base + i);
			break;
		}
	}

	return ret;   
}

mem_size_t mem_in_detour_length(mem_detour_int_t method)
{
    mem_size_t ret = (mem_size_t)MEM_BAD_RETURN;
    switch (method)
	{
		case method0: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD0); break;
		case method1: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD1); break;
		case method2: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD2); break;
		case method3: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD3); break;
		case method4: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD4); break;
		case method5: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD5); break;
	}

	return ret;
}

mem_int_t mem_in_detour(mem_voidptr_t src, mem_voidptr_t dst, mem_size_t size, mem_detour_int_t method, mem_bytearray_t* stolen_bytes)
{
    mem_int_t ret = (mem_int_t)MEM_BAD_RETURN;
    mem_size_t detour_size = mem_in_detour_length(method);
	mem_prot_t protection;
#	if defined(MEM_WIN)
	protection = PAGE_EXECUTE_READWRITE;
#	elif defined(MEM_LINUX)
	protection = PROT_EXEC | PROT_READ | PROT_WRITE;
#	endif
	if (detour_size == MEM_BAD_RETURN || size < detour_size || mem_in_protect(src, size, protection) == MEM_BAD_RETURN) return ret;

    if(stolen_bytes != NULL)
	{
		*stolen_bytes = (mem_bytearray_t)malloc(size);
        for(mem_size_t i = 0; i < size; i++)
        	*stolen_bytes[i] = *(mem_int8_t*)(src + i);
	}

    switch (method)
	{
        case method0:
        {
            mem_byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD0);
            *(mem_uintptr_t*)((mem_uintptr_t)detour_buffer + sizeof(MEM_MOV_REGAX)) = (mem_uintptr_t)dst;
            mem_in_write(src, detour_buffer, sizeof(detour_buffer));
            break;
        }

        case method1:
        {
            mem_byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD1);
            *(mem_dword_t*)((mem_uintptr_t)detour_buffer + sizeof(MEM_JMP)) = (mem_dword_t)((mem_uintptr_t)dst - (mem_uintptr_t)src - detour_size);
            mem_in_write(src, detour_buffer, sizeof(detour_buffer));
            break;
        }

        case method2:
        {
            mem_byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD2);
            *(mem_uintptr_t*)((mem_uintptr_t)detour_buffer + sizeof(MEM_MOV_REGAX)) = (mem_uintptr_t)dst;
            mem_in_write(src, detour_buffer, sizeof(detour_buffer));
            break;
        }

        case method3:
        {
            mem_byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD3);
            *(mem_dword_t*)((mem_uintptr_t)detour_buffer + sizeof(MEM_PUSH)) = (mem_dword_t)((mem_uintptr_t)dst - (mem_uintptr_t)src - detour_size);
            mem_in_write(src, detour_buffer, sizeof(detour_buffer));
            break;
        }

        case method4:
        {
            mem_byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD4);
            *(mem_uintptr_t*)((mem_uintptr_t)detour_buffer + sizeof(MEM_MOV_REGAX)) = (mem_uintptr_t)dst;
            mem_in_write(src, detour_buffer, sizeof(detour_buffer));
            break;
        }

        case method5:
        {
            mem_byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD5);
            *(mem_dword_t*)((mem_uintptr_t)detour_buffer + sizeof(MEM_CALL)) = (mem_dword_t)((mem_uintptr_t)dst - (mem_uintptr_t)src - detour_size);
            mem_in_write(src, detour_buffer, sizeof(detour_buffer));
            break;
        }

        default:
        {
            return (mem_int_t)ret;
            break;
        }
    }

    ret = (mem_int_t)!MEM_BAD_RETURN;
    return ret;
}

mem_voidptr_t mem_in_detour_trampoline(mem_voidptr_t src, mem_voidptr_t dst, mem_size_t size, mem_detour_int_t method, mem_bytearray_t* stolen_bytes)
{
    mem_voidptr_t gateway = (mem_voidptr_t)MEM_BAD_RETURN;
    mem_size_t detour_size = mem_in_detour_length(method);
	mem_alloc_t allocation;
	mem_prot_t protection;
#   if defined(MEM_WIN)
    protection = PAGE_EXECUTE_READWRITE;
	allocation.type = MEM_COMMIT | MEM_RESERVE;
	allocation.protection = PAGE_EXECUTE_READWRITE;
#   elif defined(MEM_LINUX)
    protection = PROT_EXEC | PROT_READ | PROT_WRITE;;
	allocation.protection = PROT_EXEC | PROT_READ | PROT_WRITE;
	allocation.type = MAP_ANON | MAP_PRIVATE;
#   endif

    if (detour_size == (mem_size_t)MEM_BAD_RETURN || size < detour_size || mem_in_protect(src, size, protection) == MEM_BAD_RETURN) return gateway;
    mem_size_t gateway_size = size + detour_size;
    gateway = mem_in_allocate(gateway_size, allocation);
    if (!gateway || gateway == (mem_voidptr_t)MEM_BAD_RETURN) return (mem_voidptr_t)MEM_BAD_RETURN;
    mem_in_set(gateway, 0x0, gateway_size);
    mem_in_write(gateway, src, size);
    mem_in_detour((mem_voidptr_t)((mem_uintptr_t)gateway + size), (mem_voidptr_t)((mem_uintptr_t)src + size), detour_size, method, NULL);
    mem_in_detour(src, dst, size, method, stolen_bytes);

    return gateway;
}

mem_void_t mem_in_detour_restore(mem_voidptr_t src, mem_bytearray_t stolen_bytes, mem_size_t size)
{
    mem_prot_t protection;
#   if defined(MEM_WIN)
    protection = PAGE_EXECUTE_READWRITE;
#   elif defined(MEM_LINUX)
    protection = PROT_EXEC | PROT_READ | PROT_WRITE;
#   endif
    if(mem_in_protect(src, size, protection) != MEM_BAD_RETURN)
	    mem_in_write(src, (mem_voidptr_t)stolen_bytes, (mem_size_t)size);
}

mem_int_t mem_in_load_library(mem_lib_t lib, mem_module_t* mod)
{
    mem_int_t ret = (mem_int_t)MEM_BAD_RETURN;
    if(!mem_lib_is_valid(&lib)) return ret;
#   if defined(MEM_WIN)
    HMODULE h_mod = LoadLibrary(mem_string_c_str(&lib.path));
    *mod = mem_in_get_module(mem_string_substr(&lib.path, mem_string_rfind(&lib.path, '\\', mem_string_length(&lib.path)), mem_string_length(&lib.path)));
    ret = h_mod != (HMODULE)NULL;
#   elif defined(MEM_LINUX)
    void* h_mod = dlopen(mem_string_c_str(&lib.path), lib.mode);
	ret = (h_mod == (mem_voidptr_t)-1 ? MEM_BAD_RETURN : !MEM_BAD_RETURN);
	if(mod != NULL && ret != (mem_int_t)MEM_BAD_RETURN)
	{
		*mod = mem_in_get_module(lib.path);
		mod->handle = h_mod;
	}
#   endif

    return ret;
}

#endif //MEM_COMPATIBLE