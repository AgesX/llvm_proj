//
//  ViewController.m
//  Demo
//
//  Created by 6666666 on 2020/11/16.
//  Copyright © 2020 6666666. All rights reserved.
//

#import "ViewController.h"


void test(int a, int b, int c, int d, int e){
   if (a > 0){ }

    if (a > 0 || b > 0){ }

    if ((a > 0 || b > 0) && c > 0){ }

    if (((a > 0 || b > 0) && c > 0) || d > 0){ }

    if ((((a > 0 || b > 0) && c > 0) || d > 0) && e > 0){ }

    if (((a > 0 || b > 0) && (c > 0 || d > 0)) || e > 0){ }

    if (a > 0 || b > 0 || c > 0 || d > 0 || e > 0){ }
}


@interface ViewController ()

@property(nonatomic, copy) NSString* name;
@property(nonatomic, strong) NSArray* arrs;

@end

@implementation ViewController


- (void)test:(NSInteger)a  one: (NSInteger) b two: (NSInteger) c three: (NSInteger) d four: (NSInteger) e{
    if (a > 0){}

    if (a > 0 || b > 0){ }

    if ((a > 0 || b > 0) && c > 0){ }

    if (((a > 0 || b > 0) && c > 0) || d > 0){ }

    if ((((a > 0 || b > 0) && c > 0) || d > 0) && e > 0){ }

    if (((a > 0 || b > 0) && (c > 0 || d > 0)) || e > 0){ }

    if (a > 0 || b > 0 || c > 0 || d > 0 || e > 0){ }
}


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    
    
}




@end
