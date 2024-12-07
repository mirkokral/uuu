#include "g.hpp"
#include "errors.hpp"
#include "terminal.hpp"
#include "mem.hpp"

int block_num = 0;
int mem_lower = 0;
int mem_upper = 0;

bool check(char *s, int bittocheck)
{
    size_t tn = (int)bittocheck / (sizeof(char) * 8);
    int o = sizeof(char) * 8 - (bittocheck % (sizeof(char) * 8)) - 1;
    return (s[tn] & 1 << o) != 0;
}

void set(char *s, int bittoset, bool to)
{
    size_t tn = (int)bittoset / (sizeof(char) * 8);
    int o = sizeof(char) * 8 - (bittoset % (sizeof(char) * 8)) - 1;
    s[tn] = (s[tn] | (to ? 1 : 0) << o);
}

bool get_free(int addr) {
    char* mem = (char*)mem_lower;
    return check(mem, addr - mem_lower - block_num);
}
void set_free(int addr, bool isfree) {
    char* mem = (char*)mem_lower;
    set(mem, addr - mem_lower - block_num, isfree);
}

void mem_init(int umem, int lmem)
{
    mem_lower = lmem;
    mem_upper = umem;
    block_num = (int)mem_upper - mem_lower / 9.0f;

    if (mem_upper - mem_lower / 9.0f != ((int)mem_upper - mem_lower / 9.0f))
    {
        kernel_panic("Memory cannot be enblocked");
    }

    int pe = 1;
    for (int i = mem_lower; i <= mem_upper; i++)
    {
        if (i % ((mem_upper - mem_lower) / 10000) == 0)
        {
            draw_string("Blocking out available memory: ", 10, get_fheight('F') + 10);
            char *buf;
            citoa(i - mem_lower, buf, 10);
            draw_string(buf, 10 + get_fwidth('F') * 31, get_fheight('F') + 10);
        }
        int *ur = (int *)i;
        ur = 0;
    }
    char* mem = (char*)mem_lower;
    set(mem, 1000, true);
    if(!check(mem, 1000)) {
        kernel_panic("Memory test failed.");
    }
}