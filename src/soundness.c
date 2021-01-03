/**

This file is part of lua-soundness

(c) 2020 augmented logic < dev@augmentedlogic.com >

MIT License

**/

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <ao/ao.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define BITS       16
#define CHANNELS   1
#define RATE       22050

int sound(double freq_p, double time_p, double volume_p) {

    ao_device *device;
    int driver;
    ao_sample_format format;
    ao_initialize();
    driver = ao_default_driver_id();

    memset(&format, 0, sizeof(format));
    format.bits = BITS;
    format.channels = CHANNELS;
    format.rate = RATE;
    format.byte_format = AO_FMT_LITTLE;

    device = ao_open_live(driver, &format, NULL);

    int buf_size = (int) format.bits/8 * format.channels * format.rate * time_p;
    char buffer[buf_size];
    int sample;
    int i;
    int c;
    int j;
    srand(time(NULL));
    for (i = 1; i < format.rate * time_p; ++i) {
         for(c = 0; c < format.channels; ++c) {
              sample = (int) (volume_p * (1<<(format.bits - 1)) * sin(2 * M_PI * freq_p * ((float) i/format.rate)));
              for (j = 0; j < format.bits/8; ++j) {
                 buffer[(int) format.bits/8*i*format.channels + format.channels*c + j] = sample & 0xff;
                 sample >>= 8;
              }
         }
    }
    ao_play(device, buffer, buf_size);
    ao_close(device);
    ao_shutdown();
    return 0;
}

int noise(double time_p, double volume_p) {

    ao_device *device;
    int driver;
    ao_sample_format format;
    ao_initialize();
    driver = ao_default_driver_id();

    memset(&format, 0, sizeof(format));
    format.bits = BITS;
    format.channels = CHANNELS;
    format.rate = RATE;
    format.byte_format = AO_FMT_LITTLE;

    device = ao_open_live(driver, &format, NULL);

    int buf_size = (int) format.bits/8 * format.channels * format.rate * time_p;
    char buffer[buf_size];
    int sample;
    int i;
    int c;
    int j;
    srand(time(NULL));
    for (i = 1; i < format.rate * time_p; ++i) {
         for(c = 0; c < format.channels; ++c) {
              sample =  (int) (volume_p * (1<<(format.bits - 1)) * sin(2 * M_PI * rand() * ((float) i/format.rate)));
              for (j = 0; j < format.bits/8; ++j) {
                 buffer[(int) format.bits/8*i*format.channels + format.channels*c + j] = sample & 0xff;
                 sample >>= 8;
              }
         }
    }
    ao_play(device, buffer, buf_size);
    ao_close(device);
    ao_shutdown();
    return 0;
}


static int l_pause(lua_State *L)
{
        double pause_u = luaL_checknumber(L,1) * 1000000;
        usleep((int) pause_u);
        return 0;
}


static int l_sound(lua_State *L)
{
        sound(luaL_checknumber(L,1), luaL_checknumber(L,2), luaL_checknumber(L,3));
        return 0;
}


static int l_noise(lua_State *L)
{
        noise(luaL_checknumber(L,1), luaL_checknumber(L,2));
        return 0;
}


// 5.2+
#if LUA_VERSION_NUM >= 502
static const struct luaL_Reg soundness [] = {
    {"sound", l_sound },
    {"noise", l_noise },
    {"pause", l_pause },
    {NULL, NULL}
};
#endif

#if LUA_VERSION_NUM >= 502
int luaopen_soundness(lua_State *L) {
    luaL_newlib(L, soundness);
    return 1;
}
#endif


// 5.1
#if LUA_VERSION_NUM == 501
static const struct luaL_reg lib[] = {
    {"sound", l_sound },
    {"noise", l_noise },
    {"pause", l_pause },
    {NULL, NULL}
};
#endif

#if LUA_VERSION_NUM == 501
LUALIB_API int luaopen_soundness(lua_State *L) {
        luaL_openlib(L, "soundness", lib, 0);
        return 1;
}
#endif


