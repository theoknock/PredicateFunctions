//
//  PredicateFunctions.h
//  PredicateFunctions
//
//  Created by Xcode Developer on 9/10/22.
//

#ifndef PredicateFunctions_h
#define PredicateFunctions_h

@import Foundation;

typedef typeof(unsigned long)                                  predicate;
typedef typeof(const predicate(^ _Nonnull )(predicate))        predicate_function;
typedef restrict typeof(const predicate_function *) predicate_function_t;
//typedef typeof(const predicate(^ _Nonnull const *)(predicate)) predicate_function_t;

predicate_function(^ _Nonnull (^ _Nonnull synchronous_predicate_functions)(predicate_function))(predicate_function) =  ^ (predicate(^init_func)(predicate)) {
    return ^ (predicate(^inter_func)(predicate)) {
        return ^ predicate (predicate pred) {
            return inter_func(init_func(pred)); // invokes and returns two functions in serial order
        };
    };
};

predicate_function(^ _Nonnull (^ _Nonnull asynchronous_predicate_functions)(_Nonnull predicate_function))(_Nonnull predicate_function) =  ^ (predicate(^init_func)(predicate)) {
    return ^ (predicate(^inter_func)(predicate)) {
        return ^ predicate (predicate pred) {
            return inter_func(pred) & init_func(pred); // invokes and returns two functions independently
        };
    };
};

predicate_function (^ _Nonnull (^ _Nonnull (^ _Nonnull combine_predicate_functions)(_Nonnull predicate_function))(_Nonnull predicate_function))(_Nonnull predicate_function(^ _Nonnull)(_Nonnull predicate_function_t, _Nonnull predicate_function_t, predicate)) =  ^ (predicate_function pred_f) {
    return ^ (predicate_function p_func) {
        return ^ (predicate_function(^evaluation)(predicate_function_t, predicate_function_t, predicate)) {
            return ^ predicate (predicate p) {
                return evaluation(&pred_f, &p_func, p)(p);
            };
        };
    };
};

static predicate_function (^ _Nonnull compose)(predicate_function, predicate_function) = ^ (predicate_function composition, predicate_function component) {
    predicate_function temp_comp = composition;
    predicate_function new_comp = ^ (unsigned long c) { printf("composing block chain...\n"); return component(temp_comp(c)); };
    return new_comp;
};

static unsigned long (^ _Nonnull (^ _Nonnull (^ _Nonnull objects_iterator)(void))(predicate_function))(void) = ^{
    __block unsigned long audio_state_cond = 0UL;
    static volatile predicate_function object_composition = ^ unsigned long (unsigned long c) { printf("invocation #%lu\n", c); return c; };
    return ^ (predicate_function object) { // Replace block object with the combine_predicate_functions block
        object_composition = combine_predicate_functions(object_composition)(object)(^ (predicate_function_t init_func_t, predicate_function_t inter_func_t, predicate pred) {
            return ^ predicate (predicate pred) {
                return (*inter_func_t)((*init_func_t)(pred));
            };
        });
        return ^{
            predicate_function_t object_composition_ptr = &object_composition;
            return (*object_composition_ptr)(audio_state_cond = -~audio_state_cond);
        };
    };
};


static void (^wxyz)(void) = ^{
    predicate_function pf1 = ^ predicate (predicate p) { printf("p == %lu\n", p); return p; };
    predicate_function pf2 = ^ predicate (predicate p) { printf("p == %lu\n", (p = p + 1)); return p; };
    predicate_function pfx = combine_predicate_functions(pf1)(pf2)(^ (predicate_function_t init_func_t, predicate_function_t inter_func_t, predicate pred) {
        return ^ predicate (predicate pred) {
            return (*init_func_t)(pred) & (*inter_func_t)(pred);
            
        };
    });
    pfx(55);
};

static void (^abcd)(void) = ^{
    unsigned long(^(^asdf)(predicate_function))(void) = objects_iterator();
    predicate_function pf1 = ^ predicate (predicate p) { printf("pf1 == %lu\n", p); return p; };
    predicate_function pf2 = ^ predicate (predicate p) { printf("pf2 == %lu\n", (p = p + 1)); return p; };
    
    unsigned long(^defg)(void) = asdf(pf1);
    defg();
    unsigned long(^mnop)(void) = asdf(pf2);
    mnop();
    defg();
};

#endif /* PredicateFunctions_h */
