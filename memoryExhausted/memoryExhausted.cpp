#include <cstdio>
#include <cstdlib>
#include "unistd.h"
#include "glib.h"

int main()
{
    char* buffer = NULL;

    printf("Allocate buffer using malloc!\n");
    while (true)
    {
        buffer = (char*)malloc(1024 * 1024 * 10);
        
        if (buffer == NULL)
        {
            printf("Buffer null!\n");
            break;
        }
    }
    
    //printf("Allocate buffer using operator new!\n");
    //sleep(2);
    //buffer = new char[1024*1024*10];

    printf("Allocate buffer using g_variant_builder_new!\n");
    sleep(2);
    GVariant * gVariant = g_variant_new( "s", "text");


    GVariantType * type =
    g_variant_type_new ("sa");

    sleep(10);

    return 0;

}
