#include <iostream>
#include <lua.hpp>

//显示栈内情况
static void stackDump(lua_State* L);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "You should input the lua script file path" << std::endl;
        return -1;
    }

    // Create a lua state. (You could treat it as a lua stack)
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Load lua script file.
    int fret = luaL_dofile(L, argv[1]);
    if (fret) {
        std::cout << "Read lua file " << argv[1] << " error!" << std::endl;
        return -1;
    }

    // Fetch global string lua var and push it in the stack.
    lua_getglobal(L, "name");
    std::cout <<"Var name is " << lua_tostring(L,-1) << std::endl;

    // Fetch global number lua var and push it in the stack.
    lua_getglobal(L, "version");
    std::cout << "Var version is " << lua_tonumber(L, -1) << std::endl;

    // Fetch global table lua var and push it in the stack.
    lua_getglobal(L, "me");  // Table will be pushed in the stack.
    if (!lua_istable(L, -1)) {
        std::cout << "error:it is not a table" << std::endl;
    }
    // Fetch element in table and push it in the stack.
    lua_getfield(L, -1 ,"like");
    std::cout << "Ele like is "<< lua_tostring(L, -1) << std::endl;
    lua_getfield(L, -2, "gender");
    std::cout << "Ele gender is " << lua_tostring(L, -1) << std::endl;

    // Fetch function "add" and push it in the stack.
    lua_getglobal(L, "add");
    // Push params to the stack.
    lua_pushnumber(L, 15);
    lua_pushnumber(L, 5);

    // Look up lua stack.
    stackDump(L);
    
    // Call function add, params are: lua state, function params' count, return fields' count, error or not.
    lua_pcall(L, 2, 2, 0);
    std::cout<< "Add(5, 15) is boolean:" << lua_toboolean(L, -1) << ", number:"  << lua_tonumber(L, -2) << std::endl;

    // After calling, the function and params were poped from the stack.
    // Look up lua stack.
    stackDump(L);

    // close lua state.
    lua_close(L);

    return 0;
}

static void stackDump(lua_State* L) {
    std::cout << "----------------Begin dump lua stack--------------" << std::endl;
    int top = lua_gettop(L);
    for (int i = 1; i <= top; ++i) {
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING:
                std::cout << lua_tostring(L, i) << std::endl;
                break;
            case LUA_TBOOLEAN:
                std::cout << lua_toboolean(L, i) << std::endl;
                break;
            case LUA_TNUMBER:
                std::cout << lua_tonumber(L, i) << std::endl;
                break;
            default:
                std::cout << lua_typename(L, t) << std::endl;
                break;
        }
    }
    std::cout << "----------------Begin dump lua stack--------------" << std::endl;
}
