#include <stdlib.h>
#include "lua.h"
#include "lauxlib.h"

#include "smaz.h"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#elif
#define DLLEXPORT
#endif /* _WIN32 */


static int
lcompress(lua_State *L)
{
    int stack_size = lua_gettop(L);
    char *input;
    size_t input_size = 0;
    input = (char *) luaL_checklstring(L, 1, &input_size);
    size_t output_size = input_size;
    if (stack_size == 2) // 额外输入了output_size
    {
        output_size = (size_t) luaL_checkinteger(L, 2);
    }
    else if (stack_size > 2)
    {
        return luaL_error(L, "2 args at most, data and output size which is optional");
    }
    char *output_buf = (char *) lua_newuserdata(L, output_size);
    int buffer_updated = smaz_compress(input, (int) input_size, output_buf, output_size);
    if (buffer_updated == (int) (output_size + 1))
    {
        return luaL_error(L, "output buffer is too small");
    }
    lua_pushlstring(L, output_buf, (size_t) buffer_updated);
    return 1;
}

static int
ldecompress(lua_State *L)
{
    int stack_size = lua_gettop(L);
    char *input;
    size_t input_size = 0;
    input = (char *) luaL_checklstring(L, 1, &input_size);
    size_t output_size = input_size * 2;
    if (stack_size == 2) // 额外输入了output_size
    {
        output_size = (size_t) luaL_checkinteger(L, 2);
    }
    else if (stack_size > 2)
    {
        return luaL_error(L, "2 args at most, data and output size which is optional");
    }
    char *output_buf = (char *) lua_newuserdata(L, output_size);
    int buffer_updated = smaz_decompress(input, (int) input_size, output_buf, output_size);
    if (buffer_updated == (int) (output_size + 1))
    {
        return luaL_error(L, "output buffer is too small");
    }
    lua_pushlstring(L, output_buf, (size_t) buffer_updated);
    return 1;
}

static luaL_Reg lua_funcs[] = {
        {"compress",   &lcompress},
        {"decompress", &ldecompress},
        {NULL, NULL}
};

DLLEXPORT int luaopen_smaz(lua_State *L)
{
    luaL_newlib(L, lua_funcs);
    return 1;
}