#include <windows.h>
#include "debug.h"
#include "config.h"
#include "crc32.h"

static unsigned long g_ini_section_hashes[1024];

BOOL ini_section_exists(char* section)
{
    if (!g_ini_section_hashes[0])
    {
        char* buf = calloc(8192, 1);
        if (buf)
        {
            if (GetPrivateProfileSectionNamesA(buf, 8192, g_config.ini_path) > 0)
            {
                for (int i = 0; *buf && i < sizeof(g_ini_section_hashes) / sizeof(g_ini_section_hashes[0]); i++)
                {
                    size_t len = strlen(buf);

                    for (char* p = buf; *p; ++p) 
                        *p = tolower(*p);

                    g_ini_section_hashes[i] = Crc32_ComputeBuf(0, buf, len);

                    buf += len + 1;
                }
            }
            
            free(buf);
        }
    }

    char s[MAX_PATH];
    strncpy(s, section, sizeof(s) - 1);

    for (char* p = s; *p; ++p)
        *p = tolower(*p);

    unsigned long hash = Crc32_ComputeBuf(0, s, strlen(s));

    for (int i = 0; i < sizeof(g_ini_section_hashes) / sizeof(g_ini_section_hashes[0]) && g_ini_section_hashes[i]; i++)
    {
        if (g_ini_section_hashes[i] == hash)
            return TRUE;
    }

    return FALSE;
}
