#include "cache_arr.hpp"

size_t cache_arr::get_arr_id(size_t double_id) {
    return (double_id >> (int)log2(sizeof_double));
}

size_t cache_arr::get_field_id(size_t double_id) {
    return double_id & ((1 << (int)log2(sizeof_double)) - 1);
}

size_t cache_arr::get_short_id(size_t arr_id) {
    int pref_bits = arr_id >> (int)log2(blocks_in_way);
    return pref_bits;
}

size_t cache_arr::get_block_id(size_t arr_id) {
    return arr_id & ((1 << (int)log2(blocks_in_way)) - 1);
}

void cache_arr::write_block_ram(size_t way_id, size_t block_id) {
    size_t arr_id = (ids[way_id][block_id] << (int)log2(blocks_in_way)) + block_id;
    ram[arr_id] = element(cache[way_id][block_id]);
}

element& cache_arr::read_block_ram(size_t id_ram) {
    return ram[id_ram];
}

size_t cache_arr::get_way(size_t arr_id, size_t short_id, size_t block_id) {
    size_t best_way_id = 0;
    int min_time = cur_time;
    for (size_t way_id = 0; way_id < ways; ++way_id) {
        if (ids[way_id][block_id] == short_id) {
            min_time = 0;
            best_way_id = way_id;
        }

        if (acces_times[way_id][block_id] < min_time) {
            min_time = acces_times[way_id][block_id];
            best_way_id = way_id;
        }
    }

    if (ids[best_way_id][block_id] != short_id) {
        ++cache_misses_ct;

        if (min_time != 0)
            write_block_ram(best_way_id, block_id);

        auto block = read_block_ram(arr_id);
        block.write_element(cache[best_way_id][block_id]);
        ids[best_way_id][block_id] = short_id;
    }

    acces_times[best_way_id][block_id] = cur_time;
    return best_way_id;
}

double& cache_arr::lru_read(size_t double_id) {
    ++access_ct;

    size_t arr_id = get_arr_id(double_id);
    size_t field_id = get_field_id(double_id);
    size_t block_id = get_block_id(arr_id);
    size_t short_id = get_short_id(arr_id);
    size_t way_id = get_way(arr_id, short_id, block_id);

    return cache[way_id][block_id][field_id];
}

void cache_arr::lru_write(size_t double_id, double v) {
    ++access_ct;
        
    size_t arr_id = get_arr_id(double_id);
    size_t field_id = get_field_id(double_id);
    size_t short_id = get_short_id(arr_id);
    size_t block_id = get_block_id(arr_id);
    size_t way_id = get_way(arr_id, short_id, block_id);
        
    cache[way_id][block_id][field_id] = v;
}

void cache_arr::print_log() {
    std::cout << "number of misses: " << cache_misses_ct << '\n';
    std::cout << "percentage of misses: " << std::fixed << std::setprecision(1) << (double)cache_misses_ct * 100 / access_ct << "%" << '\n';
}

cache_arr::cache_arr(element* arr_) {
    cache_misses_ct = access_ct = cur_time = 0;
    ram = arr_;
        
    memset(cache, 0, sizeof(double) * ways * blocks_in_way * block_double_size);
    memset(ids, n + 1, sizeof(size_t) * ways * blocks_in_way);
    memset(acces_times, 0, sizeof(int) * ways * blocks_in_way);
}

double& cache_arr::read(size_t id, size_t field_id) {
    ++cur_time;
    return lru_read(id * (1 << field_id_size) + field_id);
}
    
void cache_arr::write(size_t id, size_t field_id, double v) {
    ++cur_time;
    lru_write(id * (1 << field_id_size) + field_id, v);
}