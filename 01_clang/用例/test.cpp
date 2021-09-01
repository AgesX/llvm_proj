//
//  test.cpp
//  999998
//
//  Created by Jz D on 2021/9/1.
//




void test(int a, int b, int c, int d, int e){
   if (a > 0){ }

    if (a > 0 || b > 0){ }

    if ((a > 0 || b > 0) && c > 0){ }

    if (((a > 0 || b > 0) && c > 0) || d > 0){ }

    if ((((a > 0 || b > 0) && c > 0) || d > 0) && e > 0){ }

    if (((a > 0 || b > 0) && (c > 0 || d > 0)) || e > 0){ }

    if (a > 0 || b > 0 || c > 0 || d > 0 || e > 0){ }
}


