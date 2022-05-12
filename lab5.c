#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ulfius.h>

#define MAX_BUF_SIZE 100

long int counter;

int callback_print(const struct _u_request *request, struct _u_response *response, void *user_data)
{
    (void)request;
    (void)user_data;

    char buf[MAX_BUF_SIZE];

    snprintf(buf, MAX_BUF_SIZE, "%ld\n", counter);

    if (ulfius_set_string_body_response(response, 200, buf) != U_OK)
    {
        fprintf(stderr, "ulfius_set_string_body_response (get) failed\n");
        exit(EXIT_FAILURE);
    }

    return U_CALLBACK_CONTINUE;
}

int callback_increment(const struct _u_request *request, struct _u_response *response, void *user_data)
{
    (void)request;
    (void)response;
    (void)user_data;

    counter++;

    return U_CALLBACK_CONTINUE;
}

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "debe ingresar un número de puerto a utilizar\n");
        return 1;
    }

    long port = strtol(argv[1], NULL, 10);

    if (port < 1024)
    {
        fprintf(stderr, "número de puerto inválido\n");
        return EXIT_FAILURE;
    }

    struct _u_instance instance;

    if (ulfius_init_instance(&instance, (unsigned int)port, NULL, NULL) != U_OK)
    {
        fprintf(stderr, "ulfius_init_instance failed\n");
        return 1;
    }

    if (ulfius_add_endpoint_by_val(&instance, "GET", "/print", NULL, 0, &callback_print, NULL) != U_OK)
    {
        fprintf(stderr, "ulfius_add_endpoint_by_val (get) failed\n");
        return 1;
    }

    if (ulfius_add_endpoint_by_val(&instance, "POST", "/increment", NULL, 0, &callback_increment, NULL) != U_OK)
    {
        fprintf(stderr, "ulfius_add_endpoint_by_val (post) failed\n");
        return 1;
    }

    if (ulfius_start_framework(&instance) == U_OK)
    {
        counter = 0;

        printf("\nframework inicializado en puerto %d\n", instance.port);

        getchar();
    }
    else
        fprintf(stderr, "ulfius_start_framework failed\n");

    printf("finalizando framework...\n");

    if (ulfius_stop_framework(&instance) != U_OK)
    {
        fprintf(stderr, "ulfius_stop_framework failed\n");
        return 1;
    }

    ulfius_clean_instance(&instance);

    return EXIT_SUCCESS;
}