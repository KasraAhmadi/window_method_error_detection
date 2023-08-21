#include "window_method.h"


int* decimalToBinary(int decimal, int* scalar_bits) {
        int i = 0;
        while (decimal > 0) {
        	scalar_bits[i] = decimal % 2;
            decimal /= 2;
            i++;
        }
        return scalar_bits;
}

int modular_exponentiation(int a, int b){

#pragma HLS allocation operation instances=mul limit=6
#pragma HLS allocation operation instances=srem limit=6

    int ans = 1;
    a = a % MOD;
    while(b > 0){
        if(b % 2 == 1){
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        b = b / 2;
    }
    return ans;
}

int inverse(int a){
    return modular_exponentiation(a, MOD-2);
}

int CC(int* pre_pattern_counter,int* post_pattern_counter,int length){
    for (int i = 0;i<length;i++){
        if(pre_pattern_counter[i] != post_pattern_counter[i])
            return 1;
    }
    return 0;
}

void error_detection(int* pre_pattern_counter,int scalar_bits_length,int * scalar_bits,int width,int* width_precomputation){
    int length_counter = (int)scalar_bits_length/width;
    int width_helper = width - 1;
    for (int i = 0; i < length_counter; i++) {
        int window_value = 0;
        for (int j = 1;j<=width;j++){
            if(scalar_bits[scalar_bits_length-((i*width)+j)] == 1){
                window_value += width_precomputation[width_helper-j+1];
            }
        }
        pre_pattern_counter[window_value] += 1;
    }
}
// Function to add two points on the elliptic curve
Point point_add(Point p, Point q) {
    Point result;

    int lambda;
    if(p.x == 0 && p.y == 0)
        return q;
    if(q.x == 0 && q.y == 0)
        return p;
    
    if (p.x == q.x && p.y == q.y) {
        // Point doubling
        lambda = ((((3 * p.x * p.x) + A_COEFFICENT) % MOD) * inverse(2 * p.y)) % MOD;
    } else {
        // Point addition
        lambda = (((p.y - q.y) % MOD) * inverse((p.x - q.x))) % MOD;
    }
    
    result.x = ((lambda * lambda) - p.x - q.x) % MOD;
    result.y = (lambda * (p.x - result.x) - p.y) % MOD;
    
    if (result.x < 0)
        result.x += MOD;
    if (result.y < 0)
        result.y += MOD;
    
    return result;
}

Point error_detection_window_method(Point point, int scalar) {

	#pragma HLS INTERFACE ap_none port = scalar
	#pragma HLS allocation ap_none port = point
    int scalar_bits[32];
    int width_precomputation [WIDTH];
    Point _precomputed_points[SIZE_PRECOMPUTED];
    Point* precomputed_points = &_precomputed_points[0];
    Point current_point = point;
    int pre_pattern_counter[SIZE_PRECOMPUTED];
    int post_pattern_counter[SIZE_PRECOMPUTED];


    for(int i=0;i<WIDTH;i++)
        width_precomputation[i] = pow(2,i);

    for (int i = 0; i < (1 << WIDTH); i++) {
        precomputed_points[i] = current_point;
        current_point = point_add(point,current_point);

    }
    decimalToBinary(scalar,scalar_bits);
    Point result = {0,0};
	#pragma HLS INTERFACE ap_none port = result
    int scalar_bits_length = log2(scalar)+1;
    int window = 0;
    int max_window_number = floor(scalar_bits_length/WIDTH);
    int last_window_length = (scalar_bits_length%WIDTH);
    if(last_window_length == 0)
        last_window_length = WIDTH;
    int window_counter = 0;    
    error_detection(pre_pattern_counter,scalar_bits_length,scalar_bits,WIDTH,width_precomputation);

    for (int i = 1; i <= scalar_bits_length; i++) {
        if(window_counter == max_window_number){
            if(scalar_bits[scalar_bits_length-i]!=0){

                window += width_precomputation[(i%WIDTH)%last_window_length];
            }
        }
        else{
            if(scalar_bits[scalar_bits_length-i]!=0){
                window += width_precomputation[WIDTH-1-((i-1)%WIDTH)];
            }
        }
        int reminder = i%WIDTH;
        if ((reminder == 0) || i == scalar_bits_length) {
            window_counter += 1;
            post_pattern_counter[window] +=1;
            
            // Shifting
            int j;
            int shift_number = WIDTH;
            if (i == scalar_bits_length && reminder!=0){
                shift_number = reminder;
            }
            for (j = 0; j < shift_number; j++) {
                result = point_add(result,result);
            }
            if (window != 0) {
                result = point_add(result,precomputed_points[window - 1]);
                window = 0;
            }
        }
    }
    CC(pre_pattern_counter,post_pattern_counter,SIZE_PRECOMPUTED);
    return result;
}
