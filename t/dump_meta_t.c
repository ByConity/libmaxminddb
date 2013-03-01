#include "MMDB.h"
#include "tap.h"
#include <sys/stat.h>
#include <arpa/inet.h>
#include <string.h>

uint32_t ip_to_num(char *ipstr)
{
    struct in_addr ip;
    if (ipstr == NULL || 1 != inet_pton(AF_INET, ipstr, &ip))
        return 0;
    return htonl(ip.s_addr);
}

int main(void)
{
    char *fname = "./data/test-database.dat";
    struct stat sstat;
    int err = stat(fname, &sstat);
    ok(err == 0, "%s exists", fname);

    MMDB_s *mmdb = MMDB_open(fname, MMDB_MODE_MEMORY_CACHE);
    ok(mmdb != NULL, "MMDB_open successful");
    if (mmdb) {

        MMDB_decode_all_s *decode_all = calloc(1, sizeof(MMDB_decode_all_s));
        int err = MMDB_get_tree(&mmdb->meta, &decode_all);

        if (decode_all != NULL)
            MMDB_dump(decode_all, 0);
    }
    done_testing();
}