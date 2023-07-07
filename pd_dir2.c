#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

/*lai neizmainitu neko pointeros, izmanto const*/
void search_in_dir (const char *merka_cels, const char *nosaukums) {
    char cels[255];
    char pilnais_cels[255];
    DIR *d;
    struct dirent *de; /*ieraksti no direktorijas*/
    struct stat buferis;

    strcpy(cels, merka_cels);

    /*parbauda vai cela garums neparsniedz 255, kas noradits uzd noteikumos*/
    if (strlen(cels) > 255 ) {
        printf("Noraditais direktorijas cels ir garaks par 255 simboliem!\n");
        return;
    }
    /* pievieno / cela beigas*/
    if (cels[strlen(cels) -1] != '/') {
        strcat(cels, "/");
    }

    /*iziet cauri visiem direktoriju ierakstiem*/
    if (!(d = opendir(cels))) {
        printf("[%s] direktoriju neizdevas atvert! \n", cels);
        return;
    }

    while ((de = readdir(d)) != NULL) {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0 ) {
            continue;
        }

        strcpy(pilnais_cels, cels);
        strcat(pilnais_cels, de->d_name);

        /*ja faila vards sakrit -> izdruka ar pino celu */
        if (strcmp(de->d_name, nosaukums) == 0 ) {
            printf("%s\n", pilnais_cels);
        }

        /* printf("Fails: %s\n" , pilnais_cels); - visi failu nosaukumi direktorijā */
        if (lstat(pilnais_cels, &buferis) < 0 ) {
            printf("Fails neeksiste! \n");
            return;
        }

        /*parbaudit vai direktorija nav link */
        if (S_ISLNK(buferis.st_mode)) {
            continue;
        }

        /* ja fails ir direktorija (!= 0), rekursivi izsaukt serarch_in_dir */
        if (S_ISDIR(buferis.st_mode)) {
            search_in_dir(pilnais_cels, nosaukums);
        }
    }

    closedir(d);
}

int main(int argc, char **argv) {
    struct stat buferis;

    /*parbauda padoto argumentu skaitu */
    if (argc != 3) {
        printf("Noradits nepareizs argumentu skaits! \n");
        return -1;
    }

    /*parbaudit vai eksiste. ja <0, tad neeksiste*/
    if (lstat(argv[2], &buferis) < 0 ) {
        printf("Direktorija neeksiste! \n");
        return -1;
    }

    /*parbaudit vai direktorija. ja atgriež 0, tad nav */
    if (!S_ISDIR(buferis.st_mode)) {
        printf("Padotais cels nav direktorija! \n");
        return -1;
    }

/*    printf("Parametri padoti korekti, uzsak meklesanu!"); */

    search_in_dir(argv[2],argv[1]);

    return 0;
}
