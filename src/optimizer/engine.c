#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to clear system cache
void clear_cache() {
    printf("Clearing system cache...\n");
    system("sync; echo 3 > /proc/sys/vm/drop_caches");
}

// Function to optimize memory (using malloc/free to trigger memory compaction if possible, 
// but primarily relies on clearing caches and killing unnecessary processes)
void optimize_memory() {
    printf("Optimizing memory...\n");
    // In a real scenario, we might look for specific memory-heavy processes to restart or clean
    system("sync; echo 1 > /proc/sys/vm/drop_caches");
}

// Function to clean temporary files
void clean_temp_files() {
    printf("Cleaning temporary files...\n");
    system("rm -rf /tmp/*");
    system("rm -rf /var/tmp/*");
    system("apt-get clean");
}

// Function to get memory usage percentage
double get_memory_usage() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) return 0.0;

    char line[256];
    long total_mem = 0, free_mem = 0, buffers = 0, cached = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "MemTotal: %ld kB", &total_mem) == 1) continue;
        if (sscanf(line, "MemFree: %ld kB", &free_mem) == 1) continue;
        if (sscanf(line, "Buffers: %ld kB", &buffers) == 1) continue;
        if (sscanf(line, "Cached: %ld kB", &cached) == 1) continue;
    }
    fclose(fp);

    if (total_mem == 0) return 0.0;
    long used_mem = total_mem - (free_mem + buffers + cached);
    return (double)used_mem / total_mem * 100.0;
}
