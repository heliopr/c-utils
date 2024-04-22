#include <stdio.h>

#include "ds/list.h"

int test_sorting() {
    int n;
    while (scanf("%d", &n) && n) {
        list *l = list_int_new();
        list *l2 = list_int_new();
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            list_append_int(l, x);
        }

        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            list_append_int(l2, x);
        }

        list_sort(l, list_cmp_int);

        bool falhou = false;
        for (int i = 0; i < n && !falhou; i++) {
            if (list_get_int(l, i) != list_get_int(l2, i)) {
                printf("FALHOU\n");
                falhou = true;
                break;
            }
        }
        
        if (!falhou) {
            printf("DEU CERTO\n");
        }
    }

    return 0;
}

int main() {
    
}