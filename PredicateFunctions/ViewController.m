//
//  ViewController.m
//  BlockCompositionTest
//
//  Created by Xcode Developer on 9/5/22.
//

#import "ViewController.h"
#include <stdio.h>
#include <stdlib.h>

@interface ViewController ()

@end

@implementation ViewController

typedef typeof(unsigned long(^)(unsigned long)) func;
typedef typeof(func(^)(func)) func_func;
void (^(^y_combinator)(unsigned long))(func_func) = ^ (unsigned long count) {
    static func(^recursive_block)(func_func);
    typeof(recursive_block) * recursive_block_t = &recursive_block;
    (*recursive_block_t) = ^ (func_func ff) {
        return ^ (unsigned long index) {
            return ^ unsigned long { return (0UL ^ index) && ((unsigned long)ff((*recursive_block_t)(ff))(~-index)); }();
        };
    };
    return ^ (func_func ff) {
        ff((*recursive_block_t)(ff))(count);
    };
};

- (void)viewDidLoad {
    [super viewDidLoad];
    abcd();

//    asdf();
//    wxyz();
    
    func_func i_eval = ^ (func expr) {
        return ^ (unsigned long i) {
            printf("i == %lu\n", i);
            return expr(i);
        };
    };
    y_combinator(10)(i_eval);
}


@end
