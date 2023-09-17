#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

void managedLoop() {
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    printf("Running Managed Loop.\n");
    uv_run(loop, UV_RUN_DEFAULT);
    printf("Loop quit.\n");

    uv_loop_close(loop);
    free(loop);
}

void defaultLoop() {
    uv_loop_init(uv_default_loop());

    printf("Running Default Loop.\n");
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    printf("Loop quit.\n");

    uv_loop_close(uv_default_loop());
}
int main() {
    managedLoop();
    defaultLoop();
    return 0;
}