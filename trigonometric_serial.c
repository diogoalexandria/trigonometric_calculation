#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int is_odd(int number); 
long factorial(int number);
double sin_taylor(double rad, int deep);
double cos_taylor(double rad, int deep);
double tan_taylor(double sin, double cos);
void print_result(char *calculation, double getted, double c, double err);

int main(int argc, char *argv[]) {
    double initial_time = clock();
    
    if (argc > 5 || argc < 2) {
        printf("Erro de argumentos!\n USO: tangente gg mm ss angulo(em graus, minutos, e segundos)");
        exit(1);
    }       

    double degrees, minutes, seconds;
    int deep;

    if (argc == 2) {
        degrees = atof(argv[1]);
        minutes = 0.0;
        seconds = 0.0;
        deep = 2;
    } else if (argc == 3) {
        degrees = atof(argv[1]);
        minutes = 0.0;
        seconds = 0.0;
        deep = atoi(argv[2]);
    } else if (argc == 4) {
        degrees = atof(argv[1]);
        minutes = atof(argv[2]);
        seconds = 0.0;
        deep = atoi(argv[3]);
    } else if (argc == 5) {
        degrees = atof(argv[1]);
        minutes = atof(argv[2]);
        seconds = atof(argv[3]);
        deep = atoi(argv[4]);
    }            

    double PI = 3.141592635897932384626433832795;
    double rad = (double)(degrees + (minutes/60.0) + (seconds/3600.0)); 
    rad = rad * PI / 180.0;

    double sin_getted = sin_taylor(rad, deep);
    double sin_c = sin(rad);
    double err_sin = fabs(sin_c - sin_getted);

    double cos_getted = cos_taylor(rad, deep);
    double cos_c = cos(rad);
    double err_cos = fabs(cos_c - cos_getted);

    double tan_getted = tan_taylor(sin_getted, cos_getted);
    double tan_c = tan(rad);
    double err_tan = fabs(tan_c - tan_getted);

    print_result("Seno", sin_getted, sin_c, err_sin);
    print_result("Cosseno", cos_getted, cos_c, err_cos);
    print_result("Tangente", tan_getted, tan_c, err_tan);

    double final_time = clock();
    printf("Tempo decorrido: %f\n", fabs(final_time - initial_time)/(CLOCKS_PER_SEC/1000));
}

int is_odd(int number){
    if(number%2 != 0)
        return 1;

    return 0;
}

long factorial(int number) {
    if (number > 0) {
        return number * factorial(number - 1);
    }
    return 1;
}

double sin_taylor(double rad, int deep) {
    double response;
    for (int i = 1; i <= ((deep * 2) - 1); i++) {
        if (is_odd(i))
            response += pow(rad, i)/factorial(i);            
        else {
            i++;
            response -= pow(rad, i)/factorial(i);
            i++; 
        }
    }
    return response;
}

double cos_taylor(double rad, int deep) {
    double response = 1;
    for (int i = 1; i <= ((deep * 2) - 2); i++) {
        if (is_odd(i) && (i > 1)) {            
            i++;
            response += pow(rad, i)/factorial(i);
            i++;
        } else if (i > 1)            
            response -= pow(rad, i)/factorial(i);
    }
    return response;
}

double tan_taylor(double sin, double cos) {
    return sin / cos;
}

void print_result(char *calculation, double getted, double c, double err) {
    printf("%s:\n", calculation);
    printf("    Programa Serial: %f\n", getted);
    printf("    Valor Real: %f\n", c);
    printf("    Erro: %f\n", err);
}
