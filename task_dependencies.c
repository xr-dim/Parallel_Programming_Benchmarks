//Christos Dimitresis   4351

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <omp.h>

#define BUFFER_SIZE  50

char buffer[BUFFER_SIZE];
int fp;
long file_size;

void reader(size_t nbytes){
    read(fp,buffer,nbytes);
}

void writer(size_t nbytes){
    write(STDOUT_FILENO, buffer, nbytes);
}

int main(void) {

    fp = open("openMP_execution_model.txt", O_RDONLY);

    if (fp == -1) {
        perror("Opening file failed. System exit");
        return -1;
    }

    file_size = lseek(fp, 0, SEEK_END);
    lseek(fp, 0, SEEK_SET);

    int iterations_num = file_size / BUFFER_SIZE;
    size_t last_chunk_bytes = file_size % BUFFER_SIZE;

    #pragma omp parallel
    #pragma omp single
    {
        for (int i = 0; i <= iterations_num; i++) {
            #pragma omp task depend(out : buffer)
            writer(BUFFER_SIZE);

            #pragma omp task depend(in : buffer)
            reader(BUFFER_SIZE);
        }
    }

    reader(last_chunk_bytes);
    writer(last_chunk_bytes);

}
