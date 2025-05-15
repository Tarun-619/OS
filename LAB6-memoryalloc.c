#include <stdio.h>

struct Block {
    int size;
    int is_free;
};

struct File {
    int size;
};

void firstFit(struct Block blocks[], int n_blocks, struct File files[], int n_files) {
    printf("\nfirst fit alloc\n");
    printf("file no\tfile size\tblock no\tblock size\tfrag\n");
    for (int i = 0; i < n_files; i++) {
        int allocated = 0;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j].is_free && blocks[j].size >= files[i].size) {
                blocks[j].is_free = 0;
                printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, files[i].size, j + 1, blocks[j].size, blocks[j].size - files[i].size);
                allocated = 1;
                break;
            }
        }
        if (!allocated) {
            printf("file %d cannot be allocated\n", i + 1);
        }
    }
}

void bestFit(struct Block blocks[], int n_blocks, struct File files[], int n_files) {
    printf("\best fit alloc\n");
    printf("file no\tfile size\tblock no\tblock size\tfrag\n");
    for (int i = 0; i < n_files; i++) {
        int best_block = -1, min_fragment = 10000;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j].is_free && blocks[j].size >= files[i].size) {
                int fragment = blocks[j].size - files[i].size;
                if (fragment < min_fragment) {
                    min_fragment = fragment;
                    best_block = j;
                }
            }
        }
        if (best_block != -1) {
            blocks[best_block].is_free = 0;
            printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, files[i].size, best_block + 1, blocks[best_block].size, min_fragment);
        } else {
            printf("File %d cannot be allocated\n", i + 1);
        }
    }
}

void worstFit(struct Block blocks[], int n_blocks, struct File files[], int n_files) {
    printf("\nworst fit alloc\n");
     printf("file no\tfile size\tblock no\tblock size\tfrag\n");
    for (int i = 0; i < n_files; i++) {
        int worst_block = -1, max_fragment = -1;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j].is_free && blocks[j].size >= files[i].size) {
                int fragment = blocks[j].size - files[i].size;
                if (fragment > max_fragment) {
                    max_fragment = fragment;
                    worst_block = j;
                }
            }
        }
        if (worst_block != -1) {
            blocks[worst_block].is_free = 0;
            printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, files[i].size, worst_block + 1, blocks[worst_block].size, max_fragment);
        } else {
            printf("file %d cannot be allocated\n", i + 1);
        }
    }
}

int main() {
    int n_blocks, n_files;

    printf("enter the number of blocks: ");
    scanf("%d", &n_blocks);
    printf("enter the number of files: ");
    scanf("%d", &n_files);

    struct Block blocks[n_blocks];
    struct File files[n_files];

    for (int i = 0; i < n_blocks; i++) {
        printf("enter the size of block %d: ", i + 1);
        scanf("%d", &blocks[i].size);
        blocks[i].is_free = 1;
    }

    for (int i = 0; i < n_files; i++) {
        printf("enter the size of file %d: ", i + 1);
        scanf("%d", &files[i].size);
    }

    firstFit(blocks, n_blocks, files, n_files);

    for (int i = 0; i < n_blocks; i++) blocks[i].is_free = 1;

    bestFit(blocks, n_blocks, files, n_files);

    for (int i = 0; i < n_blocks; i++) blocks[i].is_free = 1;

    worstFit(blocks, n_blocks, files, n_files);

    return 0;
}
