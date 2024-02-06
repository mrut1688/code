<<<<<<< HEAD
#include <stdio.h>
//int plus(int x,int y);

// int plus(int x,int y)
// // {
//     return x+y;

// }

// void sumstore(int x,int y,int *dest)
// {
// int t=plus(x,y);
// *dest=t;

// }
 
 void swap(int *xp,int *yp)
{
    int t0=*xp;
    int t1=*yp;
    *xp=t1;
    *yp=t0;

}
int arith(int x,int y,int z)
{
    int t1=x+y;
    int t2=z+t1;
    int t3=x;
    int t4=y*48;
    int t5=t3+t4;
    int rval=t2+t5;
    return rval;
}

int abs(int v)
{
    int mask=v>>4*8-1;
    return(v+mask)^mask;

}
int main(){
    int a=abs(1);
    printf("%d",a);
}
=======
#include <stdio.h>
//int plus(int x,int y);

// int plus(int x,int y)
// // {
//     return x+y;

// }

// void sumstore(int x,int y,int *dest)
// {
// int t=plus(x,y);
// *dest=t;

// }
 
 void swap(int *xp,int *yp)
{
    int t0=*xp;
    int t1=*yp;
    *xp=t1;
    *yp=t0;

}
int arith(int x,int y,int z)
{
    int t1=x+y;
    int t2=z+t1;
    int t3=x;
    int t4=y*48;
    int t5=t3+t4;
    int rval=t2+t5;
    return rval;
}

int abs(int v)
{
    int mask=v>>4*8-1;
    return(v+mask)^mask;

}
int main(){
    int a=abs(1);
    printf("%d",a);
}
>>>>>>> a73a13b226717f7103f548730cc403470029c9fc
