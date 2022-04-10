#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#define N 1000


FILE *f1,*f2,*f3;
struct ARRAYS{
    float t[N];
    float Uvx[N];
    float Uvix[N];
}arrays;



void zastavka(){
    FILE *f=fopen("zastavka.txt","r");
    char ch;
    while (!feof(f))
    {
        fscanf(f,"%c",&ch);
        printf("%c",ch);
    }
    fclose(f);

}
void time_form(n){
    float tn=-1.5, tk=1.5, dt;
    dt = (tk - tn) / (n - 1);
    for(int i=0; i < n; i++)
        arrays.t[i] = tn + i * dt;
}


void Uvx_form(n){
    float U = 10,a=1.5;
    for(int i=0;i<n;i++)
        arrays.Uvx[i] = U * pow(M_E, -(pow(a, 2) * pow(arrays.t[i], 2)));
}


void Uvix_form(n){
    float a1 = 0.25, a2 = 0.5, a3 = 1.1, a4 = 25, b1 = 9, b2 = 7.75, b3 = 0.25, b4 = -29.75;
    float Uvx1=5, Uvx2 = 15, Uvx3=30;
    for(int i = 0; i < n; i++) {
        if (arrays.Uvx[i] <= Uvx1) arrays.Uvix[i] = a1 * arrays.Uvx[i] + b1;
        else if (Uvx1 < arrays.Uvx[i] <= Uvx2) arrays.Uvix[i] = a2 * arrays.Uvx[i] + b2;
        else if (Uvx2 < arrays.Uvx[i] <= Uvx3) arrays.Uvix[i] = a3 * arrays.Uvx[i] + b3;
        else if (arrays.Uvx[i] > Uvx3) arrays.Uvix[i] = a4 * arrays.Uvx[i] + b4;
    }
}


void form_table(n){
    system("clear");
    int i;
    printf("|-----------------------------------------|\n|    №   |     t    |    Uvx   |   Uvix   |\n|-----------------------------------------|\n");
    for (i = 0; i < n; i++) {
        printf("|  %3d   |  %6.3f  |  %6.3f  |  %6.3f  |\n|-----------------------------------------|\n", i, arrays.t[i], arrays.Uvx[i], arrays.Uvix[i]);
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}



float parameter_u(n) {
    float max = 0;
    for(int i = 0; i < n; i++)
        if (arrays.Uvx[i] > max) max = arrays.Uvx[i];
    return max;
}

float parameter_t(n){
    float max = 0;
    for(int i = 0; i < n; i++)
        if (arrays.Uvx[i] > max) max = arrays.Uvx[i];
    for (int i = 0; i < n; i++)
        if (arrays.Uvx[i] == max) {
            return arrays.t[i];
        }
    return 0;
}


void file_writer(n){
    f1=fopen("massiv_t.txt","w");
    f2=fopen("massiv_Uvx.txt", "w");
    f3=fopen("massiv_Uvix.txt", "w");
    for (int i=0;i<n;i++)
    {
        fprintf(f1, "%.3f\n", arrays.t[i]);
        fprintf(f2, "%.3f\n", arrays.Uvx[i]);
        fprintf(f3, "%.3f\n", arrays.Uvix[i]);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
}


void par_pog(n){
    float full = 999;
    float x = parameter_u(n);
    float y = parameter_t(n);
    time_form(full);
    Uvx_form(full);
    float f = parameter_u(full);
    float g = parameter_t(full);
    printf("|------------------------------------------------------------------------------|\nПараметр входного сигнала = %f\t\t\tПогрешность = %f\n", x, fabs(f - x)/x);
    printf("|------------------------------------------------------------------------------|\nМомент времени = %f\t\t\t\tПогрешность = %f\n|------------------------------------------------------------------------------|\n", y, fabs(g - y)/x);
}


int main(){
    int n, nom;
    char ch;
    system("clear");
    zastavka();
    sleep(5);
    system("clear");
    while (1) {
        printf("-------------------------------Меню---------------------------------------\n1. Контрольный расчет t, Uvx,  Uvix для  n точек\n2. Расчет параметра с заданной точностью\n3. Запись данных в файл\n>> ");
        scanf("%d", &nom);
        system("clear");
        printf("Введите количество точек для расчета\n>> ");
        scanf("%d", &n);
        time_form(n);
        Uvx_form(n);
        Uvix_form(n);
        switch (nom) {
            case 1:
                form_table(n);
                break;
            case 2:
                par_pog(n);
                break;
            case 3:
                file_writer(n);
                break;
            default:
                printf("\nВведите корректное задание\n");
                break;
        }
        printf("Для выхода введите q, для продолжения нажмите Enter\n");
        scanf("%c", &ch);
        scanf("%c", &ch);
        if (ch == 'q') {
            system("clear");
            printf("Язык си с вами прощается!\nДобро пожаловать обратно в меню Bash\n");
            system("./mainscript.sh");
            return 0;
        }
        system("clear");
    }
}


//Источники:
//«Информатика. Анализ сигнала на выходе электрической цепи. Методические указания к курсовой работе», Л. Н. Бережной, И. О. Воронцова, Д. В. Окунева, СПб 2012
