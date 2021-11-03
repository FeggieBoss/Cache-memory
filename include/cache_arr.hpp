#include "element.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>

const int n = 1000;
const int cache_size = 32 * 1024;
const int ways = 4;
const int block_byte_size = 64;
const int sizeof_double = 8; // sizeof(double) = 8
const int block_double_size = block_byte_size / sizeof_double;
const int blocks_in_way = cache_size / block_byte_size / ways;
const int double_id_size = 13; // 12 < log2(sizeof(double)*1000) < 13
const int field_id_size = log2(8);

enum fields
{
    X,
    Y,
    AX,
    AY,
    VX,
    VY,
    A,
    B
};

class cache_arr {
private:
    int cache_misses_ct, access_ct, cur_time;
    element* ram;
    double cache[ways][blocks_in_way][block_double_size];
    size_t ids[ways][blocks_in_way];
    int acces_times[ways][blocks_in_way];

    size_t get_arr_id(size_t double_id);

    size_t get_field_id(size_t double_id);

    size_t get_short_id(size_t arr_id);

    size_t get_block_id(size_t arr_id);

    void write_block_ram(size_t way_id, size_t block_id);

    element& read_block_ram(size_t id_ram);

    /* ищем блок
    * 1) нашли - возвращаем номер way, в котором он лежит
    * 2) не нашли - записываем туда блок из оперативной памяти
    * (если блок не был пустым - сохраняем старые данные в опретивную память)
    */
    size_t get_way(size_t arr_id, size_t short_id, size_t block_id);

    double& lru_read(size_t double_id);

    void lru_write(size_t double_id, double v);

public:

    void print_log();
    
    cache_arr(element* arr_);

    double& read(size_t id, size_t field_id);
    
    void write(size_t id, size_t field_id, double v);
};
