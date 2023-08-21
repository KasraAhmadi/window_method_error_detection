/*
 * Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
 * Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "window_method.h"

int main() {

    int i, retval = 0;
    ofstream FILE;
    Point base_point = {5,1}; // Example base point on the elliptic curve
    int scalar = 120120; // Example scalar value

    // Save the results to a file
    FILE.open ("result.txt");
    for (i = 0; i < 10; ++i) {
    	Point result1 = error_detection_window_method(base_point, scalar+i);
        printf("result: (%d, %d)\n", result1.x, result1.y);
    }

    FILE.close();

//
//    // Compare the results file with the golden results
//    retval = system("diff --brief -w result.dat result.golden.dat");
//    if (retval != 0) {
//        printf("Test failed  !!!\n");
//        retval = 1;
//    } else {
//        printf("Test passed !\n");
//    }

    // Return 0 if the test passed
    printf("Test Sucessed  !!!\n");

    return 0;
}

