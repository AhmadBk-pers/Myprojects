#include <stdio.h>
void func2(void *arg) {
    long f2;
    typedef void sigrout_t(void*);
    printf("Enter func2\n");
 
    /* Area2 */
 	
    *(long *)&arg -=2;
     ((sigrout_t*) ) (arg);
    
 
    printf("Exit func2\n");
}
void func1() {
    long f1;
    printf("Enter func1\n");
    func2(&f1);
    printf("Exit func1\n");
}
 
int main() {
    const long x=1;
    long y=5;
 
    /* Area1 */
 
    printf("x=%lu\n",x);
    func1();
 
    printf("Exit main\n");
    return 0;
}
