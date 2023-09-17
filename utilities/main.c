#include <stdio.h>
#include<stdlib.h>
#include <uv.h>

int64_t counter=0;
int64_t repeat_count=0;

void idle_callback(uv_idle_t* handle) {

    if(counter < 0) {
        printf("Stopping idling: %lld\n",counter);
        uv_idle_stop(handle);
        return;
    }

    counter++;
    printf("Idle callback called times: %lld\n",counter);
}

void set_timeout_callback(uv_timer_t* handle) {
    counter=-1;
    printf("Exectued timeout callback %lld times\n",++repeat_count);
}

void set_interval_callback(uv_timer_t* handle) {
    repeat_count++;

    if(repeat_count>1) {
        counter=-1;
        printf("Exectued interval callback %lld times\n",repeat_count);
        uv_timer_stop(handle);
    }
}

int main() {
    uv_loop_t *loop = uv_default_loop();
    uv_idle_t idler;
    uv_timer_t timer_req;

    uv_idle_init(loop,&idler);
    uv_timer_init(loop, &timer_req);

    uv_idle_start(&idler, idle_callback);
    uv_timer_start(&timer_req,set_timeout_callback,1000,0);
    // uv_timer_start(&timer_req,set_interval_callback,2000,2000);

    printf("Running loop..\n");
    uv_run(loop, UV_RUN_DEFAULT);
    printf("Loop quit..\n");

    uv_loop_close(loop);
    return 0;
}
