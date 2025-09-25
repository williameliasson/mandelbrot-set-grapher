// 22-07-11

#include <stdio.h>
#include <ctype.h>

struct Complex{
    double real;
    double imag;
};

struct Complex add_complex(struct Complex a, struct Complex b){
    struct Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

struct Complex multiply_complex(struct Complex a, struct Complex b){
    struct Complex result = {(a.real*b.real - a.imag*b.imag), (a.real*b.imag + a.imag*b.real)};
    return result;
}

const char* get_display_complex(struct Complex a){
    char sign = '+';
    if (a.imag < 0){
        sign = '-';
        a.imag *= -1;
    }
    char display_text[256];
    snprintf(display_text, 256, "%lf %c %lfi", a.real, sign, a.imag);
    return display_text;
}

int is_mandelbrot(struct Complex c, int iterations, int z_power){
    struct Complex z = {0,0};
    struct Complex a;
    for (int i = 0; i < iterations; i++){
        a = z;
        a = multiply_complex(a,z);
        
        for (int j = 0; j < z_power-2; j++){
            a = multiply_complex(a,z);
        }
        z = add_complex(a, c);

        if (z.real > 2 || z.imag > 2){
            return 0;
        }
    }
    return 1;
}

void draw_mandelbrot(int size_x, int size_y, struct Complex top_left, struct Complex bottom_right, int z_power){
    double step_x_per_pixel = (bottom_right.real - top_left.real)/size_x;
    double step_y_per_pixel = (bottom_right.imag - top_left.imag)/size_y;

    int max_iterations = 20;

    struct Complex current;
    char pixel;
    for (int y = 0; y < size_y; y++){
        for (int x = 0; x < size_x; x++){
            pixel = ' ';
            current.real = x*step_x_per_pixel+top_left.real;
            current.imag = y*step_y_per_pixel+top_left.imag;
            int result = is_mandelbrot(current, max_iterations,z_power);
            if (result){
                pixel = '#';
            }
            printf("%c", pixel);
        }
        printf("\n");
    }
}

int main(){
    int exit_program = 0;
    
    struct Complex top_left = {-2, 2.5};
    struct Complex bottom_right = {2, -1.5};
    
    
    double pan_amount = 0.1;

    char user_input;
    
    while (exit_program == 0) {

        draw_mandelbrot(100, 112/2, top_left, bottom_right, 2);

        printf("Enter N/E/W/S\n");
        scanf(" %c", &user_input);
        
        // Make lowercase to allow for for both upper and lowercase
        user_input = tolower((unsigned char)user_input);

        switch (user_input){
            case 'n':
                // North
                top_left.imag += pan_amount;
                bottom_right.imag += pan_amount;
                break;
            case 'e':
                // East
                top_left.real += pan_amount;
                bottom_right.real += pan_amount;
                break;
            case 'w':
                // West
                top_left.real -= pan_amount;
                bottom_right.real -= pan_amount;
                break;
            case 's':
                // South
                top_left.imag -= pan_amount;
                bottom_right.imag -= pan_amount;
                break;
            case '+':
                // Zoom in
                break;
            case '-':
                // Zoom out
                break;
        }
    }

    return 0;
}